#include "ReC98.h"
#include "th01/math/subpixel.hpp"

// Structures
// ----------
static const int REIMU_STAR_TRAILS = 6;
static const int REIMU_STAR_NODE_COUNT = 8;
static const int MARISA_LASER_COUNT = 8;
static const int MIMA_CIRCLE_COUNT = 8;

// Generic type
struct bomb_anim_t {
	point_t pos;
	int16_t val1;
	int16_t val2;
	unsigned char angle;
	int8_t padding;
};

struct reimu_star_t {
	struct {
		Subpixel screen_x;
		Subpixel screen_y;
	} topleft;
	SPPoint velocity;
	unsigned char angle;
	int8_t padding;
};

struct marisa_laser_t {
	SPPoint center;
	int16_t unused;
	pixel_t radius;
	int16_t padding;
};

struct mima_circle_t {
	screen_point_t center;
	int16_t unused;
	pixel_t distance;
	unsigned char angle;
	int8_t padding;
};

struct yuuka_heart_t {
	screen_point_t topleft;
	int16_t unused;
	pixel_t distance;
	unsigned char angle;
	int8_t padding;
};

extern union {
	reimu_star_t reimu[REIMU_STAR_TRAILS][REIMU_STAR_NODE_COUNT];
	marisa_laser_t marisa[MARISA_LASER_COUNT];
	mima_circle_t mima[MIMA_CIRCLE_COUNT];
	yuuka_heart_t yuuka;
} bomb_anim;
// ----------
