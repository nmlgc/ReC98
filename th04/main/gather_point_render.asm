public @gather_point_render$qii
@gather_point_render$qii proc near

@@left equ <ax>
@@top equ <dx>

@@rows_after_roll equ <dx>

	push	si
	push	di
	mov	si, @@left
	mov	bx, @@top
	sar	ax, 3
	shl	dx, 6
	add	ax, dx
	shr	dx, 2
	add	ax, dx
	mov	di, ax
	and	si, 7
	mov	ax, si
	shl	si, 4
	add	si, offset _sPELLET
	mov	cx, PELLET_H
	cmp	bx, (RES_Y - PELLET_H)
	ja	short @@roll_needed
	xor	@@rows_after_roll, @@rows_after_roll
	jmp	short @@no_roll
; ---------------------------------------------------------------------------

@@roll_needed:
	mov	@@rows_after_roll, cx
	mov	cx, RES_Y
	sub	cx, bx
	sub	dx, cx

@@no_roll:
	or	ax, ax
	jz	short @@BYTEALIGNED_YLOOP1
	nop

@@YLOOP:
	movsw
	add	di, (ROW_SIZE - word)
	loop	@@YLOOP

@@roll:
	or	@@rows_after_roll, @@rows_after_roll
	jz	short @@ret
	sub	di, PLANE_SIZE
	xchg	cx, @@rows_after_roll
	jmp	short @@YLOOP
; ---------------------------------------------------------------------------

@@BYTEALIGNED_YLOOP1:
	movsb
	add	di, (ROW_SIZE - byte)
	inc	si
	loop	@@BYTEALIGNED_YLOOP1
	jmp	short @@roll
; ---------------------------------------------------------------------------

@@ret:
	pop	di
	pop	si
	retn
@gather_point_render$qii endp
