/// Everything here needs to be kept in sync with the ASM versions in
/// gather.inc!

enum gather_flag_t {
	GF_FREE = 0,
	GF_ALIVE = 1,
	GF_DONE = 2,

	_gather_flag_t_FORCE_UINT8 = 0xFF
};

// Shrinking gather circles. Can fire bullets according to the included
// template once their radius reaches GATHER_RADIUS_END, unless
// [bullet_template.spawn_type] is set to BST_GATHER_ONLY.
struct gather_t {
	gather_flag_t flag;
	uint4_t col;
	PlayfieldMotion center;
	Subpixel radius_cur;
	int ring_points;
	// Added to the automatically calculated angle of each ring point
	unsigned char angle_cur;
	// Added to [angle_cur] every frame
	unsigned char angle_delta;
#if GAME == 4
	bullet_template_t bullet_template;
#endif
	Subpixel radius_prev; // never read
	// *Subtracted* from [radius_cur] every frame
	Subpixel radius_delta;
#if GAME == 5
	bullet_template_t bullet_template;
#endif
};

struct gather_template_t {
	SPPoint center;
	SPPoint velocity;
	Subpixel radius;
	int ring_points;
	uint4_t col;
	unsigned char angle_delta;
};

#define GATHER_POINT_W 8
#define GATHER_POINT_H 8
#define GATHER_FRAMES 32
#define GATHER_RADIUS_START 64.0f
#define GATHER_RADIUS_END to_sp(2.0f)

#define GATHER_COUNT 16
#if GAME == 5
# define GATHER_CAP 8
#else
# define GATHER_CAP GATHER_COUNT
#endif

extern gather_t gather_circles[GATHER_COUNT];
extern gather_template_t gather_template;

// Adds a gather circle based on the current global [gather_template], with a
// copy of the current global [bullet_template]. These bullets will be fired
// once the new circle's radius reaches GATHER_RADIUS_END.
void near gather_add_bullets(void);

// Adds a gather circle based on the current global [gather_template] which
// won't fire bullets at GATHER_RADIUS_END.
void near gather_add_only(void);

// Calls gather_add_only() to add one of the three circles in a 3-stack gather
// animation, based on the value of [frame]. The three circles are added at
// [frame] 0, 2, and 4, respectively, using the given colors. Will do nothing
// for any other value of [frame].
void pascal near gather_add_only_3stack(
	int frame, int col_for_0, int col_for_2_and_4
);

// Blits the gather point sprite to ([left], [top]). Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
void __fastcall near gather_point_render(screen_x_t left, vram_y_t top);

void gather_update(void);
void gather_render(void);
