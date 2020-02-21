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
#endif

typedef struct {
	cfg_options_t opts;
	void __seg *resident_sgm;
	int8_t debug;
} cfg_t;
#pragma option -a.
