#include "th04/score.h"

extern score_lebcd_t score;
extern score_lebcd_t hiscore;

static const unsigned int STAGE_GRAZE_CAP = 999;

extern unsigned int graze_score;	// Set per difficulty.
extern unsigned int stage_graze;	// Reset to 0 when moving to a new stage.

extern unsigned char extends_gained;
extern unsigned long score_delta;

void near score_update_and_render(void);

// Adds the entire [score_delta] at once to the current score.
void pascal score_delta_commit(void);
