#define RANDRING_SIZE 256

extern uint8_t randring[RANDRING_SIZE];

#if GAME == 2
	extern uint8_t randring_p;

	uint8_t pascal near randring1_next8(void);
	uint8_t pascal near randring1_next8_and(uint8_t mask);
	uint16_t pascal near randring1_next16(void);
	uint8_t pascal near randring2_next8(void);
	uint8_t pascal near randring2_next8_and(uint8_t mask);
	uint16_t pascal near randring2_next16(void);
#endif
