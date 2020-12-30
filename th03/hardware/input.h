// Changed from their TH02 values.
typedef enum {
	INPUT_NONE       = 0x0,
	INPUT_UP         = 0x1,
	INPUT_DOWN       = 0x2,
	INPUT_LEFT       = 0x4,
	INPUT_RIGHT      = 0x8,
	INPUT_BOMB       = 0x10,
	INPUT_SHOT       = 0x20,
	INPUT_UP_LEFT    = 0x100,
	INPUT_DOWN_LEFT  = 0x200,
	INPUT_UP_RIGHT   = 0x400,
	INPUT_DOWN_RIGHT = 0x800,
	INPUT_CANCEL     = 0x1000,
	INPUT_OK         = 0x2000,
	INPUT_Q          = 0x4000,
} input_t;

/// Variables
/// ---------
// Multi-player P1/P2 controls
extern uint16_t input_mp_p1;
extern uint16_t input_mp_p2;
// Single-player controls.
extern uint16_t input_sp;
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
/// -----

// Basic keyboard input function in this game. Resets and updates all three
// variables according to the keyboard state, with accurate detection of held
// keyboard keys.
void input_reset_sense_key_held();

// Waits the given number of [frames] for OK or SHOT to be pressed. Returns
// `true` if that happened, and `false` otherwise.
bool16 pascal input_wait_for_ok(unsigned int frames);

// Waits until BGM playback reached the given [measure] for OK or SHOT to be
// pressed. Returns `true` if that happened, and `false` otherwise. Falls back
// on input_wait_for_ok() with the given number of [frames] if BGM is disabled.
bool16 pascal input_wait_for_ok_or_measure(int measure, unsigned int frames);

// Waits for all held inputs to be released, then waits the given number of
// [frames] for an (interface) input to be pressed. Set [frames] to 0 or 9999
// to wait forever.
void pascal input_wait_for_change(int frames);
