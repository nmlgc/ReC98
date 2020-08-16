#include "th02/math/randring.h"

uint16_t pascal near randring1_next16(void);
uint16_t pascal near randring1_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_mod(uint16_t mask);

inline char randring_angle(char random_range, char offset)
{
	return randring1_next16_and(random_range) + offset;
}
