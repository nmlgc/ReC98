#include "platform.h"
#include "th01/resident.hpp"
#include "th01/main/vars.hpp"
#include "th01/formats/cfg.hpp"

int8_t rank = CFG_RANK_DEFAULT;
bgm_mode_t bgm_mode = CFG_BGM_MODE_DEFAULT;
int8_t bombs = CFG_CREDIT_BOMBS_DEFAULT;
int8_t credit_lives_extra = CFG_CREDIT_LIVES_EXTRA_DEFAULT;

int8_t stage_num = 0;
bool bgm_change_blocked = false;
