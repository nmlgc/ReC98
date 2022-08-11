// Resets the hardware palette to the [stage_palette], grants the end-of-stage
// bonus calculated from the current gameplay metrics and [stage_num], animates
// the box, shows the numbers, and waits until a Shot/OK key press before
// returning.
void stagebonus_animate(int stage_num);

// Resets any active shots and pellets, transitions both VRAM and the hardware
// palette to the end-of-scene bonus screen with the infamous typo, calculates
// and animates the bonus points from the current gameplay metrics and
// [stage_num], and waits until a Shot/OK key press before returning.
void totle_animate(int stage_num);
