public @grcg_tile_bb_put_8
@grcg_tile_bb_put_8 proc near
	@@left	equ <ax>
	@@top 	equ <dx>

	@@rows_after_roll	equ <bx>

	push	di
	mov	@@rows_after_roll, @@top
	sar	@@left, 3
	shl	@@top, 6
	add	@@left, @@top
	shr	@@top, 2
	add	@@left, @@top
	mov	di, @@left
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	cmp	bx, PLAYFIELD_BOTTOM
	ja	short @@roll_needed
	mov	cx, TILE_H
	xor	@@rows_after_roll, @@rows_after_roll
	jmp	short @@row_loop
; ---------------------------------------------------------------------------

@@roll_needed:
	mov	cx, RES_Y
	sub	cx, @@rows_after_roll
	mov	@@rows_after_roll, TILE_H
	sub	@@rows_after_roll, cx

@@row_loop:
	stosw
	add	di, (ROW_SIZE - TILE_VRAM_W)
	loop	@@row_loop
	or	@@rows_after_roll, @@rows_after_roll
	jz	short @@ret
	sub	di, PLANE_SIZE
	xchg	cx, @@rows_after_roll
	jmp	short @@row_loop
; ---------------------------------------------------------------------------

@@ret:
	pop	di
	retn
@grcg_tile_bb_put_8 endp
