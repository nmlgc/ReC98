#include "th02/core/initexit.h"
#include <stddef.h>

int game_init_op(const unsigned char *pf_fn);
int pascal game_init_main(const unsigned char *pf_fn);

// Special game_exit() variant used when exiting from MAINL.EXE to MAIN.EXE in
// TH03. Really, why is this a separate function???
void game_exit_from_mainl_to_main();
