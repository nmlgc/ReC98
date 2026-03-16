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
	pid_t pid;
} hitbox;

// ZUN bloat: Just calling explosions_hittest() in addition to hitbox_hittest()
// at the two call sites that need it would have been cleaner and shorter than
// forcing the 15 call sites that don't need it to temporarily flip this global
// flag. (Since hitbox_hittest() only compares coordinates and doesn't receive
// an entity that it can mutate the flags of, the order of checks doesn't
// matter.)
extern bool hitbox_hittest_skip_explosions;

// Processes collisions of the following entities against the [hitbox]:
// • Shots
// • Explosions (if [hitbox_hittest_skip_explosions] is `false`)
// • Charge Shots
// • A potentially active bomb
// Returns the total amount of damage dealt.
//
// ZUN bloat: Takes [hitbox.origin.center] and [hitbox.radius] and converts
// them into [hitbox.origin.topleft], [hitbox.right], and [hitbox.bottom],
// destroying the original value of [hitbox.origin.center]. Just pass center
// and radius as parameters.
uint8_t hitbox_hittest(void);
