// Card-related stuff that got a separate translation unit, for some reason
// ------------------------------------------------------------------------

#include "platform.h"

static const uint8_t CARD_FLIP_CYCLE_INITIAL_MAX = 60;
static const uint8_t CARD_FLIP_CYCLE_MAX = 140;

extern uint8_t card_flip_cycle;

// Processes any collision between a card and the Orb, together with any
// immediate effects of such collisions. Score points for collisions are
// granted in relation to the [stage_id].
void cards_hittest(int stage_id);

// Also sets the [stage_cleared] flag if all cards were cleared, and fires
// revenge pellets on Lunatic.
void cards_update_and_render(void);
// ------------------------------------------------------------------------
