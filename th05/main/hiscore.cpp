// Dumb micro-optimized raw INT 21h implementation of GENSOU.SCR for MAIN.EXE
// --------------------------------------------------------------------------
// ZUN bloat: Can be fully replaced with the regular implementation.

#pragma option -zCSCORE_TEXT -k-

#include "th04/main/hiscore.hpp"
#include "th04/formats/scoredat/scoredat.hpp"
#include "th05/playchar.h"
#include "th04/main/stage/stage.hpp"
#include "th04/main/rank.hpp"
#include "th04/main/slowdown.hpp"
#include "th04/gaiji/gaiji.h"
#include "th04/common.h"
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

// sizeof() is not supported inside ASM syntax, but compile-time constants are.
static const int16_t SIZEOF_NAME = sizeof(hi.score.g_name[0]);

void near hiscore_continue_enter_raw(void)
{
	#define _DX static_cast<int16_t>(_DX) // Entered place

	_DX = (SCOREDAT_PLACES - 1);
	do {
		_SI = _DX;

		static_assert(SCORE_DIGITS == 8);
		_SI <<= 3; // *= SCORE_DIGITS
		_SI += FP_OFF(hi.score.g_score[0].digits + (SCORE_DIGITS - 1));
		_BX = FP_OFF(&score.digits[SCORE_DIGITS - 1]);
		_CX = SCORE_DIGITS;
		digit_loop: asm {
			// Explicitly comparing and subtracting unsigned bytes avoids the
			// sorting bug with overflowed scores that TH04 suffers from.
			// (Could have been done in C too, though…)
			mov 	al, [si]
			sub 	al, gb_0
			cmp 	al, [bx]
			jb  	next
			ja  	found
			dec 	bx
			dec 	si
			loop	digit_loop;
		}
next:
		_DX--;
	} while(!FLAGS_SIGN);
found:
	_DX++;

	extern int8_t unnecessary_shift_place_copy;
	unnecessary_shift_place_copy = _DX;

	if(static_cast<uint16_t>(_DX) >= SCOREDAT_PLACES) {
		return;
	}

	// Shift
	asm { push	ds; }
	asm { pop 	es; }
	for(_BX = (SCOREDAT_PLACES - 2); static_cast<int16_t>(_BX) >= _DX; _BX--) {
		asm { imul di, bx, SIZEOF_NAME }
		_SI = _DI;
		_SI += FP_OFF(hi.score.g_name[0]);
		_DI += FP_OFF(hi.score.g_name[1]);
		static_assert(SCOREDAT_NAME_LEN == (2 * sizeof(uint32_t)));
		MOVSD;
		MOVSD;

		_DI = _BX;
		_DI <<= 3; // *= SCORE_DIGITS
		_SI = _DI;
		_SI += FP_OFF(hi.score.g_score[0].digits);
		_DI += FP_OFF(hi.score.g_score[1].digits);
		static_assert(SCORE_DIGITS == (2 * sizeof(uint32_t)));
		MOVSD;
		MOVSD;

		hi.score.g_stage[_BX + 1] = hi.score.g_stage[_BX];
	}

	// Insert "CONTINUE" entry
	extern const gaiji_th04_t gCONTINUE[SCOREDAT_NAME_LEN + 1];

	asm { imul di, dx, SIZEOF_NAME }
	_DI += FP_OFF(hi.score.g_name[0]);
	_SI = FP_OFF(gCONTINUE);
	static_assert(SCOREDAT_NAME_LEN == (2 * sizeof(uint32_t)));
	MOVSD;
	MOVSD;

	_DI = _DX;
	_DI <<= 3; // *= SCORE_DIGITS
	_DI += FP_OFF(hi.score.g_score[0].digits);
	_SI = FP_OFF(score.digits);
	static_assert(SCORE_DIGITS == (2 * sizeof(uint32_t)));
	MOVSD;
	MOVSD;

	_DI -= SCORE_DIGITS;
	_CX = SCORE_DIGITS;
	digit_offset_loop: {
		*reinterpret_cast<unsigned char __ds *>(_DI++) += gb_0;
		asm { loop digit_offset_loop }
	}

	_AL = stage_id;
	if(_AL == STAGE_EXTRA) {
		_AL ^= _AL;
	}
	_DI = _DX;
	hi.score.g_stage[_DI] = (gb_1 + _AL);

	scoredat_save_cur();

	#undef _DX
}

void near hiscore_continue_enter(void)
{
	if(turbo_mode) {
		hiscore_continue_enter_raw();
	}
}

#pragma codestring "\x90"
