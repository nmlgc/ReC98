/* ReC98
 * -----
 * MDRV2 functions
 */

#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <malloc.h>
#include <string.h>

#define	MDRV2 0xf2
#define MDRV2_CALL(func) { \
	__asm { mov	ah, func } \
	__asm { int	MDRV2 } \
}

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

extern char mdrv2_have_board;

static void near pascal mdrv2_load(const char *fn, char func)
{
	if(mdrv2_have_board) {
		int handle = open(fn, O_BINARY | O_RDONLY);
		int length = filelength(handle);
		int sgm;
		int ofs;
		void far *block;

		block = farmalloc(length);
		sgm = FP_SEG(block);
		ofs = FP_OFF(block);

		__asm {
			push	ds
			mov	ax, 0x3F00
			mov	bx, handle
			mov	cx, length
			mov	ds, sgm
			mov	dx, ofs
			int	0x21
			pop	ds
		}
		close(handle);
		__asm {
			push	ds
			mov	ah, func
			mov	ds, sgm
			mov	si, ofs
			int	MDRV2
			pop	ds
		}
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
	if(mdrv2_have_board) {
		MDRV2_CALL(MDRV2_MPLAY);
	}
}

void mdrv2_bgm_stop(void)
{
	if(mdrv2_have_board) {
		MDRV2_CALL(MDRV2_MSTOP);
	}
}

void mdrv2_bgm_fade_out_nonblock(void)
{
	if(mdrv2_have_board) {
		MDRV2_CALL(MDRV2_MFADE_OUT_NONBLOCK);
	}
}

void mdrv2_bgm_fade_out_block(void)
{
	if(mdrv2_have_board) {
		MDRV2_CALL(MDRV2_MFADE_OUT_BLOCK);
	}
}

void mdrv2_bgm_fade_in(void)
{
	if(mdrv2_have_board) {
		MDRV2_CALL(MDRV2_MFADE_IN);
	}
}

int mdrv2_check_board(void)
{
	MDRV2_CALL(MDRV2_CHECK_BOARD);
	__asm { mov	mdrv2_have_board, al }
	return mdrv2_have_board;
}

void mdrv2_se_play(int se)
{
	if(se && mdrv2_have_board) {
		se += MDRV2_EPLAY << 8;
		__asm {
			mov	ax, se
			int	MDRV2
		}
	}
}
