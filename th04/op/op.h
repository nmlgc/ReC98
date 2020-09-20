extern unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];

void near start_game(void);
void near start_extra(void);
void near start_demo(void);

void near setup_menu(void);
void near zunsoft(void);

void near main_cdg_load(void);
void near main_cdg_free(void);

void near op_animate(void);
void near musicroom(void);

void near regist_view_menu(void);

// Initializes the game clear/extra unlock variables from the score file, and
// loads the sprites used for the viewing mode of the score name registration
// menu.
void near cleardata_and_regist_view_sprites_load(void);

// Shows the player character / shot type selection menu, writing the
// selection to [resident]. Returns whether to start the game (false) or
// return to the main menu (true).
bool16 near playchar_menu(void);
