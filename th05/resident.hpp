#define RES_ID "KSOConfig"
typedef struct {
	char id[RES_ID_LEN];
	bool zunsoft_shown;
	int8_t unused_1;
	char unknown;
	unsigned char credit_lives;
	unsigned char credit_bombs;
	unsigned char cfg_lives;
	unsigned char cfg_bombs;
	unsigned char rank;
	unsigned char bgm_mode;
	unsigned char stage;
	unsigned char playchar;
	unsigned char se_mode;
	unsigned char turbo_mode;
	bool debug;
	unsigned char debug_stage;
	unsigned char debug_power;
	unsigned char end_sequence;
	unsigned char miss_count;
	unsigned char bombs_used;
	unsigned char demo_stage;
	int8_t unused_2;
	unsigned char demo_num;
	score_lebcd_t score_last;
	long rand;
	unsigned int std_frames;	// (excluding bosses, see th04/frames.h)
	unsigned int items_spawned;
	unsigned int items_collected;
	unsigned int point_items_collected;
	unsigned int max_valued_point_items_collected;

	// *Not* spawned. # of enemies that either left the screen or were killed.
	unsigned int enemies_gone;

	unsigned int enemies_killed;
	unsigned int graze;
	unsigned long slow_frames;
	unsigned long frames;	// (including bosses, see th04/frames.h)

	// Stored without the number of continues used prior to the one
	// this score was set at, interestingly enough.
	score_lebcd_t score_highest;

	score_lebcd_t stage_score[MAIN_STAGE_COUNT];
	int32_t unused_3;
} resident_t;

extern resident_t *resident;
