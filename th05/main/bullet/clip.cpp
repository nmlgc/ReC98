#pragma option -zCBULLET_A_TEXT -zPmain_03 -k-

#include "platform.h"
#include "pc98.h"
#include "th01/math/overlap.hpp"
#include "th04/main/player/player.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th04/main/bullet/clearzap.hpp"
#include "th05/main/playperf.hpp"

bool near bullet_template_clip(void)
{
	extern bool group_fixedspeed;

	if(
		(bullet_clear_time != 0) &&
		// If a newly spawned bullet wouldn't fully decay during the remaining
		// time, let's simply not spawn it at all? This way, they don't award
		// score points either.
		(bullet_clear_time < (BMS_DECAY_FRAMES + 1)) // differs from TH04!
	) {
clipped:
		return true;
	}

	// Also applies to 8×8 pellets, because why wouldn't you combine both
	// cases. #goodcode
	_AX = bullet_template.origin.x;
	_DX = bullet_template.origin.y;
	if(!playfield_encloses(_AX, _DX, BULLET16_W, BULLET16_H)) {
		goto clipped;
	}
	_AX -= player_pos.cur.x;
	if(overlap_1d_inplace_fast(_AX, BULLET_KILLBOX_W)) {
		_DX -= player_pos.cur.y;
		if(overlap_1d_inplace_fast(_DX, BULLET_KILLBOX_H)) {
			player_is_hit = true;
			// Yes, no `return true` - TH05 does in fact *not* clip bullets
			// that are spawned on top of the player.
			// This might sound like it has a different effect on gameplay.
			// Until you realize that the player got hit in this case and will
			// either lose a life or deathbomb, both of which will cause all
			// on-screen bullets to get cleared anyway.
			// So it's at most a visual glitch.
		}
	}

	if(!group_fixedspeed) {
		bullet_template.speed.v = playperf_speedtune(bullet_template.speed.v);
	}
	return false;
}
