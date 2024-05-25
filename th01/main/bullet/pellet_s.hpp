#ifndef TH01_MAIN_BULLET_PELLET_S_HPP
#define TH01_MAIN_BULLET_PELLET_S_HPP

// Much like subpixels, pellet speeds are stored pre-multiplied by 40 to allow
// an effective resolution of 0.025 pixels to be losslessly stored in an
// integer. This pre-multiplication is reverted by the pellet spawning
// functions.
typedef int pellet_speed_t;

static const pellet_speed_t PELLET_SPEED_MULTIPLIER = 40;

#define to_pellet_speed(pixel_v) \
	static_cast<pellet_speed_t>(pixel_v * PELLET_SPEED_MULTIPLIER)

#define PELLET_SPEED_LOWER_MIN to_pellet_speed(-0.375f)
#define PELLET_SPEED_RAISE_MAX to_pellet_speed(0.5f)

// Clamps the resident speed of newly fired pellets to the given maximum value
// if it's higher, then raises (sic) it by [negative_delta], down to a minimum
// of [PELLET_SPEED_LOWER_MIN].
void pellet_speed_lower(pellet_speed_t max, pellet_speed_t negative_delta);

inline void pellet_speed_lower(float max, float negative_delta) {
	pellet_speed_lower(to_pellet_speed(max), to_pellet_speed(negative_delta));
}

// Raises the resident speed of newly fired pellets by [delta], up to a
// maximum of [PELLET_SPEED_RAISE_MAX].
void pellet_speed_raise(pellet_speed_t delta);

inline void pellet_speed_raise(float delta) {
	pellet_speed_raise(to_pellet_speed(delta));
}

#endif /* TH01_MAIN_BULLET_PELLET_S_HPP */
