#if (GAME >= 4)
#define MUSICROOM_DISTANCE near
#else
#define MUSICROOM_DISTANCE
#endif

// Runs the Music Room menu and returns with VRAM page #0 as the shown and
// accessed one. TH02 reblits the title screen background to that page before
// returning; the other games return with a black screen.
void MUSICROOM_DISTANCE musicroom_menu(void);
