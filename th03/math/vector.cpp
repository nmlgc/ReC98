#pragma option -zCSHARED

#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "th03/math/vector.hpp"

// Completely disgusting. TH02's version was fine!

#define vector2_raw(ret_x, ret_y, angle, length) \
	_DL = angle; \
	_SI = length; \
	_EAX = static_cast<int16_t>(_SI); \
	_DH = 0; \
	_DX += _DX; /* *= sizeof(short) */ \
	_BX = _DX; \
	_asm { \
		db 0x66, 0x0F, 0xBF, 0x97;	/* MOVSX EDX,                */ \
		dw offset CosTable8;      	/*            CosTable8[bx]; */ \
		db 0x66, 0x0F, 0xBF, 0x8F;	/* MOVSX ECX,                */ \
		dw offset SinTable8;      	/*            SinTable8[bx]; */ \
	} \
	ret_x = (static_cast<long>(_EAX * _EDX) >> 8); \
	ret_y = (static_cast<long>(static_cast<int16_t>(_SI) * _ECX) >> 8);

void pascal vector2(int &ret_x, int &ret_y, unsigned char angle, int length)
{
	vector2_raw(ret_x, ret_y, angle, length);
}
#pragma codestring "\x90"

void pascal vector2_between_plus(
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned char plus_angle,
	int &ret_x,
	int &ret_y,
	int length
)
{
	_SI = length;
	vector2_raw(ret_x, ret_y, (iatan2((y2 - y1), (x2 - x1)) + plus_angle), _SI);
}
