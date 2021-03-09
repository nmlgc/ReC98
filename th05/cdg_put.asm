	.386
	locals

include pc98.inc
include libs/master.lib/macros.inc
include th03/formats/cdg.inc

	extrn _cdg_slots:cdg_t:CDG_SLOT_COUNT

SHARED_	segment word public 'CODE' use16
	assume cs:SHARED_
include th04/formats/cdg_put.asm
SHARED_	ends

	end
