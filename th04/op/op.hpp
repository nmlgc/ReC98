extern bool extra_unlocked;

void near start_game(void);
void near start_extra(void);
void near start_demo(void);

void near setup_menu(void);
void near zunsoft_animate(void);

void near main_cdg_load(void);
void near main_cdg_free(void);

// Returns with the title image blitted to both VRAM pages, page 1 accessed,
// and page 0 shown.
void near op_animate(void);

void near regist_view_menu(void);

// Initializes the game clear/extra unlock variables from the score file, and
// loads the sprites used for the viewing mode of the score name registration
// menu.
void near cleardata_and_regist_view_sprites_load(void);

// Shows the player character / shot type selection menu, writing the
// selection to [resident]. Returns whether to start the game (false) or
// return to the main menu (true).
bool16 near playchar_menu(void);
