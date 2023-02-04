#include "platform.h"
#include "th01/resident.hpp"

score_t score = 100000;
score_t score_highest = 100000;
int32_t continues_total;
int32_t continues_per_scene[SCENE_COUNT];

// ZUN bloat: 308 unused bytes… for 77 extra scenes, maybe?!
static int8_t unused[308];

int8_t credit_lives_extra;
end_sequence_t end_flag;
uint8_t rank;
