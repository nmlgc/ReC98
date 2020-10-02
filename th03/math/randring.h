#include "th02/math/randring.h"

uint16_t pascal near randring1_next16(void);
uint16_t pascal near randring1_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_mod(uint16_t mask);

inline unsigned char randring_angle(unsigned char range, unsigned char offset)
{
	return randring1_next16_and(range) + offset;
}
