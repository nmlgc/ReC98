#include "th03/main/playfld.hpp"

// A shared global hitbox.
extern struct {
	// ZUN bloat: Use separate variables.
	union {
		PlayfieldPoint topleft;
		PlayfieldPoint center;
	} origin;

	PlayfieldPoint radius;
	PlayfieldSubpixel right;
	PlayfieldSubpixel bottom;
} hitbox;
