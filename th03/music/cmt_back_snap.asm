; (identical to the already decompiled TH02 version, except for the first two
; X coordinates)

public CMT_BACK_SNAP
cmt_back_snap	proc near

@@i 	= word ptr -6
@@pd	= word ptr -4
@@x 	= word ptr -2

	enter	6, 0
	push	si
	push	di
	mov	[bp+@@i], 0
	jmp	short loc_A8F7
; ---------------------------------------------------------------------------

loc_A8DC:
	call	hmem_allocbyte pascal, 3200h
	mov	bx, [bp+@@i]
	shl	bx, 2
	mov	word ptr _cmt_back[bx]+2, ax
	mov	word ptr _cmt_back[bx]+0, 0
	inc	[bp+@@i]

loc_A8F7:
	cmp	[bp+@@i], 4
	jl	short loc_A8DC
	xor	si, si
	mov	di, 64
	jmp	short loc_A97D
; ---------------------------------------------------------------------------

loc_A904:
	mov	[bp+@@x], 304
	jmp	short loc_A975
; ---------------------------------------------------------------------------

loc_A90B:
	mov	ax, [bp+@@x]
	sar	ax, 3
	mov	dx, di
	shl	dx, 6
	add	ax, dx
	mov	dx, di
	shl	dx, 4
	add	ax, dx
	mov	[bp+@@pd], ax
	les	bx, _VRAM_PLANE_B
	assume es:nothing
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_B
	mov	es:[bx+si], eax
	les	bx, _VRAM_PLANE_R
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_R
	mov	es:[bx+si], eax
	les	bx, _VRAM_PLANE_G
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_G
	mov	es:[bx+si], eax
	les	bx, _VRAM_PLANE_E
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_E
	mov	es:[bx+si], eax
	add	si, 4
	add	[bp+@@x], (4 * 8)

loc_A975:
	cmp	[bp+@@x], 624
	jl	short loc_A90B
	inc	di

loc_A97D:
	cmp	di, 80
	jl	short loc_A904
	mov	di, 80
	jmp	short loc_AA00
; ---------------------------------------------------------------------------

loc_A987:
	mov	[bp+@@x], 304
	jmp	short loc_A9F8
; ---------------------------------------------------------------------------

loc_A98E:
	mov	ax, [bp+@@x]
	sar	ax, 3
	mov	dx, di
	shl	dx, 6
	add	ax, dx
	mov	dx, di
	shl	dx, 4
	add	ax, dx
	mov	[bp+@@pd], ax
	les	bx, _VRAM_PLANE_B
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_B
	mov	es:[bx+si], eax
	les	bx, _VRAM_PLANE_R
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_R
	mov	es:[bx+si], eax
	les	bx, _VRAM_PLANE_G
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_G
	mov	es:[bx+si], eax
	les	bx, _VRAM_PLANE_E
	add	bx, [bp+@@pd]
	mov	eax, es:[bx]
	les	bx, cmt_back_PL_E
	mov	es:[bx+si], eax
	add	si, 4
	add	[bp+@@x], (4 * 8)

loc_A9F8:
	cmp	[bp+@@x], 624
	jl	short loc_A98E
	inc	di

loc_AA00:
	cmp	di, 384
	jl	short loc_A987
	pop	di
	pop	si
	leave
	retn
cmt_back_snap	endp
