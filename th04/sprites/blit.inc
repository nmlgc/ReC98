; Shared sprite blitting macros
; -----------------------------
; All of these assume that:
; • the GRCG to be active, and set to the intended color and tile
; • DS:SI being set to the source sprite data, and ES:DI to the intended
;   destination byte within a VRAM plane.

; Modes:
; • roll: Y-wrapped
; • empty2opt: Not writing the right 8 dots to VRAM if they are 0
; • emptyopt: Writing nothing to VRAM if all 16 dots are 0

; Blitting [h] rows, with [top] being the first one.
blit_dots16_empty2opt_emptyopt_roll macro @@top:req, @@h:req

@@rows_after_roll equ <bx>

	cmp	@@top, (RES_Y - @@h)
	ja	short @@roll_needed
	mov	cx, @@h	; CX = # of rows copied *before* Y wrap
	xor	@@rows_after_roll, @@rows_after_roll
	jmp	short @@blit_loop

@@roll_needed:
	mov	cx, RES_Y
	sub	cx, @@top
	mov	@@rows_after_roll, @@h
	sub	@@rows_after_roll, cx
	even

@@blit_loop:
	lodsw
	or	ah, ah
	jz	short @@blit_al?
	mov	es:[di], ax
	jmp	short @@next_row

@@blit_al?:
	or	al, al
	jz	short @@next_row
	mov	es:[di], al

@@next_row:
	add	di, ROW_SIZE
	loop	@@blit_loop
	or	@@rows_after_roll, @@rows_after_roll
	jz	short @@blit_done
	sub	di, PLANE_SIZE
	xchg	cx, @@rows_after_roll
	jmp	short @@blit_loop

@@blit_done:
endm
