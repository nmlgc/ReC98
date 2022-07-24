; Additional data after the last translation unit in C land.

	.386
	.model use16 large

BINARY = 'E'

include pc98.inc

	.data

include th01/hardware/vsync[data].asm
include th01/hardware/ztext[data].asm
include th01/core/initexit[data].asm
include th01/hardware/palette[data].asm
include th01/hardware/graph_r[data].asm
include th01/hardware/respal[data].asm
include th01/formats/grp_ptn[data].asm
include th01/snd/mdrv2[data].asm
include libs/master.lib/version[data].asm
include libs/master.lib/grp[data].asm
include libs/master.lib/pal[data].asm
include libs/master.lib/respal_exist[data].asm
include libs/master.lib/resdata[data].asm
include libs/master.lib/fil[data].asm
include libs/master.lib/dos_ropen[data].asm
include libs/master.lib/clip[data].asm
include libs/master.lib/rand[data].asm

	.data?

include libs/master.lib/pal[bss].asm
include libs/master.lib/fil[bss].asm
include libs/master.lib/clip[bss].asm

	end
