// GENSOU.SCR implementation functions

#include "th03/formats/scorecry.hpp"
#include <stddef.h>

#define scoredat_sum(sum, i, section) { \
	sum = 0; \
	i = offsetof(scoredat_section_t, score); \
	while(i < sizeof(scoredat_section_t)) { \
		sum += reinterpret_cast<uint8_t *>(&section)[i]; \
		i++; \
	} \
}

#define scoredat_decode_section(section, sum, i) { \
	int i = offsetof(scoredat_section_t, score); \
	while(i < (sizeof(scoredat_section_t) - 1)) { \
		uint8_t tmp; \
		scoredat_decode_byte_at( \
			(reinterpret_cast<uint8_t *>(&section) + i),  \
			tmp, \
			section.key1, \
			section.key2 \
		) \
		i++; \
	} \
	reinterpret_cast<uint8_t *>(&section)[i] += section.key1; \
	scoredat_sum(sum, i, section); \
}
