#include <stddef.h>
#include "platform.h"
#include "th03/common.h"
#include "th03/score.h"
#include "th03/playchar.hpp"
#include "th03/sprites/regi.h"
#include "th03/formats/scoredat.hpp"
#include "th03/formats/scorecry.hpp"

void near scoredat_decode(void)
{
	uint8_t near *p = reinterpret_cast<uint8_t near *>(&hi);
	int i = 0;
	uint8_t tmp;

	while(i < (offsetof(scoredat_section_t, score.key1) - 1)) {
		scoredat_decode_byte_at(p, tmp, hi.score.key1, hi.score.key2);
		i++;
		p++;
	}
	p[0] = (hi.score.key1 + hi.score.key2 + p[0]);
}
