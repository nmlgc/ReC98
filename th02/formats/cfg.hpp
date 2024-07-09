#include "platform.h"
struct resident_t;

#if (GAME == 2)
	#define CFG_FN "huuma.cfg"
	struct cfg_options_t {
		int8_t rank;
		int8_t bgm_mode;
		int8_t bombs;
		int8_t lives;
		bool reduce_effects;
	};

	#define CFG_LIVES_MAX 4
	#define CFG_LIVES_DEFAULT 2
	#define CFG_BOMBS_MAX 3
	#define CFG_BOMBS_DEFAULT CFG_BOMBS_MAX

	int cfg_load(void);
#endif

struct cfg_t {
	cfg_options_t opts;
	resident_t __seg *resident;
	int8_t debug;
#if GAME >= 4
	int8_t opts_sum; // Sum of all bytes in [opts]
#endif
};
