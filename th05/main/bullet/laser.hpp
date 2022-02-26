enum laser_flag_t {
	LF_FREE = 0,
	LF_SHOOTOUT = 1,
	LF_FIXED_WAIT_TO_GROW = 2,
	LF_FIXED_GROW = 3,

	// Fixed laser has reached its target width and will now actually kill the
	// player on contact.
	LF_FIXED_ACTIVE = 4,

	LF_FIXED_SHRINK = 5,
	LF_FIXED_SHRINK_AND_WAIT_TO_GROW = 6,
	LF_DECAY = 7,
};

struct laser_coords_t {
	PlayfieldPoint origin;

	// Start and end point on the infinite [angle]° line starting at [origin]
	// that make up the actually rendered (and damaging) laser.
	Subpixel starts_at_distance;
	Subpixel ends_at_distance;

	unsigned char angle;
	unsigned char width; // pixel_t
};

struct laser_t {
	laser_flag_t flag;
	uint4_t col;
	laser_coords_t coords;
	Subpixel shootout_speed;
	int age;
	union {
		// [age] at which a fixed laser should transition from
		// LF_FIXED_WAIT_TO_GROW to LF_FIXED_GROW.
		int grow;
		// [age] at which a shoot-out laser should stop growing and start
		// moving along the infinite [angle]° line.
		int moveout;
	} active_at_age;

	// [age] at which a fixed laser should transition from LF_FIXED_ACTIVE to
	// LF_FIXED_SHRINK.
	int shrink_at_age;
	// [width] (in pixels) at which a fixed laser should transition from
	// LF_FIXED_GROW to LF_FIXED_ACTIVE.
	uint8_t grow_to_width;
	uint8_t padding[3];
};

#define LASER_COUNT 32

extern laser_t lasers[LASER_COUNT];
extern laser_t laser_template;

/// Control
/// -------
/// "Manual" lasers ignore any age fields from the laser template.

// Spawns a new shoot-out laser based on the [laser_template].
void near lasers_shootout_add(void);

// Creates a new fixed laser based on the [laser_template] in the given [slot]
// if that one is currently empty.
void pascal near laser_fixed_spawn(int slot);

// Creates a new fixed, manually controlled laser based on the [laser_template]
// in the given [slot] if that one is currently empty.
void pascal near laser_manual_fixed_spawn(int slot);

// Starts the growing phase of the manually controlled fixed laser at [slot].
void pascal near laser_manual_grow(int slot);

// Transitions the laser at [slot] to a stopping phase appropriate for its
// current one.
void pascal near laser_stop(int slot);
/// -------

// Returns `true` if the laser is entirely off-screen.
bool16 pascal near laser_render_ray(laser_coords_t near *coords);

// Processes any collision between the given [laser] and the player.
void pascal near laser_hittest(laser_t near &laser);

void near lasers_update(void);
void near lasers_render(void);
