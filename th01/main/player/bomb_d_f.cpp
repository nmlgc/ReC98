#include "th01/main/player/bomb.hpp"

// Global state that is defined here for some reason
// -------------------------------------------------

unsigned int hud_hp_first_white;
unsigned int hud_hp_first_redwhite;
// -------------------------------------------------

bool16 bomb_deals_damage(unsigned long frame)
{
	if((rem_lives == 0) && (bomb_damaging == true) && ((frame % 50) == 0)) {
		return true;
	}
	return false;
}
