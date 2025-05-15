/* ReC98
 * -----
 * MDRV2 functions
 */

#include <dos.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "platform/x86real/spawn.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/snd/mdrv2.h"

#define MDRV2_FN "MDRV98.COM"
#define MDRV2_MAGIC "Mdrv2System"

typedef enum {
	MDRV2_MPLAY = 0x00,
	MDRV2_MFADE_OUT_BLOCK = 0x01,
	MDRV2_MFADE_OUT_NONBLOCK = 0x02,
	MDRV2_MSTOP = 0x03,
	MDRV2_EPLAY = 0x04,
	MDRV2_MSET = 0x06,
	MDRV2_ESET = 0x07,
	MDRV2_CHECK_BOARD = 0x09,
	MDRV2_MFADE_IN = 0x0F,
} mdrv2_func_t;

static const uint8_t MDRV2 = 0xF2;

inline int16_t mdrv2_segment(void) {
	// 0000:((0xF2 * 4) + 2)
	return peek(0, ((MDRV2 * sizeof(void far *)) + sizeof(void near *)));
}

inline uint16_t mdrv2_call(mdrv2_func_t func) {
	_AH = func;
	geninterrupt(MDRV2);
	return _AX;
}

static int8_t mdrv2_active = false; // ACTUAL TYPE: bool

bool16 mdrv2_resident(void)
{
	char s1[sizeof(MDRV2_MAGIC)];
	const char MAGIC[] = MDRV2_MAGIC;
	char far *magicp = reinterpret_cast<char far *>(
		(static_cast<uint32_t>(mdrv2_segment()) << 16) + 0x102
	);

	for(int i = 0; i < sizeof(s1); i++) {
		s1[i] = magicp[i];
	}
	if(strcmp(s1, MAGIC) != 0) {
		return false;
	}
	return true;
}

void near mdrv2_load(const char *fn, char func)
{
	if(mdrv2_active) {
		file_ropen(fn);
		int length = file_size();
		seg_t block_seg;
		uint16_t block_off;
		void far *block;

		block = farmalloc(length);
		block_seg = FP_SEG(block);
		block_off = FP_OFF(block);

		file_read(block, length);
		file_close();

		_asm {
			push	ds
			mov	ah, func
			mov	ds, block_seg
			mov	si, block_off
		}
		geninterrupt(MDRV2);
		_asm { pop	ds; }

		farfree(block);
	}
}

void mdrv2_bgm_load(const char *fn)
{
	mdrv2_load(fn, MDRV2_MSET);
}

void mdrv2_se_load(const char *fn)
{
	mdrv2_load(fn, MDRV2_ESET);
}

void mdrv2_bgm_play(void)
{
	if(mdrv2_active) {
		mdrv2_call(MDRV2_MPLAY);
	}
}

void mdrv2_bgm_stop(void)
{
	if(mdrv2_active) {
		mdrv2_call(MDRV2_MSTOP);
	}
}

void mdrv2_bgm_fade_out_nonblock(void)
{
	if(mdrv2_active) {
		mdrv2_call(MDRV2_MFADE_OUT_NONBLOCK);
	}
}

void mdrv2_bgm_fade_out_block(void)
{
	if(mdrv2_active) {
		mdrv2_call(MDRV2_MFADE_OUT_BLOCK);
	}
}

void mdrv2_bgm_fade_in(void)
{
	if(mdrv2_active) {
		mdrv2_call(MDRV2_MFADE_IN);
	}
}

int mdrv2_enable_if_board_installed(void)
{
	mdrv2_active = mdrv2_call(MDRV2_CHECK_BOARD);
	return mdrv2_active;
}

void mdrv2_se_play(int se)
{
	if(se && mdrv2_active) {
		se += (MDRV2_EPLAY << 8);
		_asm { mov	ax, se; } // Prevent [se] from being put into a register
		geninterrupt(MDRV2);
	}
}

static const uint8_t MDRV2_DRIVER_KIB = 16; // Assumed by the ver 3.4F binary.
static const uint8_t MDRV2_RESERVE_KIB_MAX = (64 - MDRV2_DRIVER_KIB);

int mdrv2_spawn(uint8_t bgm_data_kib)
{
	if((bgm_data_kib < 1) || (bgm_data_kib > MDRV2_RESERVE_KIB_MAX)) {
		printf(
			"%s: MDRV2 reserve size must be between 1 and %d KiB, got %d KiB",
			_argv[0], MDRV2_RESERVE_KIB_MAX, bgm_data_kib
		);
		return -1;
	}
	uint32_t reserve = ((MDRV2_DRIVER_KIB + bgm_data_kib) * 1024L);
	char param_m[5] = "-M\0\0";
	param_m[2] = ('0' + (bgm_data_kib / 10));
	param_m[3] = ('0' + (bgm_data_kib % 10));
	return spawn_at_top_report(reserve, MDRV2_FN, param_m);
}

int mdrv2_remove(void)
{
	return spawn_adjacent_report(MDRV2_FN, "-R");
}
