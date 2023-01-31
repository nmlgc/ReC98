// Coordinates
// -----------
// These are only really correct for bumper sprites, which have a visual width
// of exactly 24×24, but are used for cards and portals as well.

static const int STAGEOBJ_W = PTN_W;
static const int STAGEOBJ_H = PTN_H;

#ifdef ORB_HPP
	static const pixel_t STAGEOBJ_ORB_DISTANCE_X = (
		((STAGEOBJ_W * 3) / 8) + (ORB_VISUAL_W / 2)
	);
	static const pixel_t STAGEOBJ_ORB_DISTANCE_Y = (
		((STAGEOBJ_W * 3) / 8) + (ORB_VISUAL_H / 2)
	);
#endif
// -----------

#define stageobj_safe_delete(ptr) { \
	if(ptr) { \
		delete[] ptr; \
		ptr = nullptr; \
	} \
}

// Cards
// -----

enum card_flag_t {
	CARD_ALIVE = 0,	// Can be hit

	// Will transition back to CARD_ALIVE if [cards.hp] is ≥1, or to
	// CARD_REMOVED otherwise.
	CARD_FLIPPING = 1,

	CARD_REMOVED = 2,

	_card_flag_t_FORCE_INT16 = 0x7FFF
};

static const int CARD_FRAMES_PER_CEL = 6;

enum card_cel_t {
	CARD_CEL_NOT_FLIPPING = 0,
	CARD_CEL_FRONT_HALF = 1,
	CARD_CEL_EDGE = 2,
	CARD_CEL_BACK_HALF = 3,
	CARD_CEL_FLIPPED = 4,
	CARD_CELS,

	_card_cel_t_FORCE_INT16 = 0x7FFF,
};

#define card_first_frame_of(cel) \
	(cel * CARD_FRAMES_PER_CEL)

#define card_cel_at(frame) \
	(frame / CARD_FRAMES_PER_CEL)

static const int CARD_HP_MAX = 5; // STAGE?.DAT only supports up to 4, though!
extern uint8_t CARD_ANIM[CARD_HP_MAX][CARD_CELS]; // ACTUAL TYPE: main_ptn_t

static const int CARD_SCORE_CAP = 25600;

// Stored outside the class for some reason... Only valid during the card flip
// animation, and reset to 0 afterwards.
extern unsigned long *cards_score;

struct CCards {
	screen_x_t *left;
	vram_y_t *top;
	char *flag;	// card_flag_t
	int count;

	// Current frame within the CARD_FLIPPING animation.
	int *flip_frames;

	// Stored minus 1: A value of 0 indicates that the card needs to be
	// flipped one more time to remove it.
	char *hp;

	void new_counted() {
		if(count > 0) {
			left = new screen_x_t[count];
			top = new vram_y_t[count];
			flag = new char[count];
			flip_frames = new int[count];
			hp = new char[count];
			cards_score = new unsigned long[count];
		}
	}

	void free() {
		stageobj_safe_delete(left);
		stageobj_safe_delete(top);
		stageobj_safe_delete(flag);
		stageobj_safe_delete(flip_frames);
		stageobj_safe_delete(hp);
		stageobj_safe_delete(cards_score);
	}

	CCards(void) {
		count = 1; // What?!
		left = nullptr;
		top = nullptr;
		flag = nullptr;
		flip_frames = nullptr;
		hp = nullptr;
		cards_score = nullptr;
	}
};

extern CCards cards;

// Also sets the [stage_cleared] flag if all cards were cleared, and fires
// revenge pellets on Lunatic.
void cards_update_and_render(void);
// -----

// "Obstacles"
// -----------
// Combines bumpers, bumper bars, portals, and turrets.

struct CObstacles {
	union obstacle_type_frames_t {
		int since_collision;
		int fire_cycle;
		int v;
	};

	screen_x_t *left;
	vram_y_t *top;
	obstacle_type_t *type;
	obstacle_type_frames_t *frames;
	int count;

	void new_counted() {
		if(count > 0) {
			left = new screen_x_t[count];
			top = new vram_y_t[count];
			type = new obstacle_type_t[count];
			frames = new obstacle_type_frames_t[count];
		}
	}

	CObstacles(void) {
		count = 1; // What?!
		left = nullptr;
		top = nullptr;
		type = nullptr;
		frames = nullptr;
	}

	void free() {
		stageobj_safe_delete(left);
		stageobj_safe_delete(top);
		stageobj_safe_delete(type);
		stageobj_safe_delete(frames);
	}
};

extern CObstacles obstacles;

// Processes collisions between the Orb and any bumpers, bumper bars, or
// portals, and handles turret firing on difficulties above Easy. Note that any
// resetting happens after the regular update and rendering code.
void obstacles_update_and_render(bool16 reset);
// -----------

// Initialization
// --------------

#ifdef DECOMP_HPP
	struct stage_t {
		StupidBytewiseWrapperAround<stagedat_stage_t> dat;
		int8_t padding[5];
	};
#endif

// Copies all stage objects from VRAM page 0 to VRAM page 1.
void stageobjs_copy_0_to_1(int stage_id);

// Initializes [cards] and [obstacles] with the objects for the given
// [stage_id], using the previously loaded scene data, and renders them to the
// current VRAM page. If [first_stage_in_scene] is true, a flip-in animation
// is shown for every card.
// ZUN quirk: [stage_id] is taken % STAGES_PER_SCENE, but the function doesn't
// check against negative numbers. Passing one will show one of five
// deterministic "glitch stages".
void stageobjs_init_and_render(int stage_id);
// --------------

// Blitting
// --------

// Stationary stage objects are blitted to both VRAM pages, which makes it
// possible to efficiently unblit the other entities moving on top of them, by
// simply restoring pixels from VRAM page 1. Since the player can remove
// cards though, the backgrounds behind them also need to be stored somewhere.
// Storing only the 32×32 regions covered by the cards minimizes the memory
// needed for this, and doesn't require the full background .GRP to be stored
// in memory… which the PiLoad library can't do anyway.
// Since obstacles also need to be removed during a stage transition, their
// backgrounds are stored as well. This makes absolutely sure that a .GRP only
// needs to be blitted a single time, when entering a new scene.
//
// Planar<ptn_plane_t> would have been enough though, since there's no alpha
// plane to be snapped from VRAM anyway... Assumed by everything to contain
// [card_count] card backgrounds first, followed by [obstacle_count] obstacle
// backgrounds.
extern ptn_t *stageobj_bgs;

extern unsigned long stageobj_bgs_size;

// Frees any previously allocated [stageobj_bgs]. Always returns 0.
bool16 stageobj_bgs_free(void);
bool16 stageobj_bgs_free_wrap(void); // ZUN bloat: Just call the real function.

// Blits the backgrounds for all cards and obstacles at their respective
// positions, effectively removing those sprites from VRAM.
void stageobj_bgs_put_all(void);

// Blits both the stage object background with the given [bg_slot], and the
// given [ptn_id] on top, to (⌊left/8⌋*8, top) in a single blitting operation.
void stageobj_put_bg_and_obj_8(
	screen_x_t left, vram_y_t top, int ptn_id, int bg_slot
);

// Blits the stage object background with the given [bg_slot] to
// (⌊left/8⌋*8, top).
#define stageobj_bgs_put_8(left, top, slot) \
	stageobj_put_bg_and_obj_8(left, top, PTN_STAGEOBJ_NONE, slot)
#define PTN_STAGEOBJ_NONE 9999
// --------
