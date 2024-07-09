#define ALPHABET_ROWS 3
#define ALPHABET_COLS 17

#define ALPHABET_ENTER_ROW (ALPHABET_ROWS - 1)
#define ALPHABET_ENTER_COL (ALPHABET_COLS - 1)

#define score_atrb_set(atrb, place, place_to_highlight) { \
	if((place) == place_to_highlight) { \
		atrb = TX_GREEN; \
	} else { \
		atrb = TX_WHITE; \
	} \
}

// Shows the high score list for the current difficulty. If [score] is good
// enough to be on there, the player is asked to enter a name, before the
// result is inserted and written to the high score file.
//
// ZUN bloat: The MAINE.EXE version expects the internal [score] to be
// multiplied by 10 and the number of continues to be added, whereas MAIN.EXE
// does this itself. Passing it as a clearly annotated parameter would have
// been nicer.
void regist_menu(void);
