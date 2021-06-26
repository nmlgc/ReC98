#define PLAYER_W 32
#define PLAYER_H 48

extern bool player_is_hit;

// Grants invincibility when >0. Decrements by 1 each frame in that case.
// In TH02, this works independently from [player_invincible_via_bomb].
extern unsigned char player_invincibility_time;

#if (GAME == 2)
	// Grants invincibility as long as it's true. Works independently from
	// [player_invincibility_time].
	extern bool player_invincible_via_bomb;
#endif
