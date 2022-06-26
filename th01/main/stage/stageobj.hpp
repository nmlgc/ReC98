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
extern unsigned char CARD_ANIM[CARD_HP_MAX][CARD_CELS];

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
};

extern CCards cards;

extern bool16 stage_cleared;

// Processes any collision between a card and the Orb, together with any
// immediate effects of such collisions. Score points for collisions are
// granted in relation to the [stage_num].
void cards_hittest(int stage_num);

// Also sets the [stage_cleared] flag if all cards were cleared, and fires
// revenge pellets on Lunatic.
void cards_update_and_render(void);
// -----

// "Obstacles"
// -----------
// Combines bumpers, bumper bars, portals, and turrets.

struct CObstacles {
	screen_x_t *left;
	vram_y_t *top;
	obstacle_type_t *type;
	int *type_frames;
	int count;

	void new_counted() {
		if(count > 0) {
			left = new screen_x_t[count];
			top = new vram_y_t[count];
			type = new obstacle_type_t[count];
			type_frames = new int[count];
		}
	}
};

extern CObstacles obstacles;
// -----------

// Initialization
// --------------

// Loads the contents of STAGE[id].DAT, and sets [default_grp_fn] and
// [default_bgm_fn] accordingly. [id] must be ≥0 and ≤9.
void scene_init_and_load(unsigned char id);

// Copies all stage objects from VRAM page 0 to VRAM page 1.
void stageobjs_copy_0_to_1(int stage_id);

// Initializes [cards] and [obstacles] with the objects for the given
// [stage_id], using the previously loaded scene data, and renders them to the
// current VRAM page. If [first_stage_in_scene] is true, a flip-in animation
// is shown for every card.
void stageobjs_init_and_render(int stage_id);
// --------------

// Current portal state
// --------------------

extern screen_x_t portal_dst_left;
extern screen_y_t portal_dst_top;
// Additional flag on top of [orb_in_portal]. Left as true for a few more
// frames after the orb has exited a portal, to prevent it from immediately
// re-entering.
extern bool16 portals_blocked;
// --------------------

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

// Planar<ptn_plane_t> would have been enough though, since there's no alpha
// plane to be snapped from VRAM anyway... Assumed by everything to contain
// [card_count] card backgrounds first, followed by [obstacle_count] obstacle
// backgrounds.
extern ptn_t *stageobj_bgs;
extern unsigned long stageobj_bgs_size;

// Frees any previously allocated [stageobj_bgs]. Always returns 0.
bool16 stageobj_bgs_free(void);

// Blits the backgrounds for all cards and obstacles at their respective
// positions, effectively removing those sprites from VRAM.
void stageobj_bgs_put_all(void);

// Blits both the stage object background with the given [bg_slot], and the
// given [ptn_id] on top, to (⌊left/8⌋*8, top) in a single blitting operation.
void stageobj_put_8(screen_x_t left, vram_y_t top, int ptn_id, int bg_slot);

// Blits the stage object background with the given [bg_slot] to
// (⌊left/8⌋*8, top).
#define stageobj_bgs_put_8(left, top, slot) \
	stageobj_put_8(left, top, PTN_STAGEOBJ_NONE, slot)
#define PTN_STAGEOBJ_NONE 9999
// --------
