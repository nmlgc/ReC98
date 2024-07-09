/// Stage background tile section definitions
/// -----------------------------------------
/// TH04 replaces TH02's 1-byte tile image IDs with precalculated 2-byte
/// offsets into VRAM, and wastes even more memory by storing an additional 8
/// unused tiles per row (probably to align each row at a 64-byte boundary).
/// As the only meaningful change, .MAP files can now store a variable number
/// of tile sections (though still limited to [TILE_SECTION_COUNT_MAX]), and
/// are consequently allocated dynamically.

#include "th02/formats/tile.hpp"
#include "planar.h"

static const unsigned int MAP_ROWS_PER_SECTION = 5;

// On-disk structures
// ------------------
#pragma pack(push, 1)

// .MAP file header.
struct map_header_t {
	uint16_t size; // Byte size of all sections
	int16_t section_count; // unused
	int16_t unknown[2];
};

struct map_section_tiles_t {
	vram_offset_t row[MAP_ROWS_PER_SECTION][TILES_MEMORY_X];
};

#pragma pack(pop)
// ------------------

extern map_section_tiles_t __seg* map_seg;

// Replaces [map_seg] with the tile sections loaded from the ST0?.MAP file
// corresponding to the current stage ID.
void near map_load(void);

// Frees [map_seg] if it's not a nullptr.
void near map_free(void);
