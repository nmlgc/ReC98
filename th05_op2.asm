	.386
	.model use16 large _TEXT

include ReC98.inc

	.data

include th03/snd/se_state[data].asm
include th04/hardware/bgimage[data].asm
include th05/mem[data].asm
include th05/op/piano[data].asm
include th05/sprites/piano_l.asp
include th05/snd/load[data].asm
include th04/snd/snd[data].asm
include th03/formats/pi_put_masked[data].asm
include th05/formats/pi_buffers[bss].asm
include th05/hardware/vram_planes[data].asm
include th03/formats/cdg[data].asm

	end
