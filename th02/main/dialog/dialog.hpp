// ID of the next dialog box to be shown.
extern uint8_t dialog_box_cur;

// Loads the dialog text file for the current stage into the internal,
// statically allocated buffer, and resets [dialog_box_cur].
void dialog_load_and_init(void);
