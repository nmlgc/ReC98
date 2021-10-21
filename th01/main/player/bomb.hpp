#define BOMB_DOUBLETAP_WINDOW 20

// Current frame within the BOMB_DOUBLETAP_WINDOW. A bomb is fired if both
// shot and strike keys are double-tapped before this variable reaches that
// window.
extern int bomb_doubletap_frames;

// Indicates whether a bomb is active and dealing damage to everything on
// screen.
extern bool bomb_damaging;

extern unsigned long bomb_frames;

// Renders the given [frame] of the bomb animation, and applies any
// frame-specific game state modifications. Returns false if the animation is
// done.
bool16 bomb_update_and_render(int frame);

// Returns `true` if an active bomb deals damage to the boss on the current
// [frame].
bool16 bomb_deals_damage(unsigned long frame);
