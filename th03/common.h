/* ReC98
 * -----
 * Common, essential macros for TH03. No structures here!
 */

#include "platform.h"

// Player ID. ZUN bloat: Only keep `pid_t`.
typedef unsigned char pid_t;
typedef int8_t spid_t;
typedef int16_t pid2;

// [PID_NONE] is a valid value.
typedef pid_t pid_optional_t;

#define PLAYER_COUNT 2
#define PID_NONE static_cast<pid_t>(-1)
