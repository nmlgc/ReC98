public POINTNUMS_ADD_YELLOW, POINTNUMS_ADD_WHITE
pointnums_add	proc near

@@number  	= word ptr  4
@@center_y	= word ptr  6
@@center_x	= word ptr  8

pointnums_add_yellow:
	mov	bl, _pointnum_yellow_p
	inc	_pointnum_yellow_p
	cmp	bl, (POINTNUM_YELLOW_COUNT - 1)
	jb	short @@skip_past_white_numbers
	mov	_pointnum_yellow_p, 0

@@skip_past_white_numbers:
	xor	bh, bh
	add	bx, POINTNUM_WHITE_COUNT
	jmp	short @@add

pointnums_add_white:
	mov	bl, _pointnum_white_p
	mov	bh, 0
	inc	_pointnum_white_p
	cmp	bl, (POINTNUM_WHITE_COUNT - 1)
	jb	short @@add
	mov	_pointnum_white_p, 0

@@add:
	shl	bx, 4
	add	bx, offset _pointnums
	mov	word ptr [bx+pointnum_t.flag], 1	; flag = 1, age = 0
	push	bp
	mov	bp, sp
	mov	ax, [bp+@@center_x]
	mov	[bx+pointnum_t.PN_center_cur.x], ax
	mov	ax, [bp+@@center_y]
	mov	[bx+pointnum_t.PN_center_cur.y], ax

	if GAME eq 5
		push	si
		mov	si, bx
	else
		mov	[bx+pointnum_t.PN_width], 0
		mov	al, _pointnum_times_2
		mov	[bx+pointnum_t.PN_times_2], al
	endif

	lea	ax, [bx+pointnum_t.PN_digits_lebcd + (POINTNUM_DIGITS - 1)]
	call	pointnum_digits_set pascal, ax, [bp+@@number]
	if GAME eq 5
		mov	[si+pointnum_t.PN_width], ax
		pop	si
	endif
	pop	bp
	retn	6
pointnums_add	endp
	nop
