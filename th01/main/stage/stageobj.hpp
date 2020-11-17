// Cards
// -----

enum card_flag_t {
	CARD_ALIVE = 0,	// Can be hit

	// Will transition back to CARD_ALIVE if [cards.hp] is ≥1, or to
	// CARD_REMOVED otherwise.
	CARD_FLIPPING = 1,

	CARD_REMOVED = 2,
};

struct CCards {
	screen_x_t *left;
	vram_y_t *top;
	card_flag_t *flag;
	int count;

	// Current frame within the CARD_FLIPPING animation.
	int *flip_frames;

	// Stored minus 1: A value of 0 indicates that the card needs to be
	// flipped one more time to remove it.
	char *hp;
};

extern CCards cards;
// -----

// Portals
// -------

extern screen_x_t portal_dst_left;
extern screen_y_t portal_dst_top;
// Additional flag on top of [orb_in_portal]. Left as true for a few more
// frames after the orb has exited a portal, to prevent it from immediately
// re-entering.
extern bool16 portals_blocked;
// -------
