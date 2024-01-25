// Changed from their TH03 values.
typedef uint16_t input_t;

// Replays only store the "subset" that fits into 8 bits.
typedef uint8_t input_replay_t;

static const input_replay_t INPUT_NONE  = 0x0000;
static const input_replay_t INPUT_UP    = 0x0001;
static const input_replay_t INPUT_DOWN  = 0x0002;
static const input_replay_t INPUT_LEFT  = 0x0004;
static const input_replay_t INPUT_RIGHT = 0x0008;
static const input_replay_t INPUT_BOMB  = 0x0010;
static const input_replay_t INPUT_SHOT  = 0x0020;
static const input_t INPUT_UP_LEFT      = 0x0100;
static const input_t INPUT_UP_RIGHT     = 0x0200;
static const input_t INPUT_DOWN_LEFT    = 0x0400;
static const input_t INPUT_DOWN_RIGHT   = 0x0800;
static const input_t INPUT_CANCEL       = 0x1000;
static const input_t INPUT_OK           = 0x2000;
static const input_t INPUT_Q            = 0x4000;

static const input_t INPUT_MOVEMENT = (
	INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT |
	INPUT_UP_LEFT | INPUT_UP_RIGHT | INPUT_DOWN_LEFT | INPUT_DOWN_RIGHT
);

extern input_t key_det; /* ZUN symbol [MAGNet2010] */
extern bool shiftkey; /* ZUN symbol [MAGNet2010] */
