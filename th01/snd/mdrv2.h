void mdrv2_bgm_load(const char *fn);
void mdrv2_se_load(const char *fn);

// Plays back the BGM file that was previously loaded via mdrv2_bgm_load().
void mdrv2_bgm_play(void);

void mdrv2_bgm_stop(void);
void mdrv2_bgm_fade_out_nonblock(void);

void mdrv2_se_play(int se);
