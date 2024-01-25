// Changed from their TH02 values.
typedef uint16_t input_t;

static const input_t INPUT_NONE       = 0x0000;
static const input_t INPUT_UP         = 0x0001;
static const input_t INPUT_DOWN       = 0x0002;
static const input_t INPUT_LEFT       = 0x0004;
static const input_t INPUT_RIGHT      = 0x0008;
static const input_t INPUT_BOMB       = 0x0010;
static const input_t INPUT_SHOT       = 0x0020;
static const input_t INPUT_UP_LEFT    = 0x0100;
static const input_t INPUT_DOWN_LEFT  = 0x0200;
static const input_t INPUT_UP_RIGHT   = 0x0400;
static const input_t INPUT_DOWN_RIGHT = 0x0800;
static const input_t INPUT_CANCEL     = 0x1000;
static const input_t INPUT_OK         = 0x2000;
static const input_t INPUT_Q          = 0x4000;

/// Variables
/// ---------

// Multi-player P1/P2 controls
extern input_t input_mp_p1;
extern input_t input_mp_p2;
// Single-player controls.
extern input_t input_sp;
/// ---------

/// Modes
/// -----
extern farfunc_t_near input_mode;

// Merges the inputs for the P1 multi-player keys into the single-player state
// after sensing.
void pascal input_mode_interface();

void pascal input_mode_key_vs_key();	// Completely ignores joystick input.
void pascal input_mode_joy_vs_key();
void pascal input_mode_key_vs_joy();

void pascal input_mode_1p_vs_cpu();
void pascal input_mode_cpu_vs_1p();
// Just allows quitting via the OK or CANCEL buttons, both of which are mapped
// to INPUT_CANCEL.
void pascal input_mode_cpu_vs_cpu();
// Just allows quitting via pressing any button.
void pascal input_mode_attract();

// Input sense function used in UIs
#define input_reset_sense_interface input_mode_interface
/// -----

// Basic keyboard input function in this game. Resets and updates all three
// variables according to the keyboard state, with accurate detection of held
// keyboard keys.
void input_reset_sense_key_held();

// Waits the given number of [frames] for OK or SHOT to be pressed. Returns
// `true` if that happened, and `false` otherwise.
bool16 pascal input_wait_for_ok(unsigned int frames);

// Behaves like a call to snd_delay_until_measure() with the given parameters
// (and all of its corner case issues) whose delay can be interrupted by
// pressing OK or SHOT. Returns `true` if such an input happened, and `false`
// otherwise.
bool16 pascal input_wait_for_ok_or_measure(int measure, unsigned int frames);

// Waits for all held inputs to be released, then waits the given number of
// [frames] for an (interface) input to be pressed. Set [frames] to 0 or 9999
// to wait forever.
void pascal input_wait_for_change(int frames);
