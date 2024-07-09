extern enum stage_progression_t {
	SP_STAGE = 0, // The scrolling part with stage enemies.
	SP_BOSS = 1, // The boss fight.
	SP_CLEAR = 2, // Calls [boss_end] once returned from [boss_update].
} stage_progression;

extern char stage_id;
