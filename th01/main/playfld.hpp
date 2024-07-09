#ifndef TH01_MAIN_PLAYFLD_HPP
#define TH01_MAIN_PLAYFLD_HPP

#include "pc98.h"

#if (GAME == 1)
	static const screen_x_t PLAYFIELD_LEFT = 0;
	static const screen_y_t PLAYFIELD_TOP = 64;
	static const screen_x_t PLAYFIELD_RIGHT = RES_X;
	static const screen_y_t PLAYFIELD_BOTTOM = RES_Y;

	static const pixel_t PLAYFIELD_W = (PLAYFIELD_RIGHT - PLAYFIELD_LEFT);
	static const pixel_t PLAYFIELD_H = (PLAYFIELD_BOTTOM - PLAYFIELD_TOP);

	static const screen_x_t PLAYFIELD_CENTER_X = (
		((PLAYFIELD_RIGHT - PLAYFIELD_LEFT) / 2) + PLAYFIELD_LEFT
	);

	static const screen_y_t PLAYFIELD_CENTER_Y = (
		((PLAYFIELD_BOTTOM - PLAYFIELD_TOP) / 2) + PLAYFIELD_TOP
	);
#endif

static inline pixel_t playfield_fraction_x(float fraction = 1.0f) {
	// Adding a small value helps with rounding inaccuracies.
	return static_cast<pixel_t>(PLAYFIELD_W * fraction + 0.0001f);
}

static inline pixel_t playfield_fraction_y(float fraction = 1.0f) {
	// Adding a small value helps with rounding inaccuracies.
	return static_cast<pixel_t>(PLAYFIELD_H * fraction + 0.0001f);
}

#if (GAME == 1)
#include "libs/master.lib/master.hpp"

// Calculates a random X position between the given minimum and maximum
// fractions of the playfield width.
static inline screen_x_t playfield_rand_x(
	float fraction_min = 0.0f, float fraction_max = 1.0f
) {
	return (PLAYFIELD_LEFT + playfield_fraction_x(fraction_min) + (
		(irand() % playfield_fraction_x(fraction_max - fraction_min))
	));
}

// Calculates a random Y position between the given minimum and maximum
// fractions of the playfield height.
static inline screen_y_t playfield_rand_y(
	float fraction_min = 0.0f, float fraction_max = 1.0f
) {
	return (PLAYFIELD_TOP + playfield_fraction_y(fraction_min) + (
		(irand() % playfield_fraction_y(fraction_max - fraction_min))
	));
}
#endif

#endif /* TH01_MAIN_PLAYFLD_HPP */
