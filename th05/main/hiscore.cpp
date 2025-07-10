// Dumb micro-optimized raw INT 21h implementation of GENSOU.SCR for MAIN.EXE
// --------------------------------------------------------------------------
// ZUN bloat: Can be fully replaced with the regular implementation.

#pragma option -zCSCORE_TEXT -k-

#include "th04/formats/scoredat/scoredat.hpp"
#include "th05/playchar.h"
#include "th04/main/rank.hpp"
#include "th04/shiftjis/fnshared.hpp"
#include "th01/rank.h"
#include "platform/x86real/flags.hpp"
#include "decomp.hpp"
#include "x86real.h"

#undef SCOREDAT_FN
extern const char near SCOREDAT_FN[];

inline void seek_to_playchar_and_rank(void) {
	// DOS file seek
	_AH ^= _AH;
	_AL = playchar;
	_AX = (_AX * RANK_COUNT);
	_AL += rank;
	_DX = (_AX * sizeof(scoredat_section_t));
	_CX ^= _CX;
	_AX = 0x4200;
	geninterrupt(0x21);
}

// Loads the score data for the current global player character and the global
// [rank] into [hi]. Leaves [hi] unmodified if [SCOREDAT_FN] could not be
// loaded, and with undefined contents if decoding failed.
void near scoredat_load_for_cur(void)
{
	// DOS file open
	_AX = 0x3D00;
	_DX = FP_OFF(SCOREDAT_FN);
	geninterrupt(0x21);
	if(FLAGS_CARRY) {
		optimization_barrier();
		return;
	}
	_BX = _AX;

	seek_to_playchar_and_rank();

	// DOS file read
	_AH = 0x3F;
	_DX = FP_OFF(&hi);
	_CX = sizeof(hi);
	geninterrupt(0x21);

	// DOS file close
	_AH = 0x3E;
	geninterrupt(0x21);

	scoredat_decode();
}

// Saves [hi] to the score file, replacing the section for the current global
// character and the current [rank].
void near scoredat_save_cur(void)
{
	scoredat_encode();

	// DOS file open (read and write)
	_AX = 0x3D02;
	_DX = FP_OFF(SCOREDAT_FN);
	geninterrupt(0x21);
	_BX = _AX; // ZUN landmine: No error handling

	seek_to_playchar_and_rank();

	// DOS file write
	_AH = 0x40;
	_DX = FP_OFF(&hi);
	_CX = sizeof(hi);
	geninterrupt(0x21);

	// DOS file close
	_AH = 0x3E;
	geninterrupt(0x21);

	scoredat_decode();
}
