	.186
	.model use16 large
	locals

include libs/master.lib/macros.inc
include th01/math/subpixel.inc
include th03/common.inc
include th03/main/playfld.inc
include th03/main/collmap.inc

extrn _collmap_topleft:Point
extrn _collmap_stripe_tile_w:word
extrn _collmap_bottomright:Point
extrn _collmap_pid:byte
extrn _collmap:byte:(PLAYER_COUNT * COLLMAP_SIZE)

; Sets @@dst to the offset of column @@x inside [collmap].
offset_x macro @@dst:req, @@x:req
	if ((@@dst eq ax) and (@@x eq al))
		; MODDERS: This performs a 8→16-bit multiplication of AX = (AH * AL).
		; Effectively limits both COLLMAP_H and COLLMAP_MEMORY_W to 8 bits!
		mov	ah, COLLMAP_H
		mul	ah
	else
		.err "Come on, just rewrite this in C++."
	endif
endm

MAIN_04 group COLLMAP_TEXT

	.code
	assume cs:MAIN_04

public _collmap_set_slope_striped
_collmap_set_slope_striped proc c far
	uses si, di
	@@collmap_p     	equ <bx>
	@@first_bit     	equ <cl>
	@@first_bit_wide	equ <cx>	; Just remove this
	@@left          	equ <si>
	@@y_double      	equ <di>

SLOPE_STRIPES = (COLLMAP_H / COLLMAP_SLOPE_VSTRIPE_DISTANCE)

	mov	bx, (COLLMAP_H - 1)
	cmp	_collmap_pid, 0
	jz	short @@set_collmap_base
	add	bx, COLLMAP_SIZE

@@set_collmap_base:
	add	bx, offset _collmap
	mov	@@collmap_p_base_player_and_row, bx

	; @@pattern = ~(0xFF >> collmap_sprite_tile_w);
	; AH needs to be 0x00 for the carry pixel rotate trick below.
	mov	al, 11111111b
	mov	cx, _collmap_stripe_tile_w
	shr	al, cl
	not	al
	xor	ah, ah
	mov	@@pattern, ax

	mov	ax, _collmap_bottomright.x
	sub	ax, _collmap_topleft.x
	mov	@@slope_subpixel_w, ax
	jmp	short $+2
	mov	@@left, _collmap_bottomright.x
	mov	@@y_double, (SLOPE_STRIPES - 1)
	even

@@row_loop:
	mov     	ax, @@left
	shr     	ax, (SUBPIXEL_BITS + COLLMAP_TILE_W_BITS)
	mov     	@@first_bit_wide, ax
	and     	@@first_bit_wide, 7
	shr     	ax, 3 	; AX = ((AX / BYTE_DOTS) * COLLMAP_H)
	offset_x	ax, al	;

	@@collmap_p_base_player_and_row = word ptr $+1
	mov	@@collmap_p, 1234h
	add	@@collmap_p, ax

	; Right-rotate the pattern by [first_bit]. If the pattern then extends into
	; a second bitmap byte, that byte's pattern will end up in AH.
	@@pattern = word ptr $+1
	mov	ax, 1234h
	ror	ax, @@first_bit
	or	[@@collmap_p], al
	or	ah, ah
	jz	short @@skip_blank
	add	@@collmap_p, COLLMAP_H
	or	[@@collmap_p], ah

@@skip_blank:
	dec	@@y_double
	jz	short @@ret

	; Interpolate new left X coordinate
	;
	; left = (collmap_topleft.x + (
	; 	static_cast<long>(slope_subpixel_w * y_double) / SLOPE_STRIPES
	; ));
	@@slope_subpixel_w = word ptr $+1
	mov	ax, 1234h
	imul	@@y_double
	mov	cx, SLOPE_STRIPES
	idiv	cx	; 32-bit division of DX:AX by CX!
	mov	@@left, _collmap_topleft.x
	add	@@left, ax

	sub	@@collmap_p_base_player_and_row, COLLMAP_SLOPE_VSTRIPE_DISTANCE
	jmp	short @@row_loop
; ---------------------------------------------------------------------------

@@ret:
	ret
_collmap_set_slope_striped endp
	even

	end
