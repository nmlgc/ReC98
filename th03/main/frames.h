#include "platform.h"

// Round-relative frame counter. Resets to 0 when winning or losing.
extern unsigned long round_frame;
extern unsigned char round_frame_mod2;
extern unsigned char round_frame_mod4;
extern unsigned char round_frame_mod8;
extern unsigned char round_frame_mod16;

// Starts out as a 16-bit copy of [round_frame], but is reset to 0 at the start
// of the round result animation.
extern uint16_t round_or_result_frame;
