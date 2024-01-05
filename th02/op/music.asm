; Already decompiled in th02\op_06.cpp, but we need to haul this around until
; we can insert the C version into TH03, TH04 and TH05. Everything here is
; identical in all 4 games.

; ... well, except for this. Even though TH05 does allocate space for 16
; polygons in the BSS segment as well.
if GAME eq 5
POLYGONS_RENDERED = 14
else
POLYGONS_RENDERED = 16
endif

	@nopoly_B_snap$qv procdesc near
	@nopoly_B_free$qv procdesc near
	@nopoly_B_put$qv procdesc near

polygon_build	proc near

var_3	= byte ptr -3
var_2	= word ptr -2
arg_0	= byte ptr  4
arg_2	= word ptr  6
arg_4	= word ptr  8
arg_6	= word ptr  0Ah
arg_8	= word ptr  0Ch
arg_A	= word ptr  0Eh

	enter	4, 0
	push	si
	push	di
	mov	di, [bp+arg_A]
	sar	[bp+arg_6], 4
	mov	[bp+var_2], 0
	jmp	short loc_A67F

loc_A628:
	mov	ax, [bp+var_2]
	shl	ax, 8
	cwd
	idiv	[bp+arg_2]
	add	al, [bp+arg_0]
	mov	[bp+var_3], al

if GAME ge 4
	push	[bp+arg_8]
	push	[bp+arg_4]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_CosTable8[bx]
	call	@polar$qiii
else
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_CosTable8[bx]
	push	[bp+arg_4]
	push	[bp+arg_8]
	call	@polar$qiii
	add	sp, 6
endif

	mov	bx, [bp+var_2]
	shl	bx, 2
	mov	[bx+di], ax

if GAME ge 4
	push	[bp+arg_6]
	push	[bp+arg_4]
	mov	al, [bp+var_3]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	call	@polar$qiii
else
	mov	al, [bp+var_3]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	push	[bp+arg_4]
	push	[bp+arg_6]
	call	@polar$qiii
	add	sp, 6
endif

	mov	bx, [bp+var_2]
	shl	bx, 2
	mov	[bx+di+2], ax
	inc	[bp+var_2]

loc_A67F:
	mov	ax, [bp+var_2]
	cmp	ax, [bp+arg_2]
	jl	short loc_A628
	mov	bx, [bp+var_2]
	shl	bx, 2
	mov	ax, [di]
	mov	[bx+di], ax
	mov	bx, [bp+var_2]
	shl	bx, 2
	mov	ax, [di+2]
	mov	[bx+di+2], ax
	pop	di
	pop	si
	leave
	retn	0Ch
polygon_build	endp

polygons_update_and_render	proc near
	push	bp
	mov	bp, sp
	push	si
	cmp	_polygons_initialized, 0
	jnz	loc_A752
	xor	si, si
	; Hack (jmp	loc_A746)
	; No idea why TASM can't assemble this properly after TH04's main() was
	; decompiled.
	db	0E9h, 91h, 00h

loc_A6B5:
	call	IRand
	mov	bx, 280h
	cwd
	idiv	bx
	mov	bx, si
	shl	bx, 2
	mov	polygon_pos.x[bx], dx
	call	IRand
	mov	bx, 1900h
	cwd
	idiv	bx
	mov	bx, si
	shl	bx, 2
	mov	polygon_pos.y[bx], dx
	call	IRand
	and	ax, 7
	mov	dx, 4
	sub	dx, ax
	mov	bx, si
	shl	bx, 2
	mov	polygon_move_speed.x[bx], dx
	mov	bx, si
	shl	bx, 2
	cmp	polygon_move_speed.x[bx], 0
	jnz	short loc_A70A
	mov	bx, si
	shl	bx, 2
	mov	polygon_move_speed.x[bx], 1

loc_A70A:
	call	IRand
	and	ax, 3
	shl	ax, 4
	add	ax, 20h	; ' '
	mov	bx, si
	shl	bx, 2
	mov	polygon_move_speed.y[bx], ax
	call	IRand
	mov	polygon_angle[si], al
	call	IRand
	and	al, 7
	mov	dl, 4
	sub	dl, al
	mov	polygon_rot_speed[si], dl
	cmp	polygon_rot_speed[si], 0
	jnz	short loc_A745
	mov	polygon_rot_speed[si], 4

loc_A745:
	inc	si

loc_A746:
	cmp	si, POLYGONS_RENDERED
	jl	loc_A6B5
	mov	_polygons_initialized, 1

loc_A752:
	xor	si, si
	jmp	loc_A88F

loc_A757:
	push	offset polygon_points
	mov	bx, si
	shl	bx, 2
	push	polygon_pos.x[bx]
	mov	bx, si
	shl	bx, 2
	push	polygon_pos.y[bx]
	mov	ax, si
	and	ax, 3
	shl	ax, 4
	add	ax, 40h
	push	ax
	mov	ax, si
	mov	bx, 4
	cwd
	idiv	bx
	add	ax, 3
	push	ax
	mov	al, polygon_angle[si]
	push	ax
	call	polygon_build
	mov	bx, si
	shl	bx, 2
	mov	ax, polygon_move_speed.x[bx]
	mov	bx, si
	shl	bx, 2
	add	polygon_pos.x[bx], ax
	mov	bx, si
	shl	bx, 2
	mov	ax, polygon_move_speed.y[bx]
	mov	bx, si
	shl	bx, 2
	add	polygon_pos.y[bx], ax
	mov	al, polygon_rot_speed[si]
	add	polygon_angle[si], al
	mov	bx, si
	shl	bx, 2
	cmp	polygon_pos.x[bx], 0
	jle	short loc_A7D1
	mov	bx, si
	shl	bx, 2
	cmp	polygon_pos.x[bx], 27Fh
	jl	short loc_A7E3

loc_A7D1:
	mov	bx, si
	shl	bx, 2
	mov	dx, 0FFFFh
	mov	ax, polygon_move_speed.x[bx]
	imul	dx
	mov	polygon_move_speed.x[bx], ax

loc_A7E3:
	mov	bx, si
	shl	bx, 2
	cmp	polygon_pos.y[bx], 1F40h
	jl	loc_A879
	call	IRand
	mov	bx, 280h
	cwd
	idiv	bx
	mov	bx, si
	shl	bx, 2
	mov	polygon_pos.x[bx], dx
	mov	bx, si
	shl	bx, 2
	mov	polygon_pos.y[bx], 0F9C0h
	call	IRand
	and	ax, 0Fh
	mov	dx, 8
	sub	dx, ax
	mov	bx, si
	shl	bx, 2
	mov	polygon_move_speed.x[bx], dx
	mov	bx, si
	shl	bx, 2
	cmp	polygon_move_speed.x[bx], 0
	jnz	short loc_A83E
	mov	bx, si
	shl	bx, 2
	mov	polygon_move_speed.x[bx], 1

loc_A83E:
	call	IRand
	and	ax, 3
	shl	ax, 4
	add	ax, 20h	; ' '
	mov	bx, si
	shl	bx, 2
	mov	polygon_move_speed.y[bx], ax
	call	IRand
	mov	polygon_angle[si], al
	call	IRand
	and	al, 7
	mov	dl, 4
	sub	dl, al
	mov	polygon_rot_speed[si], dl
	cmp	polygon_rot_speed[si], 0
	jnz	short loc_A879
	mov	polygon_rot_speed[si], 4

loc_A879:
	push	ds
	push	offset polygon_points
	mov	ax, si
	mov	bx, 4
	cwd
	idiv	bx
	add	ax, 3
	push	ax
	call	grcg_polygon_c
	inc	si

loc_A88F:
	cmp	si, POLYGONS_RENDERED
	jl	loc_A757
	pop	si
	pop	bp
	retn
polygons_update_and_render	endp


public MUSIC_FLIP
music_flip	proc near
	push	bp
	mov	bp, sp
	call	@nopoly_B_put$qv
if GAME eq 5
	call	@piano_render$qv
endif
	call	grcg_setcolor pascal, ((GC_RMW or GC_B) shl 16) + V_WHITE
	call	polygons_update_and_render
if GAME ge 4
	GRCG_OFF_CLOBBERING dx
	if GAME eq 5
		call	@frame_delay$qi pascal, 1
	endif
else
	call	grcg_off
endif
	graph_showpage _music_page
	mov	al, 1
	sub	al, _music_page
	mov	_music_page, al
	graph_accesspage al
if GAME le 4
	call	@frame_delay_2$qi pascal, 1
endif
	pop	bp
	retn
music_flip	endp
