public POINTNUMS_INIT
pointnums_init	proc near
	mov	_pointnum_white_p, 0
	mov	_pointnum_yellow_p, 0
	retn
pointnums_init	endp
	even


public POINTNUMS_INVALIDATE
pointnums_invalidate	proc near
	push	si
	push	di
	mov	_tile_invalidate_box.y, POINTNUM_H
	mov	si, offset _pointnums
	mov	di, POINTNUM_COUNT

@@loop:
	cmp	[si+pointnum_t.flag], 0
	jz	short @@next
	mov	ax, [si+pointnum_t.PN_width]
	mov	_tile_invalidate_box.x, ax
	mov	ax, [si+pointnum_t.PN_center_cur.x]
	if GAME eq 4
		cmp	[si+pointnum_t.PN_times_2], 0
		jz	short @@not_times_2
		add	ax, ((POINTNUM_TIMES_2_W / 2) shl 4)

	@@not_times_2:
	endif
	call	tiles_invalidate_around pascal, [si+pointnum_t.PN_center_prev_y], ax

@@next:
	add	si, size pointnum_t
	dec	di
	jnz	short @@loop
	pop	di
	pop	si
	retn
pointnums_invalidate	endp
	even


public POINTNUMS_UPDATE
pointnums_update	proc near
	push	si
	push	di
	mov	_pointnum_first_yellow_alive, 0
	mov	bx, offset _pointnums_alive
	mov	si, offset _pointnums
	mov	di, POINTNUM_COUNT

@@loop:
	cmp	[si+pointnum_t.flag], 0
	jz	short @@next
	cmp	[si+pointnum_t.flag], 2
	jnz	short @@still_alive
	mov	[si+pointnum_t.flag], 0
	jmp	short @@next
; ---------------------------------------------------------------------------

@@still_alive:
	mov	cl, [si+pointnum_t.age]
	mov	ax, [si+pointnum_t.PN_center_cur.y]
	mov	[si+pointnum_t.PN_center_prev_y], ax
	cmp	cl, POINTNUM_POPUP_FRAMES
	jb	short @@popup_frames_elapsed
	sub	ax, (POINTNUM_POPUP_DISTANCE / POINTNUM_POPUP_FRAMES)

@@popup_frames_elapsed:
	mov	[si+pointnum_t.PN_center_cur.y], ax
	cmp	ax, ((-POINTNUM_H / 2) shl 4)
	jg	short @@not_clipped
	mov	[si+pointnum_t.flag], 2
	jmp	short @@next
; ---------------------------------------------------------------------------

@@not_clipped:
	inc	cl
	mov	[si+pointnum_t.age], cl
	cmp	cl, POINTNUM_FRAMES
	jbe	short @@not_remove
	mov	[si+pointnum_t.flag], 2
	jmp	short @@next
; ---------------------------------------------------------------------------

@@not_remove:
	mov	[bx], si
	cmp	di, POINTNUM_YELLOW_COUNT
	ja	short @@not_yellow
	cmp	_pointnum_first_yellow_alive, 0
	jnz	short @@not_yellow
	mov	_pointnum_first_yellow_alive, si

@@not_yellow:
	add	bx, word

@@next:
	add	si, size pointnum_t
	dec	di
	jnz	short @@loop
	mov	word ptr [bx], 0
	pop	di
	pop	si
	retn
pointnums_update	endp
	even
