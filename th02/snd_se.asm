	.386
	locals

include defconv.inc
include libs/kaja/kaja.inc

	extrn _snd_se_playing:byte
	extrn _snd_se_frame:byte
	extrn _snd_se_priorities:byte
	extrn _snd_se_priority_frames:byte
	extrn _snd_fm_possible:byte

SHARED	segment word public 'CODE' use16
	assume cs:SHARED
include th02/snd/se.asm
SHARED	ends

	end
