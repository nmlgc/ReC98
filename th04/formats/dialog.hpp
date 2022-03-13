// Script buffer pointer
extern unsigned char far *dialog_p;

// Loads a dialog script from the file with the given name. `near` in this
// game, as it's only used internally.
void pascal near dialog_load(const char *fn);

// Loads the dialog script after defeating Stage 5 Yuuka with continues or on
// Easy mode, shown before the Bad Ending.
void dialog_load_yuuka5_defeat_bad(void);

// Loads the dialog script for the current player character and stage.
void near dialog_load(void);
