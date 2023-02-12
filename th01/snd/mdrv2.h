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

// Spawns the MDRV2 TSR, reserving the given number of KiB for the music data
// area, reporting any error on screen. Returns the MDRV2 exit code, or -1 on
// error.
int mdrv2_spawn(uint8_t bgm_data_kib);

// Removes the MDRV2 TSR, reporting any error on screen. Returns the MDRV2 exit
// code, or -1 on error.
int mdrv2_remove(void);
