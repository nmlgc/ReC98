#include "th04/main/playfld.hpp"
#include "th02/main/entity.hpp"

// An expanding dotted circle, shown when spawning items. Note the slight
// semantic differences to the circle_t structure.
struct item_splash_t {
	entity_flag_t flag;
	char time;	// ZUN bloat: Expressed via the radius.
	SPPoint center;
	Subpixel radius_cur;
	Subpixel radius_prev;
};

#define ITEM_SPLASH_COUNT 8
static const int ITEM_SPLASH_DOTS = ((GAME == 5) ? 32 : 64);

extern item_splash_t item_splashes[ITEM_SPLASH_COUNT];

void __fastcall near item_splash_dot_render(screen_x_t x, vram_y_t vram_y);
void near item_splashes_init(void);
void pascal near item_splashes_add(Subpixel center_x, Subpixel center_y);
void near item_splashes_update(void);
void near item_splashes_render(void);
