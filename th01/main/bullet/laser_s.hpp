static const int SHOOTOUT_LASER_COUNT = 10;

/// Q24.8 fixed-point format
/// ------------------------
// This format matches the precision of master.lib's [SinTable8] and
// [CosTable8] lookup tables, and directly maps its values to the range of
// [-1.0, +1.0].

typedef int32_t laser_pixel_t;

inline laser_pixel_t to_laser_pixel(pixel_t pixel_v) {
	return (static_cast<laser_pixel_t>(pixel_v) << 8);
}

class LaserPixel {
public:
	// Code generation will require direct access to [v], if performing
	// arithmetic with a local variable...
	laser_pixel_t v;

	int32_t to_pixel() const {
		return (v >> 8);
	}

	int32_t to_vram_byte_amount() const {
		return (v >> 11);
	}
};
/// ------------------------

class CShootoutLaser {
public:
	LaserPixel origin_left;
	LaserPixel origin_y;
	LaserPixel ray_start_left;
	LaserPixel ray_start_y;

protected:
	// For internal iteration over each ray segment
	LaserPixel ray_i_left;
	LaserPixel ray_i_y;

public:
	pixel_t ray_length;
	pixel_t ray_moveout_speed;
	screen_x_t target_left;	// unused
	vram_y_t target_y;	// unused
	int unknown;	// unused
	int32_t unused_1;
	LaserPixel velocity_y;	// per frame, unused
	LaserPixel step_y;	// per ray pixel, [-1.0, +1.0]
	LaserPixel velocity_x;	// per frame, unused
	LaserPixel step_x;	// per ray pixel, [-1.0, +1.0]
	pixel_t ray_extend_speed;
	int16_t unused_2;
	bool16 alive;
	int age;

	// At this [age], [ray_extend_speed] stops being added to [ray_length],
	// and [ray_start_*] starts being moved by [ray_moveout_speed] instead.
	int moveout_at_age;

	unsigned char col;
	unsigned char width_cel;
	bool damaging;
	char id;	// unused

	CShootoutLaser() {
		alive = false;
	}

protected:
	// MODDERS: Just turn into a parameter of hittest_and_render().
	enum { SL_RAY_UNPUT = false, SL_RAY_PUT = true } put_flag;

	void hittest_and_render(void);

public:
	// Does nothing if this laser is already [alive], and patterns do rely on
	// that behavior. No idea why the speed has to be passed like that - the
	// function simply divides it by 8, losing any extended precision. *shrug*
	void spawn(
		screen_x_t origin_left,
		vram_y_t origin_y,
		screen_x_t target_left,
		vram_y_t target_y,
		int speed_multiplied_by_8,
		int col,
		int moveout_at_age,
		int w
	);

	// Directly sets [done] if the laser collides with the player.
	void update_hittest_and_render(void);

	// Tries to unblit the entire laser, but fails hilariously and potentially
	// even crashes the game.
	void unput_and_reset(void) {
		if(alive) {
			// Two ZUN bugs here:
			//
			// 1) Surely this should have unblitted from the start to the end
			//    of the ray instead? Except that this class doesn't explicitly
			//    store that end point… so the best alternative would be the
			//    target point. But given that we use our own blitting routine,
			//    who knows how accurate that actually is?
			//
			// 2) graph_r_line_unput() takes screen_x_t and vram_y_t, not
			//    LaserPixels truncated to 16-bits. :zunpet: The function then
			//    interpolates and clips these values in a rather clumsy
			//    attempt to find a line segment between those garbage
			//    coordinates that actually falls within the boundaries of
			//    VRAM. At best, this search fails, and the function simply
			//    does nothing. At worst, the resulting line triggers the ZUN
			//    bugs in graph_r_line_unput(), raising a General Protection
			//    Fault.
			//    The latter is exactly the cause behind potential crashes when
			//    defeating bosses while there are diagonally moving lasers on
			//    screen, which are most commonly reported for Elis and Mima.
			//
			// So yeah, not doing anything would have been the much better
			// choice.
			graph_r_line_unput(
				ray_start_left.v, ray_start_y.v, origin_left.v, origin_y.v
			);

			alive = false;
		}
	}
};

extern CShootoutLaser shootout_lasers[SHOOTOUT_LASER_COUNT];

#define shootout_lasers_init(i) { \
	for(i = 0; i < SHOOTOUT_LASER_COUNT; i++) { \
		int id = i; \
		shootout_lasers[i].id = id; \
	} \
}

// Quite a roundabout way of preventing buffer overflows, but fine.
#define shootout_laser_safe(i) \
	shootout_lasers[(i) % SHOOTOUT_LASER_COUNT]

#define shootout_lasers_unput_and_reset_broken(i, count) { \
	for(i = 0; i < count; i++) { \
		shootout_lasers[i].unput_and_reset(); \
	} \
}
