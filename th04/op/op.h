extern unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];

// Shows the player character / shot type selection menu, writing the
// selection to [resident]. Returns whether to start the game (false) or
// return to the main menu (true).
bool16 near playchar_menu(void);
