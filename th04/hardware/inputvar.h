// Changed from their TH03 values.
#define INPUT_NONE       0
#define INPUT_UP         1
#define INPUT_DOWN       2
#define INPUT_LEFT       4
#define INPUT_RIGHT      8
#define INPUT_BOMB       0x10
#define INPUT_SHOT       0x20
#define INPUT_UP_LEFT    0x100
#define INPUT_UP_RIGHT   0x200
#define INPUT_DOWN_LEFT  0x400
#define INPUT_DOWN_RIGHT 0x800
#define INPUT_CANCEL     0x1000
#define INPUT_OK         0x2000
#define INPUT_Q          0x4000

#define INPUT_MOVEMENT \
	INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT | \
	INPUT_UP_LEFT | INPUT_UP_RIGHT | INPUT_DOWN_LEFT | INPUT_DOWN_RIGHT

extern int16_t key_det; /* ZUN symbol [MAGNet2010] */
