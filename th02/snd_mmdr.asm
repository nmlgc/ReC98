	.386
	.model use16 large SHARED
	locals

include libs/kaja/kaja.inc

	extrn _snd_interrupt_if_midi:byte
	extrn _snd_midi_active:byte
	extrn _snd_midi_possible:byte

SHARED	segment word public 'CODE' use16
	assume cs:SHARED
include th02/snd/mmd_res.asm
SHARED	ends

	end
