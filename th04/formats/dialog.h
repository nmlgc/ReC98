// Box
// ---
#define DIALOG_BOX_W 320
#define DIALOG_BOX_H 48
#define DIALOG_BOX_TILE_W 16
#define DIALOG_BOX_TILE_H 4
#define DIALOG_BOX_TILE_COUNT 3

#define DIALOG_BOX_TILE_VRAM_W (DIALOG_BOX_TILE_W / 8)
#define DIALOG_BOX_VRAM_W (DIALOG_BOX_W / 8)

extern const dots16_t DIALOG_BOX_TILES[DIALOG_BOX_TILE_COUNT][DIALOG_BOX_TILE_H];

void pascal near dialog_box_put(unsigned int left, unsigned int top, int tile);
void pascal near dialog_box_fade_in();
// ---
