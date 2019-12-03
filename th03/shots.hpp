#define SHOT_VELOCITY -12.0f
#define SHOT_SO_PID (320 / 8)

#define SHOT_SPRITE_COUNT 4
#define SHOT_W 16
#define SHOT_H 8
#define SHOT_VRAM_W (SHOT_W / 8)
#define SHOT_VRAM_H (SHOT_H / 2)

struct shotpair_t {
	char flag;
	char unused_1;
	SPPoint topleft;
	Subpixel velocity_y;
	unsigned int so_pid;
	unsigned char so_anim;
	char unused_2;
	unsigned char pid;
	char unused_3;
};

#define SHOTPAIR_DISTANCE 16
#define SHOTPAIR_COUNT 32

extern shotpair_t shotpairs[SHOTPAIR_COUNT];

void pascal near shots_update(void);
void pascal near shots_render(void);
