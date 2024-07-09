#include "th02/resident.hpp"
#include "th02/core/globals.hpp"
#include "th02/main/playperf.hpp"

void near skill_calculate(void)
{
	int skill = (rank * 20);
	skill += (10 - (resident->continues_used * 3));

	int skill_miss_and_bombs = (50 - (total_miss_count * 3) - total_bombs_used);
	if(skill_miss_and_bombs < 0) {
		skill_miss_and_bombs = 0;
	}
	skill += skill_miss_and_bombs;

	if(item_skill > 25) {
		item_skill = 25;
	} else if(item_skill < 0) {
		item_skill = 0;
	}
	skill += item_skill;
	resident->skill = skill;
}
