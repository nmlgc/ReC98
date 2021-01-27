#include "th02/core/initexit.h"

int game_init_op(const unsigned char *pf_fn);
int pascal game_init_main(const unsigned char *pf_fn);

// Special game_exit() variant used when exiting from MAINL.EXE to MAIN.EXE in
// TH03. Really, why is this a separate function???
void game_exit_from_mainl_to_main();

// Number of paragraphs to be reserved by the game_init_*() function.
extern size_t mem_assign_paras;
