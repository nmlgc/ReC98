// Player performance metrics
// --------------------------

extern uint8_t total_miss_count;
extern uint8_t total_bombs_used;

// Reset to 0 when moving to a new stage.
extern uint8_t stage_miss_count;
extern uint8_t stage_bombs_used;

// Increases by varying amounts depending on how well items are collected,
// decrements for every 16 dropped items.
extern int item_skill;

extern int point_items_collected;
