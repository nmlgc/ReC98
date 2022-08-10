#include "platform.h"
#include "th01/common.h"
#include "th01/resident.hpp"

long score = 100000;
long score_highest = 100000;
long continues_total;
long continues_per_scene[SCENE_COUNT];

// ZUN bloat: 308 unused bytes… for 77 extra scenes, maybe?!
static int8_t unused[308];

char start_lives_extra;
end_sequence_t end_flag;
unsigned char rank;
