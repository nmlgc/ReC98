/* ReC98
 * -----
 * Useless reimplementations of master.lib text functions, half of which are
 * unused anyway.
 */

#include "th01/th01.h"

#include <mbctype.h>
#include <mbstring.h>
#include <stdarg.h>
#include <stdio.h>

#pragma option -1

extern char txesc_25line[];
extern char txesc_20line[];
extern char txesc_systemline_show[];
extern char txesc_systemline_hide[];
extern char txesc_clear[];

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
	z_text_print(txesc_25line);
}

void z_text_20line(void)
{
	z_text_print(txesc_20line);
}

void z_text_systemline_show(void)
{
	z_text_print(txesc_systemline_show);
}

void z_text_systemline_hide(void)
{
	z_text_print(txesc_systemline_hide);
}

void z_text_clear(void)
{
	z_text_print(txesc_clear);
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
	_BX = *(char*)MK_FP(0, 0x53B);
	OUTB(0x62, 0x4B); // CSRFORM
	OUTB(0x60, _BL | 0x80);
	switch(type) {
		case CURSOR_HIDE:
			OUTB(0x60, 0x9F);
			break;
		case CURSOR_BLOCK:
			OUTB(0x60, 0x80);
			break;
		case CURSOR_UNDERLINE:
			OUTB(0x60, _BL + 0x7D);
			break;
	}
	OUTB(0x60, (_BL << 3) + 2);
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

void z_text_putsa(int x, int y, int z_atrb, const char *str)
{
	uint16_t codepoint;
	int p = ((y * text_width()) + x) * 2;
	int hw_atrb = 1;

	#define tx_chars(byte) ((char*)MK_FP(0xA000, p + byte))
	#define tx_chars(byte) ((char*)MK_FP(0xA000, p + byte))
	#define tx_atrbs(byte) ((int16_t*)MK_FP(0xA200, p + byte))

	if(z_atrb & 1) {
		hw_atrb += 0x20;
	}
	if(z_atrb & 4) {
		hw_atrb += 0x40;
	}
	if(z_atrb & 2) {
		hw_atrb += 0x80;
	}
	if(z_atrb & 0x800) {
		hw_atrb += 0x10;
	}
	if(z_atrb & 0x400) {
		hw_atrb += TX_UNDERLINE;
	}
	if(z_atrb & 0x200) {
		hw_atrb += TX_REVERSE;
	}
	if(z_atrb & 0x100) {
		hw_atrb += TX_BLINK;
	}
	hw_atrb += hw_atrb << 8;
	while(str[0]) {
		if(_ismbblead(str[0])) {
			codepoint = _mbcjmstojis(
				(str[0] << 8) + (unsigned char)str[1]
			);
			str += 2;
			if(codepoint >= 0x2921 && codepoint <= 0x2B7E) {
				*tx_chars(0) = ((codepoint >> 8) + 0xE0) | 0x80;
				*tx_chars(1) = codepoint;
				*tx_atrbs(0) = hw_atrb;
			} else if(x == text_width() - 1) {
				*(int16_t*)tx_chars(0) = ' ';
				*tx_atrbs(0) = hw_atrb;
			} else {
				*tx_chars(0) = (codepoint >> 8) + 0xE0;
				*tx_chars(1) = codepoint;
				*tx_chars(2) = ((codepoint >> 8) + 0xE0) | 0x80;
				*tx_chars(3) = codepoint;

				*tx_atrbs(0) = hw_atrb;
				*tx_atrbs(2) = hw_atrb;
				p += 2;
				x++;
			}
		} else {
			*(int16_t*)tx_chars(0) = *(unsigned char*)(str++);
			*tx_atrbs(0) = hw_atrb;
		}
		p += 2;
		if(++x >= text_width()) {
			break;
		}
	}
}

void z_text_vputsa(int x, int y, int z_atrb, const char *fmt, ...)
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
	OUTB(0x64, 0); // VSync interrupt trigger
}
