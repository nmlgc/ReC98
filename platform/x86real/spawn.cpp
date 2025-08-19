#pragma option -zC_TEXT

#include <dos.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "platform/x86real/dos.hpp"
#include "platform/x86real/flags.hpp"
#include "platform/x86real/spawn.hpp"
#include "platform/x86real/spawnenv.hpp"

#if defined(__TURBOC__) && defined(__MSDOS__)
// Nothing wrong with Borland's low-level spawn function.
extern "C" int near __cdecl _spawn(
	const char *pathP, const char *cmdP, const char *envP
);
#endif

static int near report(int ret, const char* path)
{
	if(ret == -1) {
		printf("%s: Failed to spawn `%s", _argv[0], path);
		perror("`");
	}
	return ret;
}

// TSR spawning
// ------------
// Any TSRs spawned after the initialization of the C heap (i.e., at any point
// after main()) need to be spawned at the top of conventional memory to not
// block the C heap from expanding. It might seem as if the "low memory last
// fit" allocation strategy (INT 21h AX=5801h BL=2) would be all we need here,
// but it effectively only ends up placing the TSR's environment segment at the
// top of conventional memory. For a .COM binary, DOS would still allocate all
// remaining memory and load the program at the bottom of this allocation,
// defeating the point of changing the allocation strategy in the first place.
// One possible workaround: Temporarily claim all free conventional memory
// minus [reserve_bytes] for the currently running process, which leaves no
// other place but the top of RAM for DOS to place the TSR.
//
// Except that [reserve_bytes] must also include an undefined amount of bytes
// for the TSR's environment segment. And this has to be a cruel joke:
// Processes must be able to add new environment variables, and the official
// environment segment is *obviously* the right place to put *all* the
// variables. And so, DOS is free to add any amount of bytes on top of the
// null-terminated environment string provided in the INT 21h AH=4Bh EXEC
// parameter block. DOSBox-X, for example, has been adding 1024 bytes by
// default since 2015 (commit 1a18812), because the use case of compiling
// FreeDOS required it.
// As a result, this approach of exactly spawning a TSR on top of conventional
// memory is *technically* impossible. We can sort of work around it though,
// thanks to the C standard library's [environ] abstraction that puts any new
// variables into different segments. By assuming that the child process will
// get exactly as many additional bytes as the parent did, we then only have to
// add our newly added environment variables, i.e., the strings in [environ]
// that don't point to the official environment segment, to the amount of
// memory we leave at the top. This works and is highly unlikely to ever break,
// but it's still a heuristic at the end of the day. If it *does* break, we can
// still reimplement all of INT 21h AH=4Bh to bypass DOS entirely – or just
// forget about this entire idea and go back to batch files. (Lame!)
//
// (Another approach would be to just spawn the process regularly and only
// relocate its exact memory to the top once the process called INT 21h AH=31h,
// together with fixing up any interrupt vectors it might have modified. This
// avoids the need for [reserve_bytes] and any upfront calculations, but is
// just as prone to break because interrupts are not the only way to hook into
// other programs…)
//
// It would appear as if we could even do this temporary reallocation in pure C
// with sbrk(), coreleft(), and brk(). However, Borland's C heap implementation
// secretly rounds up the break level to full kibibytes without any indication
// to the caller, ruining any hope of precise byte allocations.
//
// The final annoyance in all of this is caused by Borland's intermediate
// _LoadProg() function, which heap-allocates the command line and environment
// and frees those allocations at the end of the function. Turns out that
// additional C heap allocations don't go well with manipulations of the
// underlying DOS heap: Since we don't inform the C heap about our DOS memory
// block manipulation (because we can't, due to the kibibyte rounding),
// _LoadProg()'s malloc() calls might raise the break level, resetting the size
// of the DOS memory block back to the intended one and undoing all our
// manipulation work.
// The only stable fix: Replace _LoadProg(), allocate and prepare the two
// buffers ourselves before manipulating the DOS process memory allocation, and
// call the low-level _spawn() function when we need it. Oh well, this at least
// allows us to simplify _LoadProg() to its essentials here. This way, our
// custom TSR spawn function can have a "sane" parameter list – no need to
// conform to POSIX when we don't have to.

// The MCB of each allocation immediately precedes the allocated segment.
inline dos_mcb_t __seg* near mcb_for(seg_t sgm) {
	return reinterpret_cast<dos_mcb_t __seg *>(sgm - (sizeof(dos_mcb_t) >> 4));
}

int near spawn_adjacent(const char *path, const char *args, const SpawnEnv *env)
{
	char dos_args[128]; // DOS PSP limit
	const uint16_t args_len = strlen(args);
	if(args_len > (sizeof(dos_args) - 2)) {
		errno = E2BIG;
		return -2;
	}
	dos_args[0] = args_len;
	memcpy(&dos_args[1], args, args_len);
	dos_args[args_len + 1] = 0x0D;

	// Depending on the Borland C runtime out of pure convenience here. Would
	// need to be replaced or reimplemented when migrating to other compilers.
	//
	// The only gotcha: _spawn() returns either -1 on error or the 8-bit return
	// code of the spawned process. This meant that the function had to return
	// `int`, but Borland then didn't truncate the return code to [0; 255],
	// which potentially leaves garbage in the high byte.
	int ret = _spawn(path, dos_args, (env ? env->buf_aligned : nullptr));
	if(ret == -1) {
		return ret;
	}
	return (ret & 0xFF);
}

SpawnSpacer pascal spawn_claim_memory_minus(
	uint32_t payload_bytes,
	unsigned int process_count,
	unsigned int max_binary_fn_len,
	const SpawnEnv *env
)
{
	SpawnSpacer ret;
	SpawnSpacer err;
	err.set_error();

	char __seg* env_seg = reinterpret_cast<dos_psp_t __seg *>(_psp)->environ;
	ret.prev_paras = mcb_for(_psp)->size;

	// Ensure that environment segments can fit an extra [max_binary_fn_len].
	// Calculation taken from the DOS 6 kernel, where this is actually an
	// issue that would prevent this whole thing from working.
	unsigned int env_seg_size = ((mcb_for(FP_SEG(env_seg))->size) * 16);
	char far *env_p = env_seg;
	do {
		env_p += (strlen(env_p) + 1);
	} while(*env_p != '\0');
	env_p++;
	const unsigned int env_seg_size_min = (
		FP_OFF(env_p) + 2 + max_binary_fn_len + 15
	);
	if(env_seg_size_min > env_seg_size) {
		env_seg_size = env_seg_size_min;
	}

	// Get the maximum amount of conventional RAM this process could take up by
	// asking for the maximum possible segment size. Will already reallocate
	// [_psp] to the returned size!
	uint16_t extended_paras = setblock(_psp, 0xFFFF);
	if((extended_paras == 0xFFFF) || (errno != ENOMEM)) {
		return err;
	}

	// Guess the amount of paragraphs that DOS requires for each process, which
	// includes
	// • the MCB of its environment block (+1),
	// • the size of our own environment block (+[env_seg_size]),
	// • any bytes added through [environ],
	// • and the MCB for the process itself (+1).
	uint16_t dos_process_paras = (1 + ((env_seg_size + 15) >> 4) + 1);
	if(env) {
		dos_process_paras += ((env->added_bytes + 15) >> 4);
	}

	// Calculating the final reserve size in 32 bits also includes an overflow
	// check for [payload_bytes].
	uint32_t top_paras = (
		(process_count * dos_process_paras) + ((payload_bytes + 15) >> 4)
	);
	if(top_paras > (extended_paras - ret.prev_paras)) {
		errno = ENOMEM;
		return err;
	}

	if(setblock(_psp, (extended_paras - top_paras)) != -1) {
		return err;
	}
	return ret;
}

void SpawnSpacer::release(void)
{
	if(*this) {
		return;
	}

	// Restore original memory boundaries
	setblock(_psp, prev_paras);
	set_error();
}

int near spawn_at_top(
	const char *path,
	const char *args,
	const uint32_t reserve_bytes,
	const SpawnEnv *env
)
{
	SpawnSpacer spacer = spawn_claim_memory_minus(
		reserve_bytes, 1, strlen(path), env
	);
	if(spacer) {
		return -1;
	}
	int ret = spawn_adjacent(path, args, env);
	spacer.release();
	return ret;
}
// ------------

int spawn_at_top_report(
	const uint32_t reserve_bytes,
	const char* path,
	const char *args,
	const SpawnEnv *env
)
{
	return report(spawn_at_top(path, args, reserve_bytes, env), path);
}

int spawn_adjacent_report(
	const char* path, const char *args, const SpawnEnv *env
)
{
	return report(spawn_adjacent(path, args, env), path);
}
