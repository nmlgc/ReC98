#include "th01/main/player/bomb.hpp"

bool16 bomb_deals_damage(unsigned long frame)
{
	if((lives == 0) && (bomb_damaging == true) && ((frame % 50) == 0)) {
		return true;
	}
	return false;
}
