; master.lib data for TH01's OP.EXE.

	.386
	.model use16 large _TEXT

	.data

include libs/master.lib/version[data].asm
include libs/master.lib/grp[data].asm
include libs/master.lib/pal[data].asm
include libs/master.lib/respal_exist[data].asm
include libs/master.lib/resdata[data].asm
include libs/master.lib/fil[data].asm
include libs/master.lib/keytable[data].asm
include libs/master.lib/keystart[data].asm
include libs/master.lib/keyback[data].asm
include libs/master.lib/dos_ropen[data].asm
include libs/master.lib/clip[data].asm
include libs/master.lib/rand[data].asm

	.data?

include libs/master.lib/pal[bss].asm
include libs/master.lib/fil[bss].asm
include libs/master.lib/keystart[bss].asm
include libs/master.lib/clip[bss].asm

	end
