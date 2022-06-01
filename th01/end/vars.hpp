extern long score;
extern long score_highest;
extern unsigned char rank;
extern long continues_total;
extern long continues_per_scene[SCENE_COUNT];
extern char start_lives_extra;
extern end_sequence_t end_flag; /* ZUN symbol [Strings] */

// Resets all end-related data in the resident structure. Always returns true.
bool16 end_resident_clear(void);
