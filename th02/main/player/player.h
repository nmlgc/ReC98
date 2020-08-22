#define PLAYER_W 32
#define PLAYER_H 48

// Grants invincibility when >0. Decrements by 1 each frame in that case.
// Works independently from [player_invincible_via_bomb].
extern unsigned char player_invincibility_time;

// Grants invincibility as long as it's true. Works independently from
// [player_invincibility_time].
extern bool player_invincible_via_bomb;
