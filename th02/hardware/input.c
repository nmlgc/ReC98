#pragma option -k-
void input_sense(void)
{
	#define KEYGROUP_SENSE(group) __asm { \
		mov al, group; \
		mov ah, 4; \
		int 0x18; \
	}

	key_det = 0;

	KEYGROUP_SENSE(7);
	_BH = _AH;
	KEYGROUP_SENSE(8);
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
	KEYGROUP_SENSE(9);
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
	KEYGROUP_SENSE(5);
	if(_AH & K5_Z) {
		key_det |= INPUT_SHOT;
	}
	if(_AH & K5_X) {
		key_det |= INPUT_BOMB;
	}
	KEYGROUP_SENSE(0);
	if(_AH & K0_ESC) {
		key_det |= INPUT_CANCEL;
	}
	KEYGROUP_SENSE(3);
	if(_AH & K3_RETURN) {
		key_det |= INPUT_OK;
	}
	KEYGROUP_SENSE(2);
	if(_AH & K2_Q) {
		key_det |= INPUT_Q;
	}
	KEYGROUP_SENSE(6);
	if(_AH & K6_SPACE) {
		key_det |= INPUT_SHOT;
	}
}
#pragma codestring "\x90"
#pragma option -k
