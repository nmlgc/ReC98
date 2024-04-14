#include "platform.h"
#include "pc98.h"
#include "th03/common.h"

static const int HITCIRCLE_FRAMES = 16;

static const int HITCIRCLE_ENEMY_COUNT = 12;

// ZUN quirk: Should *maybe* be [PLAYER_COUNT]? If both players get hit within
// [HITCIRCLE_FRAMES], the earlier animation is cut off. It's too obvious of an
// oversight to classify it as a bug, though. The sudden stop of the animation
// could also be supposed to telegraph that the other player got hit, without
// having to peek over to the other playfield.
static const int HITCIRCLE_PLAYER_COUNT = 1;

static const int HITCIRCLE_COUNT = (
	HITCIRCLE_ENEMY_COUNT + HITCIRCLE_PLAYER_COUNT
);

struct HitCircle {
	uint8_t age; // Alive if ≥1.
	pid_t pid;
	screen_point_t topleft;
};

extern HitCircle hitcircles[HITCIRCLE_COUNT];
