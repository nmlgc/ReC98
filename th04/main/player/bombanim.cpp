// Star animation
// --------------
static const int BOMB_STAR_COUNT = 48;
static const pixel_t BOMB_STAR_W = 16;
static const pixel_t BOMB_STAR_H = 16;

struct bomb_star_t {
	SPPoint center;
	unsigned char angle;
	SubpixelLength8 speed;
};

extern bomb_star_t bomb_stars[BOMB_STAR_COUNT];

void pascal near bomb_stars_update_and_render_for(playchars_t playchar)
;
// --------------
