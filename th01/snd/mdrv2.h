#include "platform.h"

// Returns `true` if the MDRV2 driver is resident.
bool16 mdrv2_resident(void);

// Checks and returns whether an FM sound source is installed, and enables all
// other functions if `true`.
bool16 mdrv2_enable_if_board_installed(void);

void mdrv2_bgm_load(const char *fn);
void mdrv2_se_load(const char *fn);

// Plays back the BGM file that was previously loaded via mdrv2_bgm_load().
void mdrv2_bgm_play(void);

void mdrv2_bgm_stop(void);
void mdrv2_bgm_fade_out_nonblock(void);

void mdrv2_se_play(int se);
