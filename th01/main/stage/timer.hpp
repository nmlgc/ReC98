static const int TIMER_TICK = 2;

// Saves the current VRAM contents at the timer's position as the background
// in successive timer_put() calls, then renders the timer's current value.
void timer_bg_snap_and_put(void);

// Renders the stage timer to both VRAM pages.
void timer_put(void);

// Reduces the timer by [STAGE_TIMER_TICK], then renders its new value.
void timer_tick_and_put(void);

// Adds some more time onto the timer, canceling any active HARRY UP state,
// then renders its new value.
void timer_extend_and_put(void);
