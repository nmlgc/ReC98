extern unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];

// Initializes the game clear/extra unlock variables from the score file, and
// loads the sprites used for the viewing mode of the score name registration
// menu.
void near cleardata_and_regist_view_sprites_load(void);

// Shows the player character / shot type selection menu, writing the
// selection to [resident]. Returns whether to start the game (false) or
// return to the main menu (true).
bool16 near playchar_menu(void);
