#ifndef TH02_MAIN_ENTITY_HPP
#define TH02_MAIN_ENTITY_HPP

// Generic entity state flag
enum entity_flag_t {
	F_FREE = 0,
	F_ALIVE = 1,
	F_REMOVE = 2, // Removes the entity from VRAM and transitions to F_FREE.

	_entity_flag_t_FORCE_UINT8 = 0xFF
};

#endif // TH02_MAIN_ENTITY_HPP
