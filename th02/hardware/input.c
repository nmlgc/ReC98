#pragma option -k-
void input_sense(void)
{
	#define KEYGROUP_SENSE(group) __asm { \
		mov al, group; \
		mov ah, 4; \
		int 0x18; \
	}

	input = 0;

	KEYGROUP_SENSE(7);
	_BH = _AH;
	KEYGROUP_SENSE(8);
	if(_BH & K7_ARROW_UP || _AH & K8_NUM_8) {
		input |= INPUT_UP;
	}
	if(_BH & K7_ARROW_LEFT || _AH & K8_NUM_4) {
		input |= INPUT_LEFT;
	}
	if(_AH & K8_NUM_7) {
		input |= INPUT_UP_LEFT;
	}
	if(_AH & K8_NUM_9) {
		input |= INPUT_UP_RIGHT;
	}
	KEYGROUP_SENSE(9);
	if(_BH & K7_ARROW_DOWN || _AH & K9_NUM_2) {
		input |= INPUT_DOWN;
	}
	if(_BH & K7_ARROW_RIGHT || _AH & K9_NUM_6) {
		input |= INPUT_RIGHT;
	}
	if(_AH & K9_NUM_1) {
		input |= INPUT_DOWN_LEFT;
	}
	if(_AH & K9_NUM_3) {
		input |= INPUT_DOWN_RIGHT;
	}
	KEYGROUP_SENSE(5);
	if(_AH & K5_Z) {
		input |= INPUT_SHOT;
	}
	if(_AH & K5_X) {
		input |= INPUT_BOMB;
	}
	KEYGROUP_SENSE(0);
	if(_AH & K0_ESC) {
		input |= INPUT_CANCEL;
	}
	KEYGROUP_SENSE(3);
	if(_AH & K3_RETURN) {
		input |= INPUT_OK;
	}
	KEYGROUP_SENSE(2);
	if(_AH & K2_Q) {
		input |= INPUT_Q;
	}
	KEYGROUP_SENSE(6);
	if(_AH & K6_SPACE) {
		input |= INPUT_SHOT;
	}
}
#pragma codestring "\x90"
#pragma option -k
