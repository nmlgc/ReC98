#include "th03/common.h"

extern uint8_t enemies_alive[PLAYER_COUNT];

// Derived from [round_speed].
extern uint8_t enemy_speed;

// Loads constant enemy formation data.
void enemy_formations_load(void);

// Creates a new randomized order of enemy formations and movement directions.
void enemy_formations_randomize(void);
