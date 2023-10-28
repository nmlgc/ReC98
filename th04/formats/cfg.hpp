#define CFG_FN "miko.cfg"
typedef struct {
	int8_t rank;
	int8_t lives;
	int8_t bombs;
	int8_t bgm_mode;
	int8_t se_mode;
	int8_t turbo_mode;

	int8_t sum(void) const {
		return (rank + lives + bombs + bgm_mode + se_mode + turbo_mode);
	}
} cfg_options_t;

#include "th03/formats/cfg.hpp"

#define CFG_LIVES_MAX 6
#define CFG_LIVES_DEFAULT 3

#if GAME == 5
	#define CFG_BOMBS_MAX 3
#else
	#define CFG_BOMBS_MAX 2
#endif
#define CFG_BOMBS_DEFAULT CFG_BOMBS_MAX
