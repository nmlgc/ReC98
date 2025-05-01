#include "th03/main/chars/speed.hpp"
#include "th03/main/playfld.hpp"
#include "th03/hardware/input.h"

enum move_ret_t {
	MOVE_INVALID = 0,
	MOVE_VALID = 1,
	MOVE_NOINPUT = 2,
};

extern speed_t player_speed_base; // of [player_cur]
extern SPPoint8 player_velocity; // of [player_cur]

void pascal near player_pos_update_and_clamp(PlayfieldPoint near& center);

// Sets [player_velocity] according to [input].
move_ret_t pascal near player_move(input_t input);
