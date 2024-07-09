// Player performance metrics
// --------------------------

#include "platform.h"

extern int playperf;
static const int playperf_min = -6;
extern uint8_t playperf_max;

extern uint8_t total_miss_count;
extern uint8_t total_bombs_used;

// Reset to 0 when moving to a new stage.
extern uint8_t stage_miss_count;
extern uint8_t stage_bombs_used;

// Increases by varying amounts depending on how well items are collected,
// decrements for every 16 dropped items.
extern int item_skill;

extern int point_items_collected;
