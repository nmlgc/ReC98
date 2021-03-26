#pragma option -WX -zCSHARED -k-

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98kbd.h"
#include "th02/hardware/input.hpp"

inline uint8_t keygroup_sense(uint8_t group) {
	_AL = group;
	_AH = 0x04;
	geninterrupt(0x18);
	return _AH;
}

void input_sense(void)
{
	key_det = INPUT_NONE;

	_BH = keygroup_sense(7);
	_AH = keygroup_sense(8);
	if(_BH & K7_ARROW_UP || _AH & K8_NUM_8) {
		key_det |= INPUT_UP;
	}
	if(_BH & K7_ARROW_LEFT || _AH & K8_NUM_4) {
		key_det |= INPUT_LEFT;
	}
	if(_AH & K8_NUM_7) {
		key_det |= INPUT_UP_LEFT;
	}
	if(_AH & K8_NUM_9) {
		key_det |= INPUT_UP_RIGHT;
	}

	_AH = keygroup_sense(9);
	if(_BH & K7_ARROW_DOWN || _AH & K9_NUM_2) {
		key_det |= INPUT_DOWN;
	}
	if(_BH & K7_ARROW_RIGHT || _AH & K9_NUM_6) {
		key_det |= INPUT_RIGHT;
	}
	if(_AH & K9_NUM_1) {
		key_det |= INPUT_DOWN_LEFT;
	}
	if(_AH & K9_NUM_3) {
		key_det |= INPUT_DOWN_RIGHT;
	}

	_AH = keygroup_sense(5);
	if(_AH & K5_Z) {
		key_det |= INPUT_SHOT;
	}
	if(_AH & K5_X) {
		key_det |= INPUT_BOMB;
	}

	_AH = keygroup_sense(0);
	if(_AH & K0_ESC) {
		key_det |= INPUT_CANCEL;
	}

	_AH = keygroup_sense(3);
	if(_AH & K3_RETURN) {
		key_det |= INPUT_OK;
	}

	_AH = keygroup_sense(2);
	if(_AH & K2_Q) {
		key_det |= INPUT_Q;
	}

	_AH = keygroup_sense(6);
	if(_AH & K6_SPACE) {
		key_det |= INPUT_SHOT;
	}
}
#pragma codestring "\x90"

}
