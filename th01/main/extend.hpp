#include "th01/score.h"

static const score_t SCORE_PER_EXTEND = 400000;

extern int extend_next;

// Checks if [score] has exceeded a certain threshold, and grants an extra life
// in that case, redrawing the life section of the UI if that happened.
void score_extend_update_and_render(void);
