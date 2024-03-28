typedef uint16_t input_t;

static const input_t INPUT_NONE       = 0x0000;
static const input_t INPUT_UP         = 0x0001;
static const input_t INPUT_DOWN       = 0x0002;
static const input_t INPUT_LEFT       = 0x0004;
static const input_t INPUT_RIGHT      = 0x0008;
static const input_t INPUT_SHOT       = 0x0010;
static const input_t INPUT_BOMB       = 0x0020;
static const input_t INPUT_CANCEL     = 0x0040;
static const input_t INPUT_OK         = 0x0080;
static const input_t INPUT_Q          = 0x0100;
static const input_t INPUT_UP_LEFT    = 0x1000;
static const input_t INPUT_UP_RIGHT   = 0x2000;
static const input_t INPUT_DOWN_LEFT  = 0x4000;
static const input_t INPUT_DOWN_RIGHT = 0x8000;

static const input_t INPUT_MOVEMENT_ALIGNED = (
	INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT
);

static const input_t INPUT_MOVEMENT_DIAGONAL = (
	INPUT_UP_LEFT | INPUT_UP_RIGHT | INPUT_DOWN_LEFT | INPUT_DOWN_RIGHT
);

extern input_t key_det; /* ZUN symbol [MAGNet2010] */

// Resets and updates [key_det].
void input_reset_sense(void);

void key_delay(void);
