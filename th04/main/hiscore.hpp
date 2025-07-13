// High Score-related functions in MAIN.EXE
// ----------------------------------------

// Tries to find a place for [score] in [hi]. If successful, the score is
// entered under the name "CONTINUE" and the current stage, and [hi] is saved
// for the current global character and [rank].
// TH04 reloads [hi] from the score file before trying.
void near hiscore_continue_enter(void);

// Loads [hi] with the score data for the current [rank] and copies the highest
// score into [hiscore].
void near hiscore_load(void);
