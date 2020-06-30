/// Constants
/// ---------
static const int PELLET_COUNT = 100;
/// ---------

enum pellet_motion_t {
};

enum pellet_sling_direction_t {
	_pellet_sling_direction_t_FORCE_INT = 0x7FFF
};

enum pellet_pattern_t {
	_pellet_pattern_t_FORCE_INT = 0x7FFF
};

struct pellet_t {
	unsigned char moving;
	unsigned char motion_type;
	Subpixel cur_left;
	Subpixel cur_top;
	SPPoint spin_center;
	Subpixel prev_left;
	Subpixel prev_top;
	pellet_pattern_t from_pattern;
	SPPoint velocity;
	SPPoint spin_velocity;
	bool16 not_rendered;
	int age;
	Subpixel speed;
	int decay_frame;
	int cloud_frame;
	int cloud_left;	// Not subpixels!
	int cloud_top; 	// Not subpixels!
	int angle;
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
};

/// Globals
/// -------
extern CPellets Pellets;
/// -------
