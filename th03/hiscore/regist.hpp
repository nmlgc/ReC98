// Shows the High Score menu for the current [resident->rank].
// If [resident->story_stage] is [STAGE_NONE], the menu is shown in view-only
// mode. Otherwise, the game tries to add [resident->score_last[0]] to the
// difficulty's score list if possible, asking the player to enter a name and
// saving the score file if necessary.
// Leaves with [PaletteTone] at 0 and both VRAM and RAM prepared for showing
// either the Continue or Game Over screen.
void near regist_menu(void);
