uint16_t pascal near randring1_next16(void);
uint16_t pascal near randring1_next16_and(uint16_t mask);

inline char randring_angle(char random_range, char offset)
{
	return randring1_next16_and(random_range) + offset;
}
