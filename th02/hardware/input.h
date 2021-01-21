typedef uint16_t input_t;

// TODO: Turn into `const` variables once every translation unit that includes
// this file is compiled in C++ mode.
#define INPUT_UP         0x0001
#define INPUT_DOWN       0x0002
#define INPUT_LEFT       0x0004
#define INPUT_RIGHT      0x0008
#define INPUT_SHOT       0x0010
#define INPUT_BOMB       0x0020
#define INPUT_CANCEL     0x0040
#define INPUT_OK         0x0080
#define INPUT_Q          0x0100
#define INPUT_UP_LEFT    0x1000
#define INPUT_UP_RIGHT   0x2000
#define INPUT_DOWN_LEFT  0x4000
#define INPUT_DOWN_RIGHT 0x8000

#define INPUT_MOVEMENT_ALIGNED \
	(INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT)

#define INPUT_MOVEMENT_DIAGONAL \
	(INPUT_UP_LEFT | INPUT_UP_RIGHT | INPUT_DOWN_LEFT | INPUT_DOWN_RIGHT)

extern input_t key_det; /* ZUN symbol [MAGNet2010] */

void input_sense(void);
void key_delay(void);
