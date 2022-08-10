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

	end
