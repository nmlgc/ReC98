// Yes, snd_delay_until_measure() links to its own copy of frame_delay(), but
// only in TH02's OP.EXE. And since every other SHARED function with a
// frame_delay() call *does* refer to the same instance of this function, we
// have no choice but to compile the OP.EXE version separately.
//
// Really, how was this game even *built*, originally, if it uses *both* a
// common set of library functions *and* obviously copy-pasted and separately
// compiled versions of some of these functions?

#include "platform.h"
#include "th02/snd/data.c"
#include "th02/snd/se_data.c"

#define frame_delay frame_delay_2
#include "th02/snd_dlym.cpp"
