	.386
	.model large SHARED_
	locals

include twobyte.inc
include th04/hardware/input.inc

	extrn _key_det:word
	extrn _shiftkey:byte
	extrn js_stat:word
	extrn js_bexist:word

	extrn JS_SENSE:proc

SHARED_	segment word public 'CODE' use16
	assume cs:SHARED_
include th04/hardware/input_s.asm
SHARED_	ends

	end
