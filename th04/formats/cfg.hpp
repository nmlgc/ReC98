#ifndef TH04_FORMATS_CFG_HPP
#define TH04_FORMATS_CFG_HPP

#include "platform.h"

#define CFG_FN "MIKO.CFG"

// ZUN landmine: The lowercase variant is only used by `ZUN.COM -S`. Will break
// when porting to case-sensitive file systems.
#define CFG_FN_LOWER "miko.cfg"

struct cfg_options_t {
	int8_t rank;
	int8_t lives;
	int8_t bombs;
	int8_t bgm_mode;
	int8_t se_mode;
	int8_t turbo_mode;

	int8_t sum(void) const {
		return (rank + lives + bombs + bgm_mode + se_mode + turbo_mode);
	}
};

#include "th03/formats/cfg.hpp"

#define CFG_LIVES_MAX 6
#define CFG_LIVES_DEFAULT 3

static const int CFG_BOMBS_MAX = ((GAME == 5) ? 3 : 2);
#define CFG_BOMBS_DEFAULT CFG_BOMBS_MAX

#endif /* TH04_FORMATS_CFG_HPP */
