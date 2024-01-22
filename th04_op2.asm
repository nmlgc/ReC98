GAME = 4

	.386
	.model use16 large _TEXT

include ReC98.inc

	.data

include th03/snd/se_state[data].asm
include th04/hardware/bgimage[data].asm
include th03/formats/cdg[data].asm

	end
