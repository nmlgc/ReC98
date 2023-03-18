#if GAME == 2
	#define CFG_FN "huuma.cfg"
	typedef struct {
		int8_t rank;
		int8_t bgm_mode;
		int8_t bombs;
		int8_t lives;
		bool reduce_effects;
	} cfg_options_t;

	#define CFG_LIVES_MAX 4
	#define CFG_LIVES_DEFAULT 2
	#define CFG_BOMBS_MAX 3
	#define CFG_BOMBS_DEFAULT CFG_BOMBS_MAX
#endif

typedef struct {
	cfg_options_t opts;
	resident_t __seg *resident;
	int8_t debug;
#if GAME >= 4
	int8_t opts_sum; // Sum of all bytes in [opts]
#endif
} cfg_t;
