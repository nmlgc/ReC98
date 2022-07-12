PELLET_TOP_H = 6
PELLET_BOTTOM_H = 4
PELLET_BOTTOM_Y = (PELLET_H - PELLET_BOTTOM_H)

public _pellets_render_top
_pellets_render_top	proc near
	mov	ax, _pellets_render_count
	or	ax, ax
	jnz	short @@at_least_one_alive
	retn
; ---------------------------------------------------------------------------

@@at_least_one_alive:
	push	bp
	push	si
	push	di
	mov	bp, ax
	mov	bx, offset _pellets_render

@@pellet_loop:
	mov	di, [bx+pellet_render_t.PRT_left]
	mov	ax, di
	sar	di, 3
	mov	cx, [bx+pellet_render_t.PRT_top]
	shl	cx, 6
	add	di, cx
	shr	cx, 2
	add	di, cx
	and	ax, 7
	mov	si, ax
	shl	si, 4
	add	si, offset _sPELLET
	shl	ax, 3
	mov	cx, PELLET_TOP_H
	or	ax, ax
	jz	short @@BYTEALIGNED
	cmp	di, ((RES_Y - PELLET_TOP_H + 1) * ROW_SIZE)
	jb	short @@SHIFTED_YLOOP2

@@SHIFTED_YLOOP1:
	movsw
	add	di, (ROW_SIZE - word)
	dec	cx
	cmp	di, PLANE_SIZE
	jb	short @@SHIFTED_YLOOP1
	sub	di, PLANE_SIZE

@@SHIFTED_YLOOP2:
	movsw
	add	di, (ROW_SIZE - word)
	loop	@@SHIFTED_YLOOP2
	jmp	short @@pellet_next
; ---------------------------------------------------------------------------
	even

@@BYTEALIGNED:
	cmp	di, ((RES_Y - PELLET_TOP_H + 1) * ROW_SIZE)
	jb	short @@BYTEALIGNED_YLOOP2

@@BYTEALIGNED_YLOOP1:
	movsb
	inc	si
	add	di, (ROW_SIZE - byte)
	dec	cx
	cmp	di, PLANE_SIZE
	jb	short @@BYTEALIGNED_YLOOP1
	sub	di, PLANE_SIZE

@@BYTEALIGNED_YLOOP2:
	movsb
	inc	si
	add	di, (ROW_SIZE - byte)
	loop	@@BYTEALIGNED_YLOOP2

@@pellet_next:
	sub	di, (((PELLET_TOP_H + 1) - PELLET_BOTTOM_Y) * ROW_SIZE)
	jns	short @@set_bottom_data
	add	di, PLANE_SIZE

@@set_bottom_data:
	add	ax, offset _sPELLET_BOTTOM
	mov	[bx+pellet_render_t.PRB_vram_offset], di
	mov	[bx+pellet_render_t.PRB_sprite_offset], ax
	add	bx, size pellet_render_t
	dec	bp
	jnz	short @@pellet_loop
	pop	di
	pop	si
	pop	bp
	retn
_pellets_render_top	endp
	even


public _pellets_render_bottom
_pellets_render_bottom	proc near

@@rows_after_roll equ <dx>

	mov	ax, _pellets_render_count
	or	ax, ax
	jnz	short @@at_least_one_alive
	retn
; ---------------------------------------------------------------------------

@@at_least_one_alive:
	push	bp
	push	si
	push	di
	mov	bp, ax
	mov	bx, offset _pellets_render

@@pellet_loop:
	mov	di, [bx+pellet_render_t.PRB_vram_offset]
	mov	si, [bx+pellet_render_t.PRB_sprite_offset]
	xor	@@rows_after_roll, @@rows_after_roll
	cmp	di, ((RES_Y - PELLET_BOTTOM_H - 1) * ROW_SIZE)
	jnb	short @@roll_needed
	even
	mov	cx, (PELLET_BOTTOM_H + 1)
	jmp	short @@no_roll
; ---------------------------------------------------------------------------

@@roll_needed:
	mov	ax, (PLANE_SIZE + (ROW_SIZE - 1))
	sub	ax, di
	mov	cx, ROW_SIZE
	div	cx
	mov	cx, ax
	mov	@@rows_after_roll, (PELLET_BOTTOM_H + 1)
	sub	@@rows_after_roll, cx

@@no_roll:
	mov	ax, [si] ; lol, it's also just a LODSW?
	jmp	short @@put
; ---------------------------------------------------------------------------

@@row_loop:
	lodsw

@@put:
	or	al, al
	jz	short @@only_byte_2
	or	ah, ah
	jz	short @@only_byte_1
	mov	es:[di], ax
	jmp	short @@row_next
; ---------------------------------------------------------------------------

@@only_byte_1:
	mov	es:[di], al
	jmp	short @@row_next
; ---------------------------------------------------------------------------

@@only_byte_2:
	mov	es:[di+1], ah

@@row_next:
	add	di, ROW_SIZE
	loop	@@row_loop
	or	@@rows_after_roll, @@rows_after_roll
	jz	short @@pellet_next
	sub	di, PLANE_SIZE
	xchg	cx, @@rows_after_roll
	jmp	short @@row_loop
; ---------------------------------------------------------------------------

@@pellet_next:
	add	bx, size pellet_render_t
	dec	bp
	jnz	short @@pellet_loop
	pop	di
	pop	si
	pop	bp
	retn
_pellets_render_bottom	endp
