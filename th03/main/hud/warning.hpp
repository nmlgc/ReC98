// WARNING!! You are forced to evade from... '(BOSS|GAUGE) ATTACK' Level
// Your life is in peril !! Be careful...
// ---------------------------------------------------------------------

#include "th03/common.h"

static const int WARNING_FLASH_RED_FRAMES = 30;

// Not really keyframes because [WF_FLASH_WHITE] takes more than one real
// frame.
enum warning_flag_t {
	WF_NONE = 0,

	// Starts the warning animation with the attacking character's portrait
	// on their playfield.
	WF_PORTRAIT = 1,

	WF_FLASH_WHITE = 2, // Runs in a blocking way.
	WF_FLASH_RED = 3, // Runs in a non-blocking way.
	WF_FLASH_RED_END = (WF_FLASH_RED + WARNING_FLASH_RED_FRAMES),
};

extern warning_flag_t warning_flag[PLAYER_COUNT];
