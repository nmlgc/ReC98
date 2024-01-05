; (identical to the already decompiled TH02 version, except for the first X
; coordinate)

public DRAW_CMT
draw_cmt	proc near

@@track		= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	music_cmt_load pascal, [bp+@@track]
	call	@nopoly_B_put$qv
	call	cmt_back_put
	push	1300040h
	push	1Fh
	push	ds
	push	offset _music_cmt
	call	graph_putsa_fx
	mov	di, 1
	jmp	short loc_ABDC
; ---------------------------------------------------------------------------

loc_ABC0:
	push	130h
	lea	ax, [di+4]
	shl	ax, 4
	push	ax
	push	1Dh
	push	ds
	mov	ax, di
	imul	ax, MUSIC_CMT_LINE_LEN
	add	ax, offset _music_cmt
	push	ax
	call	graph_putsa_fx
	inc	di

loc_ABDC:
	cmp	di, MUSIC_CMT_LINE_COUNT
	jl	short loc_ABC0
	xor	si, si
	jmp	short loc_ABFA
; ---------------------------------------------------------------------------

loc_ABE5:
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, es:[bx]
	mov	es, _nopoly_B
	mov	es:[si], eax
	add	si, 4

loc_ABFA:
	cmp	si, PLANE_SIZE
	jl	short loc_ABE5
	pop	di
	pop	si
	pop	bp
	retn	2
draw_cmt	endp
