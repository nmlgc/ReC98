#pragma option -zCmain_031_TEXT -zPmain_03

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th05/main/playfld.hpp"
#include "th05/main/player/player.hpp"

unsigned char pascal near player_angle_from(
	Subpixel x, Subpixel y, unsigned char plus_angle
)
{
	return (
		iatan2((player_pos.cur.y - y), (player_pos.cur.x - x)) + plus_angle
	);
}
#pragma codestring "\x90"

}
