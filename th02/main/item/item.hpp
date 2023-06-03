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

extern unsigned int item_bigpower_override;

// Increases by varying amounts depending on how well items are collected,
// decrements for every 16 dropped items.
extern int item_skill;

extern int point_items_collected;

void near items_update_and_render(void);
