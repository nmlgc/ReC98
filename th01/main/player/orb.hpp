static const pixel_t ORB_W = 32;
static const pixel_t ORB_H = 32;

static const pixel_t ORB_HITBOX_W = (ORB_W / 2);
static const pixel_t ORB_HITBOX_H = (ORB_W / 2);

static const pixel_t ORB_HITBOX_LEFT   = ((ORB_W / 2) - (ORB_HITBOX_W / 2));
static const pixel_t ORB_HITBOX_TOP    = ((ORB_H / 2) - (ORB_HITBOX_H / 2));
static const pixel_t ORB_HITBOX_RIGHT  = ((ORB_W / 2) + (ORB_HITBOX_W / 2));
static const pixel_t ORB_HITBOX_BOTTOM = ((ORB_H / 2) + (ORB_HITBOX_H / 2));

static const screen_x_t ORB_LEFT_MIN = (PLAYFIELD_LEFT);
static const screen_x_t ORB_LEFT_MAX = (PLAYFIELD_RIGHT - ORB_W);
static const screen_y_t ORB_TOP_MIN = (PLAYFIELD_TOP);
static const screen_y_t ORB_TOP_MAX = (PLAYFIELD_BOTTOM - ORB_H);

static const screen_x_t ORB_LEFT_START = (ORB_LEFT_MAX -  8);
static const screen_y_t  ORB_TOP_START = ( ORB_TOP_MAX - 88);
#define ORB_FORCE_START -8.0

extern screen_x_t orb_cur_left;
extern screen_y_t orb_cur_top;
extern screen_x_t orb_prev_left;
extern screen_y_t orb_prev_top;
extern bool16 orb_in_portal;

/// Physics
/// -------
enum orb_velocity_x_t {
	OVX_0 = 0,
	OVX_4_LEFT = 1,
	OVX_4_RIGHT = 2,
	OVX_8_LEFT = 3,
	OVX_8_RIGHT = 4,

	_orb_velocity_x_t_FORCE_INT16 = 0x7FFF
};

enum orb_force_t {
	OF_BOUNCE_FROM_GROUND = 0,
	OF_BOUNCE_FROM_TOP = 1,
	OF_SHOT = 2,
	OF_IMMEDIATE = 3, // new force passed directly in [immediate]

	_orb_force_t_FORCE_INT16 = 0x7FFF
};

// Initial value of the current force acting on the orb
extern double orb_force;

// Number of frames that [orb_force] has been acting on the orb
extern int orb_force_frame;

extern orb_velocity_x_t orb_velocity_x;
extern double orb_velocity_y;

// Applies a new force of the given type onto the orb. Sets [orb_force], and
// resets [orb_force_frame].
void orb_force_new(double immediate, orb_force_t force);

// Updates [orb_velocity_y] with the currently active force, and returns the
// orb's velocity for this frame, in pixels to be added to [orb_cur_top].
int orb_velocity_y_update(void);

// Updates [orb_cur_left] depending on the passed [velocity_x], *as well as*
// the global [orb_velocity_x] (!) to bounce the orb off the left or right
// edge of the playfield, if necessary.
void orb_move_x(orb_velocity_x_t velocity_x);
/// -------

static const int ORB_FORCE_REPEL = -13;

enum orb_repel_friction_t {
	OR_NONE = 0, // No repulsion, kills player on collision
	OR_MAX = (-ORB_FORCE_REPEL * 2),

	// Wouldn't it be cool if those *exactly* matched the orb_velocity_x_t
	// order?
	OR_3_X_UNCHANGED = 100,
	OR_3_X_4_LEFT = 101,
	OR_3_X_4_RIGHT = 102,
	OR_3_X_8_RIGHT = 103,
	OR_3_X_8_LEFT = 104,
};

// Processes any collision between the Orb and the player. If a friction is
// given (either from orb_repel_friction_t or as an immediate force), the Orb
// is repelled with [ORB_FORCE_REPEL] minus the given friction. Make sure that
// number is below OR_MAX, otherwise the new force will end up pointing into
// the ground.
void orb_player_hittest(int repel_friction);
