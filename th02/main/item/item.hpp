enum item_type_t {
	IT_POWER = 0,
	IT_POINT = 1,
	IT_BOMB = 2,
	IT_BIGPOWER = 3,
	IT_1UP = 4,
	IT_COUNT,

	_item_type_t_FORCE_UINT8 = 0xFF
};

#define ITEM_COUNT 20

// Turns the next N power or point items spawned via items_add() into big power
// items. Used for recharging power after using a continue after a Game Over.
extern unsigned int item_bigpower_override;

// Spawns the Game Over item set on the next call to items_miss_add().
// ZUN bloat: Both turning this into a parameter or hardcoding the condition
// (as TH04 and TH05 do it) would have been better than this.
extern bool items_miss_add_gameover;

// Also picks a new starting point inside the hardcoded randomized item cycle
// used by items_add_semirandom().
void near items_init_and_reset(void);

// Unconditionally spawns a big power item if [item_bigpower_override] is > 0.
// Otherwise, spawns a bomb item with a 1-in-512 chance, or the next item along
// a hardcoded ring of power and point items.
void pascal items_add_semirandom(screen_x_t left, screen_y_t top);

void pascal items_add(int type, screen_x_t left, screen_y_t top);

// Spawns each of the items dropped when losing a life at the given position.
void pascal near items_miss_add(screen_x_t left, screen_y_t top);

void near items_update_and_render(void);
