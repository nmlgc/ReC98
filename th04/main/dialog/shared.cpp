#include "th04/main/dialog/shared.hpp"

#define BOX_TILE_W 16
#define BOX_TILE_H 4
#define BOX_TILE_COUNT 3

#define BOX_TILE_VRAM_W (BOX_TILE_W / BYTE_DOTS)
#define BOX_VRAM_W (BOX_W / BYTE_DOTS)

extern const dot_rect_t(BOX_TILE_W, BOX_TILE_H) BOX_TILES[BOX_TILE_COUNT];

void pascal near dialog_box_put(uscreen_x_t left, uvram_y_t top, int tile)
;
