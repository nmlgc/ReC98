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
		return (v >> (8 + BYTE_BITS));
	}
};
/// ------------------------

class CShootoutLaser {
	enum put_flag_t {
		SL_RAY_UNPUT = false,
		SL_RAY_PUT = true,
	};

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
	LaserPixel step_y;	// per ray pixel, [-1.0, +1.0]
	LaserPixel step_x;	// per ray pixel, [-1.0, +1.0]
	pixel_t ray_extend_speed;
	int age;

	// At this [age], [ray_extend_speed] stops being added to [ray_length],
	// and [ray_start_*] starts being moved by [ray_moveout_speed] instead.
	int moveout_at_age;

	unsigned char col;
	unsigned char width_cel;
	bool alive;
	bool damaging;

protected:
	void hittest_and_render(put_flag_t put_flag);

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
};

extern CShootoutLaser shootout_lasers[SHOOTOUT_LASER_COUNT];

// Quite a roundabout way of preventing buffer overflows, but fine.
#define shootout_laser_safe(i) \
	shootout_lasers[(i) % SHOOTOUT_LASER_COUNT]

// Resets all lasers, but leaves them in VRAM. The boss defeat animation is
// supposed to get rid of them.
void shootout_lasers_reset(void);
