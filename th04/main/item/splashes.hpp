// An expanding dotted circle, shown when spawning items. Note the slight
// semantic differences to the circle_t structure.
struct item_splash_t {
	char flag;
	char time;	// unused
	SPPoint center;
	Subpixel radius_cur;
	Subpixel radius_prev;
};

#define ITEM_SPLASH_COUNT 8
#if GAME == 5
# define ITEM_SPLASH_DOTS 32
#else
# define ITEM_SPLASH_DOTS 64
#endif
#define ITEM_SPLASH_RADIUS_START 2
#define ITEM_SPLASH_RADIUS_DELTA 2
#define ITEM_SPLASH_RADIUS_END 32

extern item_splash_t item_splashes[ITEM_SPLASH_COUNT];
extern unsigned char item_splash_last_id;

void __fastcall near item_splash_dot_render(screen_x_t x, vram_y_t vram_y);
void pascal near item_splashes_init(void);
void pascal near item_splashes_add(Subpixel x, Subpixel y);
void pascal near item_splashes_update(void);
void pascal near item_splashes_render(void);
