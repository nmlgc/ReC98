enum item_splash_flag_t {
	ISF_FREE = 0,
	ISF_ALIVE = 1,
	ISF_DONE = 2,
};

// An expanding dotted circle, shown when spawning items. Note the slight
// semantic differences to the circle_t structure.
struct item_splash_t {
	item_splash_flag_t flag;
	char time;	// unused
	SPPoint center;
	Subpixel radius_cur;
	Subpixel radius_prev;
};

#define ITEM_SPLASH_COUNT 8
#if GAME == 5
	#define ITEM_SPLASH_DOTS 32
#else
	#define ITEM_SPLASH_DOTS 64
#endif

extern item_splash_t item_splashes[ITEM_SPLASH_COUNT];

void __fastcall near item_splash_dot_render(screen_x_t x, vram_y_t vram_y);
void near item_splashes_init(void);
void pascal near item_splashes_add(Subpixel center_x, Subpixel center_y);
void near item_splashes_update(void);
void near item_splashes_render(void);
