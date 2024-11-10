#include "platform.h"

// The character selection menu needs to load exactly 255,216 bytes of sprite
// data, excluding headers, from a total of 14 files. This amount of loading
// was probably very noticeable on hard drives of the day, and so ZUN decided
// to split up the loading calls and move these three ahead into the main menu.
void near select_cdg_load_part1_of_4(void);
void near select_cdg_load_part2_of_4(void);
void near select_cdg_load_part3_of_4(void);

// Shows the respective character selection menu and writes the selected
// characters to [resident->playchar_paletted]. Returns `true` if the selection
// was canceled.
bool near select_1p_vs_2p_menu(void);
bool near select_vs_cpu_menu(void); // 1P vs. CPU or CPU vs. CPU
bool near select_story_menu(void);
