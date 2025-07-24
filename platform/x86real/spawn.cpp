#pragma option -zC_TEXT

#include <alloc.h>
#include <dos.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "platform/x86real/dos.hpp"
#include "platform/x86real/flags.hpp"
#include "platform/x86real/spawn.hpp"

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

class Subprocess {
private:
	char far* env;
	char __seg* env_aligned;
	int16_t env_added_bytes;
	char args[128]; // DOS PSP limit

public:
	Subprocess(const char* args);
	~Subprocess() {
		if(env) {
			free(env);
		}
	}

	int near spawn_adjacent(const char* path);
	int near spawn_at_top(const char* path, const uint32_t reserve_bytes);
};

Subprocess::Subprocess(const char *args_) :
	env(nullptr), env_aligned(nullptr)
{
	// Build command line
	// ------------------

	const uint16_t args_len = strlen(args_);
	if(args_len > (sizeof(this->args) - 2)) {
		errno = E2BIG;
		return;
	}
	this->args[0] = args_len;
	memcpy(&this->args[1], args_, args_len);
	this->args[args_len + 1] = 0x0D;
	// ------------------

	// Build environment
	// -----------------

	char __seg* env_seg = reinterpret_cast<dos_psp_t __seg *>(_psp)->environ;
	char* far* src_p;

	uint16_t env_orig_bytes = 1; 	// original, including the list terminator
	this->env_added_bytes = 0;   	// added since startup
	for(src_p = environ; *src_p != nullptr; src_p++) {
		char far* p = *src_p;
		uint16_t p_len = (strlen(p) + 1);
		if(static_cast<char __seg *>(p) != env_seg) {
			this->env_added_bytes += p_len;
		} else {
			env_orig_bytes += p_len;
		}
	}

	// The EXEC block only stores a segment-only pointer, so we need to
	// paragraph-align it.
	this->env = reinterpret_cast<char far *>(malloc(
		env_orig_bytes + this->env_added_bytes + 15
	));
	if(!this->env) {
		errno = ENOMEM;
		return;
	}
	this->env_aligned = reinterpret_cast<char __seg *>(
		FP_SEG(this->env) + (FP_OFF(this->env + 15) >> 4)
	);

	char far* dst_p = this->env_aligned;
	for(src_p = environ; *src_p != nullptr; src_p++) {
		dst_p = stpcpy(dst_p, *src_p);
		*(dst_p++) = '\0';
	}
	*(dst_p++) = '\0';
	// -----------------
}

// The MCB of each allocation immediately precedes the allocated segment.
inline dos_mcb_t __seg* near mcb_for(seg_t sgm) {
	return reinterpret_cast<dos_mcb_t __seg *>(sgm - (sizeof(dos_mcb_t) >> 4));
}

int near Subprocess::spawn_adjacent(const char *path)
{
	if(!env) {
		return -1;
	}

	// Depending on the Borland C runtime out of pure convenience here. Would
	// need to be replaced or reimplemented when migrating to other compilers.
	return _spawn(path, dos_args, env_aligned);
}

int near Subprocess::spawn_at_top(
	const char *path, const uint32_t reserve_bytes
)
{
	if(!env) {
		return -1;
	}

	char __seg* env_seg = reinterpret_cast<dos_psp_t __seg *>(_psp)->environ;
	uint16_t prev_paras = mcb_for(_psp)->size;

	// Get the maximum amount of conventional RAM this process could take up by
	// asking for the maximum possible segment size. Will already reallocate
	// [_psp] to the returned size!
	uint16_t extended_paras = setblock(_psp, 0xFFFF);
	if((extended_paras == 0xFFFF) || (errno != ENOMEM)) {
		return -1;
	}

	// Calculating the final reserve size in 32 bits also includes an overflow
	// check for [reserve_bytes].
	uint32_t top_paras = (
		1 +                               	// Environment MCB
		(mcb_for(FP_SEG(env_seg))->size) +	// Original environment
		((env_added_bytes + 15) >> 4) +   	// New environment
		1 +                               	// TSR MCB
		((reserve_bytes + 15) >> 4)       	// TSR itself
	);
	if(top_paras > (extended_paras - prev_paras)) {
		errno = ENOMEM;
		return -1;
	}

	if(setblock(_psp, (extended_paras - top_paras)) != -1) {
		return -1;
	}

	int ret = spawn_adjacent(path);

	// Restore original memory boundaries
	setblock(_psp, prev_paras);

	return ret;
}
// ------------

int spawn_at_top_report(
	const uint32_t reserve_bytes, const char* path, const char *args
)
{
	Subprocess subprocess(args);
	return report(subprocess.spawn_at_top(path, reserve_bytes), path);
}

int spawn_adjacent_report(const char* path, const char *args)
{
	Subprocess subprocess(args);
	return report(subprocess.spawn_adjacent(path), path);
}
