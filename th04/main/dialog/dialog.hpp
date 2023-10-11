// Runs the next dialog scene in a blocking way.
// During the TH05 Extra Stage Clear replay, this function
// • skips the dialog for the call before the fight, while replicating the
//   sprite loading and BGM change side effects from the original script,
// • and directly switches back to OP.EXE for the call after the fight.
void dialog_animate(void);

#if (GAME == 4)
	// Dialog-related image functions with optional EMS support
	// --------------------------------------------------------

	// Loads the remaining .CDG images for in-game dialog that haven't been in
	// memory since the start of the stage (i.e., the player character
	// faceset), freeing any images that aren't used during a dialog (i.e.,
	// the bomb background) in exchange for the necessary conventional memory.
	void near dialog_init(void);

	// Restores the bomb background image, after freeing any dialog-only images
	// (i.e., the player character faceset) in exchange for the necessary
	// conventional memory.
	// Apparently, this was also the most convenient place to load the boss
	// faceset used for both the Mugetsu defeat / Gengetsu entrance dialog and
	// the Gengetsu defeat dialogue? To differentiate between those two, the
	// function tracks how often it has been called during the Extra Stage.
	void near dialog_exit(void);
	// --------------------------------------------------------
#endif
