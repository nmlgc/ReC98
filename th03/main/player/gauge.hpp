#include "th03/common.h"

#define GAUGE_MAX (0xFF << 4)

typedef uint16_t gauge_t;
typedef uint8_t gauge_perbyte_t;

// 1-based, 16 possible levels.
static const uint8_t GAUGE_ATTACK_LEVEL_MIN = 1;
static const uint8_t GAUGE_ATTACK_LEVEL_MAX = 16;
extern uint8_t gauge_attack_level[PLAYER_COUNT];

static const uint8_t BOSS_ATTACK_LEVEL_MAX = 16;
extern uint8_t boss_attack_level;

void pascal near gauge_avail_add(pid_t pid, unsigned char charge);
