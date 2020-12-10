/// Generic state variables
/// -----------------------
/// Really just freely usable memory shared between all bosses.

extern int boss_hp;
extern int boss_phase_frame;
/// -----------------------

// No-op function for callbacks.
void far boss_nop(void);
