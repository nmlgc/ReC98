extern long score;
extern long score_highest;
extern int32_t continues_total;

// ZUN bloat: The resident structure just uses uint16_t.
extern int32_t continues_per_scene[SCENE_COUNT];

extern int8_t start_lives_extra;
extern end_sequence_t end_flag; /* ZUN symbol [Strings] */
extern uint8_t rank;

// Resets all end-related data in the resident structure. Always returns true.
bool16 end_resident_clear(void);
