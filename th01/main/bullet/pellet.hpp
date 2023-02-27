/// Constants
/// ---------
static const int PELLET_COUNT = 100;

static const unsigned char PELLET_SLING_DELTA_ANGLE = +0x08;
static const unsigned char PELLET_SPIN_DELTA_ANGLE = +0x04;
#define PELLET_SPIN_CIRCLE_RADIUS to_sp(16.0f)
#define PELLET_CHASE_TOP_MAX to_sp(PLAYFIELD_BOTTOM - 80.0f)
/// ---------

enum pellet_motion_t {
	// No velocity change during regular pellet updates.
	PM_REGULAR = 0,

	// Accelerates the Y velocity of the pellet by its [speed] every frame.
	// Exclusively used with the pellets_add_single_rain() helper function.
	PM_GRAVITY = 1,

	// Slings the pellet in a (counter-)clockwise motion around its spawn
	// point, with a sling radius of [speed] and a rotational speed of
	// [PELLET_SLING_DELTA_ANGLE]° per frame. Once the pellet completed one
	// full revolution, it is fired towards the player's position on that
	// frame, in a straight line at the same [speed].
	PM_SLING_AIMED = 2,

	// Behaves like PM_REGULAR until the pellet reaches the top of the
	// playfield. There, it bounces off by negating its X velocity, and zeroing
	// its Y velocity before switching to PM_GRAVITY.
	// Unused in the original game. Should have bounced the bullets off the
	// left and right edge of the playfield as well, but that part doesn't
	// actually work in ZUN's original code.
	PM_BOUNCE_FROM_TOP_THEN_GRAVITY = 3,

	// Behaves like PM_REGULAR until the pellet reaches the top of the
	// playfield. There, it zeroes its X velocity and sets its Y velocity to
	// [speed] before switching to PM_REGULAR.
	PM_FALL_STRAIGHT_FROM_TOP_THEN_REGULAR = 4,

	// Spins the pellet on a circle around a [spin_center] point, which moves
	// at [spin_velocity], with [PELLET_SPIN_CIRCLE_RADIUS] and a rotational
	// speed of [PELLET_SPIN_DELTA_ANGLE]° per frame. Since both the center of
	// rotation and the angle are changed every frame, this will result in a
	// swerving motion for individual pellets. Use this type for a ring of
	// pellets to create moving multi-bullet circles, as seen in the Kikuri
	// fight.
	PM_SPIN = 5,

	// For every frame this pellet is above [PELLET_CHASE_TOP_MAX], its
	// velocity is adjusted by -1, 0, or +1 in both coordinates, depending on
	// the location of the player relative to this pellet.
	PM_CHASE = 6,

	_pellet_motion_t_FORCE_INT16 = 0x7FFF
};

enum pellet_sling_direction_t {
	PSD_NONE = 0,
	PSD_CLOCKWISE = 1,
	PSD_COUNTERCLOCKWISE = 2,

	_pellet_sling_direction_t_FORCE_INT16 = 0x7FFF
};

// Types for predefined multi-pellet groups. In TH01, individual bullets of
// such a group only differ in their angle.
//
// The PG_?_ number indicates the number of pellets created by this group.
//
// All groups (including the random-angle ones) are symmetrical around
// • a (0, 1) vector, pointing downwards (for static groups)
// • a vector from the pellet's origin to the player (for aimed groups)
// Odd-numbered spreads always contain a pellet in the center, which moves
// along this axis of symmetry; even-numbered spreads don't.
//
// For aimed groups, this means that:
// • spreads with  odd numbers of pellets are aimed *at* the player, while
// • spreads with even numbers of pellets are aimed *around* the player.
enum pellet_group_t {
	// Not a valid pellet type, due to a potential ZUN bug in
	// group_velocity_set()!
	PG_NONE = 0,

	PG_1 = 1,
	PG_1_AIMED = 12,

	PG_2_SPREAD_WIDE,
	PG_2_SPREAD_NARROW,
	PG_3_SPREAD_WIDE,
	PG_3_SPREAD_NARROW,
	PG_4_SPREAD_WIDE,
	PG_4_SPREAD_NARROW,
	PG_5_SPREAD_WIDE,
	PG_5_SPREAD_NARROW,

	// Aimed versions of the n-way spreads above. Expected to have enum values
	// >= this one!
	PG_AIMED_SPREADS,

	PG_2_SPREAD_WIDE_AIMED = PG_AIMED_SPREADS,
	PG_2_SPREAD_NARROW_AIMED,
	PG_3_SPREAD_WIDE_AIMED,
	PG_3_SPREAD_NARROW_AIMED,
	PG_4_SPREAD_WIDE_AIMED,
	PG_4_SPREAD_NARROW_AIMED,
	PG_5_SPREAD_WIDE_AIMED,
	PG_5_SPREAD_NARROW_AIMED,

	// -11.25 deg to +11.25 deg, around the player
	PG_1_RANDOM_NARROW_AIMED = 29,
	// -45 deg to +45 deg, facing down
	PG_1_RANDOM_WIDE = 30,

	_pellet_group_t_FORCE_INT16 = 0x7FFF
};

struct Pellet {
	bool moving;
	unsigned char motion_type;

	// Automatically calculated every frame for PM_SPIN
	Subpixel cur_left;
	Subpixel cur_top;

	SPPoint spin_center; // only used for PM_SPIN
	Subpixel prev_left;
	Subpixel prev_top;
	pellet_group_t from_group;
	SPPoint velocity; // unused for PM_SPIN
	SPPoint spin_velocity; // only used for PM_SPIN

	// Used only for poor attempts at reducing flickering. Does not disable
	// hit testing if true.
	bool not_rendered;

	Subpixel speed; // for recalculating velocities with certain motion types
	int decay_frame;
	int cloud_frame;
	screen_x_t cloud_left;	// Not subpixels!
	screen_y_t cloud_top; 	// Not subpixels!
	int angle;	// for recalculating velocities with certain motion types

	// Direction for PM_SLING_AIMED. Not reset when a pellet is destroyed -
	// and therefore effectively only calculated once for every instance of
	// this structure.
	pellet_sling_direction_t sling_direction;
};

class CPellets {
	Pellet near pellets[PELLET_COUNT];
	int alive_count; // only used for one single optimization

public:
	// Rendering pellets at odd or even indices this frame?
	bool interlace_field;
	bool spawn_with_cloud;

protected:
	Pellet near* iteration_start(void) {
		return static_cast<Pellet near *>(pellets);
	}

	// Updates the velocity of the currently iterated pellet, depending on its
	// [motion_type].
	void motion_type_apply_for_cur(void);

	void decay_tick_for_cur(void);
	bool hittest_player_for_cur(void);

	// Processes any collision between the currently iterated pellet, the Orb,
	// or a deflecting player. (Regular, life-losing hit testing between
	// pellets and the player is done elsewhere!)
	// Returns true if the bullet remains visible.
	//
	// (And yes, this function does operate on the currently iterated pellet,
	// despite taking separate position parameters!)
	bool visible_after_hittests_for_cur(
		screen_x_t pellet_left, screen_y_t pellet_top
	);

	void clouds_unput_update_render(void);

public:
	CPellets(void);

	// Spawns a number of bullets according to the given [group], with their
	// corresponding velocities, at (left, top). [speed_base] is tuned
	// according to the currently played difficulty and the resident
	// [pellet_speed]. The [motion_type] for the new pellets is PM_REGULAR.
	void add_group(
		screen_x_t left,
		screen_y_t top,
		pellet_group_t group,
		subpixel_t speed_base
	);

	// Spawns a single new pellet with a customizable [motion_type].
	// [speed_base] is tuned according to the currently played difficulty and
	// the resident [pellet_speed]; [speed_for_motion_fixed] is never tuned.
	//
	// [spin_center_x] and [spin_center_y] are only used with PM_SPIN,
	// while [speed_base] is *ignored* for PM_SPIN and PM_SLING_AIMED.
	void add_single(
		screen_x_t left,
		screen_y_t top,
		unsigned char angle,
		subpixel_t speed_base,
		pellet_motion_t motion_type = PM_REGULAR,
		subpixel_t speed_for_motion_fixed = to_sp(0.0f),
		screen_x_t spin_center_x = 0,
		screen_y_t spin_center_y = 0
	);

	// Transitions all living pellets into their decay state, awarding score
	// points for each one.
	void decay(void);

	void unput(void);

	// Also calls Shots.unput_update_render()!
	void unput_update_render(void);

	void unput_and_reset(void);
	void reset(void);
};

/// Globals
/// -------
extern CPellets Pellets;

// Helper function for rain pellets.
#define pellets_add_single_rain(left, top, angle, speed_base) { \
	Pellets.add_single( \
		left, top, angle, to_sp(speed_base), PM_GRAVITY, to_sp(0.0625f) \
	); \
}

// If true, CPellets::unput_update_render() performs
// • rendering,
// • hit testing against the Orb,
// • and deflection testing against the player
// for only half of the [Pellets] each frame, alternating between even and odd
// [Pellets] array indices. However,
// • motion updates,
// • life-losing hit testing against the player
// • and hit testing against player shots
// are still done for all pellets every frame.
//
// Probably not really meant to save CPU and/or VRAM accesses, but rather to
// reduce flicker in busy boss battles, due to all the sloppy unblitting...
extern bool pellet_interlace;

extern unsigned int pellet_destroy_score_delta;
/// -------
