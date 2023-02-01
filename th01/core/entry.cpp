#include <process.h>
#include <dos.h>
#include <string.h>
#include "platform.h"
#include "th01/core/entry.hpp"

// argv[1] value to select a given entry point.
static char* ENTRYPOINTS[EP_COUNT] = {
	"op", "reiiden", "fuuin"
};

int __cdecl main(int argc, const char *argv[])
{
	int (*entry)(int, const char* []);

	if(argc < 2) {
		entry = main_op;
	} else if(!stricmp(argv[1], ENTRYPOINTS[EP_OP])) {
		entry = main_op;
	} else if(!stricmp(argv[1], ENTRYPOINTS[EP_MAIN])) {
		entry = main_main;
	} else if(!stricmp(argv[1], ENTRYPOINTS[EP_CUTSCENE])) {
		entry = main_cutscene;
	} else {
		// No entry point string means that we've got debug flags. Pass them
		// along to OP, just like GAME.BAT does.
		return main_op(argc, argv);
	}
	return entry((argc - 1), &argv[1]);
}

void entrypoint_exec(entrypoint_t entrypoint)
{
	execl(_argv[0], ENTRYPOINTS[entrypoint], ENTRYPOINTS[entrypoint], nullptr);
}
