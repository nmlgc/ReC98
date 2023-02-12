// GAME.BAT replica
// ----------------

#include "platform.h"
#include "th01/core/entry.hpp"
#include "th01/snd/mdrv2.h"

int main_setup(int argc, const char *argv[])
{
	const bool mdrv2_not_spawned_outside = !mdrv2_resident();
	if(mdrv2_not_spawned_outside) {
		// MODDERS: Find the largest .MDT file, and set the size accordingly.
		// (.MDE sound effect files have a hardcoded 4 KiB limit.)
		if(mdrv2_spawn(7) == -1) {
			return -1;
		}
	}
	int ret = main_op(argc, argv);
	if(mdrv2_not_spawned_outside) {
		mdrv2_remove();
	}
	return ret;
}
