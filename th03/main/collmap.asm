	.386
	.model use16 large
	locals

include libs/master.lib/macros.inc
include th01/math/subpixel.inc
include th03/common.inc
include th03/main/playfld.inc
include th03/main/collmap.inc

extrn _collmap_topleft:Point
extrn _collmap_center:Point
extrn _collmap_stripe_tile_w:word
extrn _collmap_tile_h:word
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

public _collmap_set_rect_striped
_collmap_set_rect_striped proc far
	@@byte_x               	equ <al>
	@@byte_x_wide         	equ <ax>	; Just remove this
	@@left                 	equ <ax>
	@@pattern              	equ <ah>
	@@collmap_p            	equ <bx>
	@@h_remaining          	equ <cx>
	@@bottom               	equ <cx>
	@@tile_w_remaining     	equ <dl>
	@@tile_w_remaining_wide	equ <dx>	; Just remove this
	@@top                 	equ <dx>

	 ; (yeah, it's still center, will take a while to actually become top)
	mov	@@top, _collmap_center.y
	or	@@top, @@top
	js	@@ret
	cmp	@@top, (PLAYFIELD_H shl 4)
	jge	@@ret

@@set_collmap_base_p:
	xor	ax, ax
	cmp	_collmap_pid, 0
	jz	short @@set_collmap_p_player_and_row
	mov	ax, COLLMAP_SIZE

@@set_collmap_p_player_and_row:
	add	ax, offset _collmap
	mov	@@collmap_p_player_and_row, ax

@@set_top_and_bottom:
	sar	@@top, (SUBPIXEL_BITS + COLLMAP_TILE_H_BITS)
	mov	@@bottom, _collmap_tile_h
	mov	ax, @@bottom   	; top -= (collmap_tile_h / 2);
	shr	ax, 1          	;
	sub	@@top, ax      	;
	add	@@bottom, @@top	; bottom = (top + collmap_tile_h);

@@clip_top?:
	or	@@top, @@top
	jns	short @@clip_bottom?
	xor	@@top, @@top

@@clip_bottom?:
	cmp	@@bottom, COLLMAP_H
	jb	short @@set_tile_h_and_column_stride
	mov	@@bottom, (COLLMAP_H - 1)

@@set_tile_h_and_column_stride:
	add	@@collmap_p_player_and_row, @@top
	sub	@@bottom, @@top    	; tile_h = (top - bottom); // = collmap_tile_h
	mov	@@tile_h, @@bottom 	;
	mov	ax, COLLMAP_H      	; column_stride = (COLLMAP_H - tile_h);
	sub	ax, @@bottom       	;
	mov	@@column_stride, ax	;

@@set_left:
	mov	@@left, _collmap_center.x
	sar	@@left, (SUBPIXEL_BITS + COLLMAP_TILE_W_BITS)

	mov	@@tile_w_remaining_wide, _collmap_stripe_tile_w
	mov	bx, @@tile_w_remaining_wide	; left -= (collmap_stripe_tile_w / 2);
	shr	bx, 1                 	;
	sub	@@left, bx            	;

@@clip_left?:
	or	@@left, @@left
	jns	short @@left_positive

@@left_negative:
	add	@@tile_w_remaining_wide, @@left	; Subtract number of offscreen columns
	cmp	@@tile_w_remaining_wide, 0 	; Entirely outside the playfield?
	jle	short @@ret
	xor	@@left, @@left

@@left_positive:
	mov	cx, @@left	; first_bit = left;
	shr	@@left, 3	; left /= 8;
	and	cx, (8 - 1)	; first_bit &= (8 - 1);
	mov	@@first_bit, cl

	; Enlarge the width by the position of the first bit…? Required for every
	; single overly clever calculation below that involves this variable.
	add	@@tile_w_remaining_wide, cx
	jmp	short $+2

	; collmap_p = (left * COLLMAP_H);
	mov     	cx, @@left
	offset_x	ax, al
	mov    	@@collmap_p, ax

	@@collmap_p_player_and_row = word ptr $+2
	add	@@collmap_p, 1234h
	mov	@@byte_x_wide, cx

	; Assume @@tile_w_remaining == 8 for now
	mov	@@pattern, 11111111b

	@@first_bit = byte ptr $+2
	shr	@@pattern, 4	; pattern >>= first_bit

	; Remove tiles from the right of the initial pattern if the rectangle is
	; less than 8 tiles wide. After the addition above, any rectangle that
	; spans more than one byte (and thus, doesn't need tiles removed here)
	; will have [tile_w_remaining] > 8. That addition is also required for
	; this bit twiddling hack to work correctly, since the removed tiles are
	; past both the first bit and the width in tiles.
	;
	; An example with [first_bit] = 2 and an original [tile_w] of 4:
	; • [@@pattern] >> [@@first_bit]: 00111111
	; •          Tiles to be removed: 00000011 (11111111 >> (4 + 2))
	; •            Final [@@pattern]: 00111100
	cmp	@@tile_w_remaining, 8
	jge	short @@column_loop
	mov	ch, 11111111b
	mov	cl, @@tile_w_remaining
	shr	ch, cl
	xor	@@pattern, ch

@@column_loop:
	; This is the only instance where we have to clip at the right edge.
	cmp	@@byte_x, COLLMAP_MEMORY_W
	jnb	short @@ret

	@@tile_h = word ptr $+1
	mov	@@h_remaining, 1234h

@@row_loop:
	or	[@@collmap_p], @@pattern
	add	@@collmap_p, COLLMAP_RECT_VSTRIPE_DISTANCE
	sub	@@h_remaining, COLLMAP_RECT_VSTRIPE_DISTANCE
	jg	short @@row_loop

@@columns_more?:
	sub	@@tile_w_remaining, 8
	jle	short @@ret

@@column_next:
	inc	@@byte_x

	; [collmap_p] has probably overshot the bottom of the rectangle, making
	; [h_remaining] negative as well. Adding the column stride results in the
	; correct amount of rows to skip until [collmap_p] ends up that the top row
	; of the rectangle again.
	@@column_stride = word ptr $+2
	add	@@h_remaining, 1234h
	add	@@collmap_p, @@h_remaining

	; pattern = (tile_w_remaining < 8) ? ~(0xFF >> tile_w_remaining) : 0xFF;
	;
	; Since we consistently subtract 8, [tile_w_remaining] will only have the
	; correct amount of carry tiles if we previously added [first_bit] to it
	; (which we did).
	mov	@@pattern, 11111111b
	cmp	@@tile_w_remaining, 8
	jge	short @@column_loop
	mov	cl, @@tile_w_remaining
	shr	@@pattern, cl
	not	@@pattern

	jmp	short @@column_loop

@@ret:
	ret
_collmap_set_rect_striped endp
	even


public _collmap_set_vline
_collmap_set_vline proc far
	@@pattern         	equ <ah>
	@@first_bit       	equ <cl>
	@@first_bit_wide  	equ <cx>	; Just remove this
	@@rows_from_bottom	equ <dx>	; Ensures clipping at the bottom edge
	@@collmap_p       	equ <bx>

	mov	ax, _collmap_topleft.x
	mov	dx, _collmap_topleft.y

	; Clip
	or	ax, ax
	js	short @@ret
	cmp	ax, (PLAYFIELD_W shl 4)
	jge	short @@ret
	or	dx, dx
	js	short @@ret
	cmp	dx, (PLAYFIELD_H shl 4)
	jge	short @@ret

	xor	@@collmap_p, @@collmap_p
	cmp	_collmap_pid, 0
	jz	short @@set_collmap_p
	mov	@@collmap_p, COLLMAP_SIZE

@@set_collmap_p:
	add	@@collmap_p, offset _collmap

	sar	ax, (SUBPIXEL_BITS + COLLMAP_TILE_W_BITS)
	sar	dx, (SUBPIXEL_BITS + COLLMAP_TILE_H_BITS)

	mov     	@@first_bit_wide, ax     	; first_bit = AX;
	sar     	ax, 3                    	; AX /= 8; (bits per byte)
	and     	@@first_bit_wide, (8 - 1)	; first_bit &= (8 - 1);
	add     	@@collmap_p, dx          	; collmap_p += (
	offset_x	ax, al                   	; 	DX + (AX * COLLMAP_H)
	add     	@@collmap_p, ax          	; );

	mov	ax, COLLMAP_H
	sub	ax, dx
	mov	@@rows_from_bottom, ax
	mov	@@pattern, 80h
	shr	@@pattern, @@first_bit
	mov	cx, _collmap_tile_h
	even

@@row_loop:
	or	[@@collmap_p], @@pattern
	inc	@@collmap_p
	dec	@@rows_from_bottom
	loopne	@@row_loop

@@ret:
	ret
_collmap_set_vline endp
	even


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
