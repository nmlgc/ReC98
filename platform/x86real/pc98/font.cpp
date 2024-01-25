#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "platform/x86real/pc98/font.hpp"

// The PC-98 character generator can be accessed in two ways:
//
// 1) I/O ports (0xA1, 0xA3, 0xA5, 0xA9)
// 2) BIOS function INT 18h AH=14h (reading) / AH=18h (writing gaiji)
//
// The BIOS variant is both simpler to use *and* faster, as the BIOS implements
// it in the optimal way for the specific hardware we run on:
//
// • At worst, it's an optimized ASM version of the I/O port code we would
//   write ourselves (as seen in the PC-9801VX / PC-9801RA BIOS).
// • At best, it directly reads from and writes to memory after mapping the JIS
//   code point to an address, which is always preferable to port I/O (as seen
//   in the PC-98HA BIOS).
// • Emulators directly implement it in native code.

void font_read(font_glyph_t& glyph, jis_t jis)
{
	_BX = FP_SEG(&glyph);
	_CX = FP_OFF(&glyph);
	_DX = jis;
	_AH = 0x14;
	geninterrupt(0x18);
	glyph.tag.w *= GLYPH_HALF_W;
	glyph.tag.h *= GLYPH_HALF_H;
}

void font_read(font_glyph_ank_8x8_t& glyph, ank_t ank)
{
	font_read(reinterpret_cast<font_glyph_t &>(glyph), static_cast<jis_t>(ank));
}

void font_read(font_glyph_ank_8x16_t& glyph, ank_t ank)
{
	font_read(reinterpret_cast<font_glyph_t &>(glyph), (0x8000 + ank));
}

void font_gaiji_write(
	const dot_rect_t(GLYPH_FULL_W, GLYPH_H)* gaiji,
	uint16_t count,
	uint8_t id
)
{
	// Yeah, that copy is kind of silly, but we don't want to force that
	// awkward 16×17 format onto the caller.
	font_glyph_kanji_t tmp;

	jis_t jis = (0x7680 + id);
	for(uint16_t i = 0; i < count; i++) {
		tmp.dots = *gaiji;
		_BX = FP_SEG(&tmp);
		_CX = FP_OFF(&tmp);
		_DX = jis;
		_DX &= 0xFF7F;
		_AH = 0x1A;
		geninterrupt(0x18);

		gaiji++;
		jis++;
	}
}
