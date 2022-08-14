// Card-related stuff that got a separate translation unit, for some reason
// ------------------------------------------------------------------------

extern unsigned char card_flip_cycle;

// Processes any collision between a card and the Orb, together with any
// immediate effects of such collisions. Score points for collisions are
// granted in relation to the [stage_id].
void cards_hittest(int stage_id);

// Also sets the [stage_cleared] flag if all cards were cleared, and fires
// revenge pellets on Lunatic.
void cards_update_and_render(void);
// ------------------------------------------------------------------------
