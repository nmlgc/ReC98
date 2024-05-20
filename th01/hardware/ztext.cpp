/* ReC98
 * -----
 * Useless reimplementations of master.lib text functions, half of which are
 * unused anyway.
 */

#pragma option -1 -Z-

#include <mbctype.h>
#include <mbstring.h>
#include <stdarg.h>
#include <stdio.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "shiftjis.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/hardware/ztext.hpp"

static int8_t unused[256]; // ZUN bloat

void z_text_init(void)
{
	union REGS regs;
	regs.h.ah = 0xE; // "Set single display area"
	regs.w.dx = 0;
	int86(0x18, &regs, &regs);
	z_text_25line();
	z_text_systemline_hide();
	z_text_setcursor(CURSOR_HIDE);
	z_text_clear();
	z_text_show();
}

void z_text_exit(void)
{
	z_text_25line();
	z_text_systemline_show();
	z_text_setcursor(CURSOR_BLOCK);
	z_text_clear();
	z_text_show();
}

void z_text_25line(void)
{
	z_text_print("\x1B[>3l");
}

void z_text_20line(void)
{
	z_text_print("\x1B[>3h");
}

void z_text_systemline_show(void)
{
	z_text_print("\x1B[>1l");
}

void z_text_systemline_hide(void)
{
	z_text_print("\x1B[>1h");
}

void z_text_clear(void)
{
	z_text_print("\x1B[2J");
}

void z_text_show(void)
{
	union REGS regs;
	regs.h.ah = 0xC;
	int86(0x18, &regs, &regs);
}

void z_text_hide(void)
{
	union REGS regs;
	regs.h.ah = 0xD;
	int86(0x18, &regs, &regs);
}

void z_text_setcursor(z_text_cursor_t type)
{
	_BX = _peekb_(0, 0x53B); // Text mode line height
	outportb(0x62, 0x4B); // CSRFORM
	outportb(0x60, (_BL | 0x80));
	switch(type) {
		case CURSOR_HIDE:
			outportb(0x60, 0x9F);
			break;
		case CURSOR_BLOCK:
			outportb(0x60, 0x80);
			break;
		case CURSOR_UNDERLINE:
			outportb(0x60, (_BL + 0x7D));
			break;
	}
	outportb(0x60, ((_BL << 3) + 2));
}

void z_text_locate(char x, char y)
{
	union REGS regs;
	regs.h.cl = 0x10;
	regs.h.ah = 3;
	regs.h.dh = y;
	regs.h.dl = x;
	int86(0xDC, &regs, &regs);
}

inline uint8_t* tram_jis(uint16_t offset) {
	return reinterpret_cast<uint8_t *>(MK_FP(SEG_TRAM_JIS, offset));
}

inline tram_atrb2* tram_atrb(uint16_t offset) {
	return reinterpret_cast<tram_atrb2 *>(MK_FP(SEG_TRAM_ATRB, offset));
}

void z_text_putsa(tram_x_t x, tram_y_t y, int z_atrb, const sshiftjis_t *str)
{
	jis_t codepoint;
	int p = (((y * text_width()) + x) * 2);
	tram_atrb2 hw_atrb = 1;

	if(z_atrb & Z_ATRB_BLUE) {
		hw_atrb += 0x20;
	}
	if(z_atrb & Z_ATRB_RED) {
		hw_atrb += 0x40;
	}
	if(z_atrb & Z_ATRB_GREEN) {
		hw_atrb += 0x80;
	}
	if(z_atrb & Z_ATRB_VLINE) {
		hw_atrb += 0x10;
	}
	if(z_atrb & Z_ATRB_UNDERLINE) {
		hw_atrb += TX_UNDERLINE;
	}
	if(z_atrb & Z_ATRB_REVERSE) {
		hw_atrb += TX_REVERSE;
	}
	if(z_atrb & Z_ATRB_BLINK) {
		hw_atrb += TX_BLINK;
	}
	hw_atrb += (hw_atrb << 8);
	while(str[0]) {
		if(_ismbblead(str[0])) {
			codepoint = _mbcjmstojis(
				(str[0] << 8) + static_cast<uint8_t>(str[1])
			);
			str += 2;
			if((codepoint >= 0x2921) && (codepoint <= 0x2B7E)) {
				tram_jis(p)[0] = (((codepoint >> 8) + 0xE0) | 0x80);
				tram_jis(p)[1] = codepoint;
				tram_atrb(p)[0] = hw_atrb;
			} else if(x == (text_width() - 1)) {
				reinterpret_cast<jis_t *>(tram_jis(p))[0] = ' ';
				tram_atrb(p)[0] = hw_atrb;
			} else {
				tram_jis(p)[0] = ((codepoint >> 8) + 0xE0);
				tram_jis(p)[1] = codepoint;
				tram_jis(p)[2] = (((codepoint >> 8) + 0xE0) | 0x80);
				tram_jis(p)[3] = codepoint;

				tram_atrb(p)[0] = hw_atrb;
				tram_atrb(p)[1] = hw_atrb;
				p += 2;
				x++;
			}
		} else {
			reinterpret_cast<jis_t *>(tram_jis(p))[0] = *reinterpret_cast<
				const uint8_t *
			>(str++);
			tram_atrb(p)[0] = hw_atrb;
		}
		p += 2;
		if(++x >= text_width()) {
			break;
		}
	}
}

void z_text_vputsa(
	tram_x_t x, tram_y_t y, int z_atrb, const sshiftjis_t *fmt, ...
)
{
	char str[256];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	z_text_putsa(x, y, z_atrb, str);
}

void z_text_print(const char *str)
{
	union REGS regs;
	regs.h.cl = 0x10;
	regs.h.ah = 0;
	while(*str) {
		regs.h.dl = *(str++);
		int86(0xDC, &regs, &regs);
	}
	outportb(0x64, 0); // VSync interrupt trigger
}
