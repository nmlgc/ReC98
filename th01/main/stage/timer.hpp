static const int TIMER_TICK = 2;

// Renders the stage timer to both VRAM pages.
void timer_put(void);

// Reduces the timer by [STAGE_TIMER_TICK], then renders its new value.
void timer_tick_and_put(void);

// Adds some more time onto the timer, canceling any active HARRY UP state,
// then renders its new value.
void timer_extend_and_put(void);
