/// GAME.BAT replica
/// ----------------

#pragma option -zCPLATFORM_TEXT -k-

#include "platform/x86real/spawn.hpp"
#include "platform/x86real/dos.hpp"
#include "platform/x86real/doserror.hpp"
#include "libs/master.lib/master.hpp"
#if (GAME == 5)
#include "th05/resident.hpp"
#elif (GAME == 4)
#include "th04/resident.hpp"
#elif (GAME == 3)
#include "th03/resident.hpp"
#include "libs/sprite16/sprite16.h"
#include <mem.h>
#elif (GAME == 2)
#include "th02/resident.hpp"
#endif
#include "th02/snd/snd.h"
#include "th01/pc98/entry.hpp"
#include "x86real.h"
#include <stddef.h>
#include <string.h>
#include <process.h>

#if (defined(__TURBOC__) && defined(__MSDOS__))
// Turbo C++ implements signal(2) for `SIGSEGV` and `SIGILL` by hooking INT 5
// and INT 6 respectively. You'd think that its implementation would then
// install an atexit() handler to restore the specific hooked interrupt vector
// at shutdown. However, swapping process binaries via execl() ends up calling
// _cexit(), which unconditionally resets *all* vectors that signal() can
// possibly hook to the values they had during startx(), *even if your program
// never calls signal()*. As a result of this choice, execl() would not only
// remove ZUN's INT 5 and INT 6 handlers if they were changed by a self-spawned
// ZUNINIT process, but also leak said process – INT 6 will have received its
// original handler, and the `-r` command can no longer locate and validate its
// PSP via the system-wide INT 6 handler.
// Thankfully, C0 exports its saved interrupt vector pointers, so we can just
// overwrite them here. The fix requires overwrites at two places:
// 1) After spawning ZUNINIT to preserve its handlers across process switches
// 2) Before shutdown to turn Borland's automatic restoration into a no-op.
//    Otherwise, it would reapply the ZUNINIT handlers that now point to
//    freed memory.
extern "C" void far *_Int5Vector;
extern "C" void far *_Int6Vector;

void near borland_signal_workaround(void)
{
	_AX = 0x3505;
	geninterrupt(0x21);
	_Int5Vector = MK_FP(_ES, _BX);
	_AX = 0x3506;
	geninterrupt(0x21);
	_Int6Vector = MK_FP(_ES, _BX);
}
#endif

static const char ZUN_COM[] = "zun.com";

// A little size optimization
int near pascal zuncom_spawn(const char near *args)
{
	return spawn_adjacent_report(ZUN_COM, args);
}

#if (GAME >= 4)
#define ZUNCOM_RESIDENT	"-s"
#define ZUNCOM_ZUNINIT 	"-i"
#define ZUNCOM_ONGCHK  	"-o"
#elif (GAME == 3)
#define ZUNCOM_RESIDENT	"-5"
#define ZUNCOM_ZUNINIT 	"-2"
#define ZUNCOM_ONGCHK  	"-1"
#define ZUNCOM_ZUNSOFT 	"-3"
#elif (GAME == 2)
#define ZUNCOM_RESIDENT	"zun_res"
#define ZUNCOM_ZUNINIT 	"zuninit"
#define ZUNCOM_ONGCHK  	"ongchk"
#define ZUNCOM_ZUNSOFT 	"zunsoft.com"
#endif

// Nobody would ever mod *those* beyond hex-editing, right???
#if (GAME == 5)
static const uint16_t ZUNINIT_SIG_OFF = 0x1EA;
#elif (GAME == 4)
static const uint16_t ZUNINIT_SIG_OFF = 0x20A;
#else
static const uint16_t ZUNINIT_SIG_OFF = 0x23D;
#endif

enum shutdown_flag_t {
	SHUTDOWN_NONE = 0x00,
	SHUTDOWN_RESIDENT = 0x01,
	SHUTDOWN_ZUNINIT = 0x02,
	SHUTDOWN_SPRITE16 = 0x04,
	SHUTDOWN_PMD = 0x08,
	SHUTDOWN_MMD = 0x10,
};

resident_t __seg* near resident_get(void)
{
	return ResData<resident_t>::exist(RES_ID);
}

enum tsr_flag_t {
	TSR_OPTIONAL = 0x01,
	TSR_SPAWNING = 0x80, // Are we actually spawning this TSR?
};

struct near TSR {
	const char near *fn;
	const char near *spawn_args;
	const char near *remove_args;

	// Checks and returns `true` if this TSR is already resident. Can also
	// perform any run-time initialization of other fields.
	bool (near pascal *near init)(TSR near &this_tsr);

	uint8_t shutdown_flag;

	// Interrupt hooked by this TSR. The segment part of its handler must
	// correspond to the TSR's PSP.
	uint8_t intvector;

	uint8_t flags;

	int pascal near spawn(const char near *args);
};

int pascal near TSR::spawn(const char near *args)
{
	return spawn_adjacent_report(fn, args);
}

// INTvector set program
// ---------------------

bool pascal near tsr_zuninit_init(TSR near &)
{
	// 'UZPN' in memory order
	if(0x4E505A55UL == *reinterpret_cast<uint32_t far *>(
		MK_FP(intvector_segment(6), ZUNINIT_SIG_OFF)
	)) {
		return true;
	}
	return false;
}

TSR tsr_zuninit = {
	ZUN_COM,
	ZUNCOM_ZUNINIT,
	(ZUNCOM_ZUNINIT " -r"),
	tsr_zuninit_init,
	SHUTDOWN_ZUNINIT,
	6,
	TSR_OPTIONAL,
};
// ---------------------

// SPRITE16
// --------

#if (GAME == 3)
static const char SPRITE16_SIG[] = "SPRITE16\0\x04";

bool pascal near tsr_sprite16_init(TSR near &)
{
	if(!memcmp(
		MK_FP(intvector_segment(SPRITE16), 0x102),
		SPRITE16_SIG,
		(sizeof(SPRITE16_SIG) - 1)
	)) {
		return true;
	}
	return false;
}

TSR tsr_sprite16 = {
	ZUN_COM, "-4 -z", "-4 -r", tsr_sprite16_init, SHUTDOWN_SPRITE16, SPRITE16,
};
#endif
// --------

// MMD
// ---

#if (GAME == 2)
bool pascal near tsr_mmd_init(TSR near &)
{
	return snd_mmd_resident();
}

TSR tsr_mmd = {
	"mmd.com",
	"/D /K /M12",
	"/R",
	tsr_mmd_init,
	SHUTDOWN_MMD,
	MMD,
	TSR_OPTIONAL,
};
#endif
// ---

// PMD
// ---

#if (GAME >= 4)
#define PMD_ARGS_26 "/M8 /V0 /E2 /K /N  /P"
#define PMD_ARGS_86 "/M8 /V0 /E2 /K /N- /P"
#else
#define PMD_ARGS_26 "/M8 /V0 /E2 /K"
#define PMD_ARGS_86 "/M8 /V0 /E2 /K"
#endif

// Driver for each ONGCHK.COM return code
static const char near *PMD_DRIVERS[6] = {
	/* 0 */ "pmd.com",
	/* 1 */ "pmd.com",
	/* 2 */ "pmdb2.com",
	/* 3 */ "pmd86.com",
	/* 4 */ "pmdb2.com",
	/* 5 */ "pmd86.com",
};

bool pascal near tsr_pmd_init(TSR near &pmd)
{
	if(snd_pmd_resident()) {
		return true;
	}
	int ongchk_ret = zuncom_spawn(ZUNCOM_ONGCHK);
	if(ongchk_ret < 0) {
		exit(2);
	}
	pmd.fn = PMD_DRIVERS[ongchk_ret];
	pmd.spawn_args = ((ongchk_ret <= 1) ? PMD_ARGS_26 : PMD_ARGS_86);
	return false;
}

TSR tsr_pmd = { nullptr, nullptr, "/R", tsr_pmd_init, SHUTDOWN_PMD, PMD };
// ---

// Compared to TH01's sole MDRV2 TSR, the big challenge in TH02-TH05 is that
// all these utility programs are bundled into the single ZUN.COM binary, which
// is larger than the ZUNINIT INTvector TSR. This creates two problems when
// trying to apply the TH01 strategy of individually spawning TSRs at the top
// of conventional memory:
//
// 1) If we reserve just the expected resident size of the TSR, we couldn't
//    even spawn ZUN.COM because there's not enough free memory left.
// 2) If we reserve the size of ZUN.COM, we leave an undesirable memory hole at
//    the top of conventional RAM after ZUNINIT terminates – at least 17,364
//    bytes with the original ZUN.COM that ships with TH05. This is too little
//    for either PMD or SPRITE16.
//
// If we *only* need to spawn ZUNINIT, 2) is the best we can do. But since we
// typically have to spawn more TSRs than that, we can avoid memory holes by
// pre-calculating the total amount of required resident memory for all TSRs,
// allocating a single spacer, and then spawning all of them in order.
// Comparing the total intended reserve size to the size of the involved
// binaries then completes the solution.
struct TSRBundle {
	uint32_t min_size;
	uint32_t reserve_size;
	unsigned int max_binary_fn_len;
	int count;

	TSRBundle() {
		_EAX ^= _EAX;
		min_size = _EAX;
		reserve_size = _EAX;
		max_binary_fn_len = _EAX;
		count = _EAX;
	}

	uint32_t spacer_size(void) const {
		return ((min_size > reserve_size) ? min_size : reserve_size);
	}
};

TSR near *tsrs[] = {
	&tsr_zuninit,
#if (GAME == 3)
	&tsr_sprite16,
#endif
#if (GAME == 2)
	&tsr_mmd,
#endif
	&tsr_pmd,
};

static const int TSR_COUNT = (sizeof(tsrs) / sizeof(tsrs[0]));

int main_setup(int argc, const char *argv[])
{
	TSRBundle bundle;

	// If all required TSRs are already resident, we assume that the game was
	// started through GAME.BAT and directly launch into the OP entry point,
	// skipping TH05's gaiji upload and TH02/TH03's ZUN Soft logo.
	//
	// Note how we always skip TH04/TH05's memory check. The hardcoded values
	// in ZUN's ASM code assume that this binary hasn't been loaded yet, and
	// can easily return a false-positive wrong result, particularly with
	// TH04's 520 KB. mem_assign_dos() and its return value already comprises
	// all the memory checking we could ever need. If anything, we should add
	// an error message there.
	bool all_tsrs_resident = true;

	for(int i = 0; i < TSR_COUNT; i++) {
		TSR near& tsr = *tsrs[i];
		if(tsr.init(tsr)) {
			continue;
		}
		all_tsrs_resident = false;

		if(tsr.spawn(tsr.spawn_args)) {
			if(tsr.flags & TSR_OPTIONAL) {
				continue;
			} else {
				return (128 + i);
			}
		}
		tsr.flags |= TSR_SPAWNING;

		// No search through the entire DOS heap since we only care about the
		// resident segment, not the environment one...
		uint16_t tsr_paras = reinterpret_cast<dos_mcb_t __seg *>(
			FP_SEG(intvector_segment(tsr.intvector)) - 1
		)->size;
		tsr.spawn(tsr.remove_args);
#if (GAME == 3)
		// …*except* for SPRITE16, which allocates two additional DOS memory
		// blocks of 16 KB each. We could solve this by iterating through the
		// MCBs, but then we may (MS-DOS) or may not (DOSBox-X) also add the
		// environment segment, which our current architecture already deals
		// with inside spawn_claim_memory_minus(). So let's just special-case
		// this one for now; it's getting late and I want to get this done...
		if(tsr.intvector == SPRITE16) {
			tsr_paras += (1U + 1000U + 1U + 1000U);
		}
#endif
		if(tsr_paras == 0) {
			dos_print_error("Failed to determine TSR size of `", tsr.fn, "`");
			return (128 + i);
		}

		// Calculate the minimum amount of memory required to load the given
		// .COM binary. We later spawn all of the binaries we check the size
		// of, so we can skimp on error handling here.
		file_ropen(tsr.fn);

		// Don't forget the Program Segment Prefix. DOSBox also adds an extra
		// 256 bytes for stack memory.
		const uint16_t binary_size = (256 + 256 + file_size());
		file_close();

		// The difference between the previous binary and resident size will
		// have been deallocated by the time we will spawn this TSR, but the
		// previous binary might have still been larger than the new one.
		uint32_t min_size_new = (bundle.reserve_size + binary_size);
		if(min_size_new > bundle.min_size) {
			bundle.min_size = min_size_new;
		}
		bundle.reserve_size += (tsr_paras * 16U);

		unsigned int binary_fn_len = strlen(tsr.fn);
		if(binary_fn_len > bundle.max_binary_fn_len) {
			bundle.max_binary_fn_len = binary_fn_len;
		}
		bundle.count++;
	}

	// Safer than trying to load a potentially invalid pointer out of the .CFG
	// file.
	resident_t __seg *resident = resident_get();

	if(all_tsrs_resident && resident) {
		return main_op(argc, argv);
	}

#if (GAME == 5)
	// Gaiji
	if(zuncom_spawn("-g")) {
		return 1;
	}
#endif
	// Resident structure
	if(!resident) {
		if(zuncom_spawn(ZUNCOM_RESIDENT) == 1) {
			return 2;
		}
		resident = resident_get();

		// No `|=` as we want to reset the flags for safety reasons.
		resident->shutdown_flags = SHUTDOWN_RESIDENT;
	} else {
		resident->shutdown_flags = 0;
	}

	resident->pmd_fn = tsr_pmd.fn;
#if (GAME == 2)
	// All KAJA drivers free their own environment segment before TSRing, so we
	// can save a few bytes if we start PMD immediately after MMD. Decrementing
	// the TSR bundle count would also remove the MCB of PMD's main allocation
	// from the spacer size though, so we need to add it back to the reserve
	// size to compensate.
	if((tsr_pmd.flags & TSR_SPAWNING) && (tsr_mmd.flags & TSR_SPAWNING)) {
		bundle.count--;
		bundle.reserve_size += sizeof(dos_mcb_t);
	}
#endif

	if(bundle.count > 0) {
		SpawnSpacer spacer = spawn_claim_memory_minus(
			bundle.spacer_size(),
			bundle.count,
			bundle.max_binary_fn_len,
			nullptr
		);
		if(spacer) {
			return 3;
		}
		for(int i = 0; i < TSR_COUNT; i++) {
			TSR near& tsr = *tsrs[i];
			if(tsr.flags & TSR_SPAWNING) {
				if(tsr.spawn(tsr.spawn_args)) {
					return (128 + i);
				}
				resident->shutdown_flags |= tsr.shutdown_flag;
			}
		}
		spacer.release();
	}

#if (defined(__TURBOC__) && defined(__MSDOS__))
	if(tsr_zuninit.flags & TSR_SPAWNING) {
		borland_signal_workaround();
	}
#endif

#if (GAME <= 3)
	zuncom_spawn(ZUNCOM_ZUNSOFT);
#endif
	return main_op(argc, argv);
}

void main_shutdown(void)
{
	resident_t __seg *resident = resident_get();
	if(!resident) {
		return;
	}

	tsr_pmd.fn = resident->pmd_fn;
	for(int i = (TSR_COUNT - 1); i >= 0; i--) {
		TSR near& tsr = *tsrs[i];
		if(resident->shutdown_flags & tsr.shutdown_flag) {
			tsr.spawn(tsr.remove_args);
		}
	}
#if (defined(__TURBOC__) && defined(__MSDOS__))
	if(resident->shutdown_flags & SHUTDOWN_ZUNINIT) {
		borland_signal_workaround();
	}
#endif
	if(resident->shutdown_flags & SHUTDOWN_RESIDENT) {
		zuncom_spawn(ZUNCOM_RESIDENT " -r");
	}
}
