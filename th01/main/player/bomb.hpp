// Indicates whether a bomb is active and dealing damage to everything on
// screen.
bool bomb_damaging;

// Renders the given [frame] of the bomb animation, and applies any
// frame-specific game state modifications. Returns false if the animation is
// done.
bool16 bomb_update_and_render(int frame);
