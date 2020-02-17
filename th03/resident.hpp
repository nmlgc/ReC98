typedef struct {
	char id[11]; // "YUMEConfig"
	char difficulty;
	char playchar_paletted[2]; // ID of the player character in the same format as in playchar_palleted in player.h
	char pl_is_cpu[2];
	long random_seed;
	char unused;
	char music_mode;
	char input_mode
	bool game_over;
	score_lebcd_t score_last[2];
	char mode; /* 0x01 = Story mode
	              0x7F = Demo mode
	              0x80 = Player vs CPU
	              0x81 = Player vs Player
	              0x82 = CPU vs CPU */
	char story_opponents[10]; // Character IDs are the same as in playchar_paletted
	char stage_id;
	char lifes;
	bool story_beat; // Will cause OP.EXE to open the name registry
	char credits_remaining;
	bool op_fast_load;
	char skill;
	bool demo_active; // Doesn't get reset to 0 immediatly when the demo finishes
} resident_t;
