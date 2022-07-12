typedef enum {
	// .GRC slots that can be freely used by bosses.
	GRC_SLOT_BOSS_1 = 0,
	GRC_SLOT_BOSS_2 = 1,
	GRC_SLOT_BOSS_3 = 2,
	GRC_SLOT_BOSS_4 = 3,

	GRC_SLOT_BOMB_KUJI_1 = 6, // kuzi1.grc
	GRC_SLOT_BOMB_KUJI_2 = 7, // kuzi2.grc
	GRC_SLOT_COUNT,

	_main_grc_slot_t_FORCE_INT16 = 0x7FFF
} main_grc_slot_t;
