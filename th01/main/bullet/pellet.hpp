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
	PM_NORMAL = 0,

	// Accelerates the Y velocity of the pellet by its [speed] every frame.
	PM_GRAVITY = 1,

	// Slings the pellet in a (counter-)clockwise motion around its spawn
	// point, with a sling radius of [speed] and a rotational speed of
	// [PELLET_SLING_DELTA_ANGLE]° per frame. Once the pellet completed one
	// full revolution, it is fired towards the player's position on that
	// frame, in a straight line at the same [speed].
	PM_SLING_AIMED = 2,

	// Lets the pellet bounce off the top of the playfield once, negating its
	// X velocity, and zeroing its Y velocity. The pellet then switches to
	// PM_GRAVITY.
	// Unused in the original game. Should have bounced the bullets off the
	// left and right edge of the playfield as well, but that code doesn't
	// actually work in ZUN's original code.
	PM_BOUNCE_FROM_TOP_THEN_GRAVITY = 3,

	// Lets the pellet bounce off the top of the playfield once, zeroing its
	// X velocity, and setting its Y velocity to [speed]. The pellet then
	// switches to PM_NORMAL.
	PM_FALL_STRAIGHT_FROM_TOP_THEN_NORMAL = 4,

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

	_pellet_motion_t_FORCE_INT = 0x7FFF
};

enum pellet_sling_direction_t {
	PSD_NONE = 0,
	PSD_CLOCKWISE = 1,
	PSD_COUNTERCLOCKWISE = 2,

	_pellet_sling_direction_t_FORCE_INT = 0x7FFF
};

enum pellet_pattern_t {
	_pellet_pattern_t_FORCE_INT = 0x7FFF
};

struct pellet_t {
	unsigned char moving;
	unsigned char motion_type;

	// Automatically calculated every frame for PM_SPIN
	Subpixel cur_left;
	Subpixel cur_top;

	SPPoint spin_center; // only used for PM_SPIN
	Subpixel prev_left;
	Subpixel prev_top;
	pellet_pattern_t from_pattern;
	SPPoint velocity; // unused for PM_SPIN
	SPPoint spin_velocity; // only used for PM_SPIN
	bool16 not_rendered;
	int age;
	Subpixel speed; // for recalculating velocities with certain motion types
	int decay_frame;
	int cloud_frame;
	int cloud_left;	// Not subpixels!
	int cloud_top; 	// Not subpixels!
	int angle;	// for recalculating velocities with certain motion types

	// Direction for PM_SLING_AIMED. Not reset when a pellet is destroyed -
	// and therefore effectively only calculated once for every instance of
	// this structure.
	pellet_sling_direction_t sling_direction;
};

class CPellets {
	pellet_t near pellets[PELLET_COUNT];
	int alive_count; // only used for one single optimization
	int unknown_zero[10];
public:
	int unknown_seven;
	bool16 interlace_field;
	bool spawn_with_cloud;

protected:
	// Updates the velocity of the currently iterated pellet, depending on its
	// [motion_type].
	void motion_type_apply_for_cur(void);
};

/// Globals
/// -------
extern CPellets Pellets;
/// -------
