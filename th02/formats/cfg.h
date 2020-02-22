#pragma option -a1

#if GAME == 2
# define CFG_FN "huuma.cfg"
	typedef struct {
		int8_t rank;
		int8_t bgm_mode;
		int8_t bombs;
		int8_t lives;
		int8_t perf;
	} cfg_options_t;

# define CFG_LIVES_MAX 4
# define CFG_LIVES_DEFAULT 2
# define CFG_BOMBS_MAX 3
# define CFG_BOMBS_DEFAULT CFG_BOMBS_MAX
#endif

typedef struct {
	cfg_options_t opts;
	void __seg *resident_sgm;
	int8_t debug;
} cfg_t;
#pragma option -a.
