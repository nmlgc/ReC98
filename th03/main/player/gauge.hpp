#include "th03/common.h"

#define GAUGE_MAX (0xFF << 4)

typedef uint16_t gauge_t;
typedef uint8_t gauge_perbyte_t;

// 1-based, 16 possible levels.
static const uint8_t GAUGE_ATTACK_LEVEL_MIN = 1;
static const uint8_t GAUGE_ATTACK_LEVEL_MAX = 16;
extern uint8_t gauge_attack_level[PLAYER_COUNT];

// ZUN bloat: But how many possible levels does this one have? A
// [boss_attack_level] of 1 would render as 2 next to the gauge, but as 1 in
// the WARNING popup. Since firing a Boss Attack always increments the level,
// it would seem that the popup indicates the level of the *incoming* attack
// while the gauge indicates the level of the *next* one. However, this
// interpretation would contradict 夢時空.TXT, which explicitly describes the
// level next to the gauge as the 「現在のＢＯＳＳアタックのレベル」.
// In any case, this could have been solved more cleanly with a separate
// variable.
// TODO: Look at this again once we've decompiled a few of the Boss Attacks and
// can confirm how they use this variable.
static const uint8_t BOSS_ATTACK_LEVEL_MAX = 16;
extern uint8_t boss_attack_level;

void pascal near gauge_avail_add(pid_t pid, unsigned char charge);
