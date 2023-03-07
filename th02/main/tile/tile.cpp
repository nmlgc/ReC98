#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th02/main/tile/tile.hpp"

// State
// -----

extern int8_t tile_line_at_top;
extern vram_offset_t tile_image_vos[TILE_IMAGE_COUNT];
extern pixel_t tile_copy_lines_top;
extern pixel_t tile_copy_lines_h;
extern bool tile_dirty[TILES_X][TILES_Y];

// Optimization to skip checking all vertical tiles for clean columns.
extern bool tile_column_dirty[TILES_X];
// -----
