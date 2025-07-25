// GAME.BAT replica
// ----------------

#include "platform/x86real/spawn.hpp"
#include "th01/pc98/entry.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/resident.hpp"

int main_setup(int argc, const char *argv[])
{
	resident = resident_get_or_create();
	if(!mdrv2_resident()) {
		// MODDERS: Find the largest .MDT file, and set the size accordingly.
		// (.MDE sound effect files have a hardcoded 4 KiB limit.)
		if(mdrv2_spawn(7) == -1) {
			return -1;
		}
		resident->shutdown_flags |= SHUTDOWN_MDRV2;
		spawn_adjacent_report("zunsoft.com", "");
	}
	return main_op(argc, argv);
}

void main_shutdown(void)
{
	resident = resident_get();
	if(!resident) {
		return;
	}
	if(resident->shutdown_flags & SHUTDOWN_MDRV2) {
		mdrv2_remove();
	}
	resident_free();
}
