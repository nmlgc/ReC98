; (identical to the already decompiled TH02 version, except for the first two
; X coordinates)

public CMT_BACK_FREE
cmt_back_free	proc near
	push	bp
	mov	bp, sp
	call	hmem_free pascal, word ptr cmt_back_PL_B+2
	call	hmem_free pascal, word ptr cmt_back_PL_R+2
	call	hmem_free pascal, word ptr cmt_back_PL_G+2
	call	hmem_free pascal, word ptr cmt_back_PL_E+2
	pop	bp
	retn
cmt_back_free	endp


public CMT_BACK_PUT
cmt_back_put	proc near

@@pd		= word ptr -2

	enter	2, 0
	push	si
	push	di
	xor	cx, cx
	mov	si, 64
	jmp	short loc_AB05
; ---------------------------------------------------------------------------

loc_AA89:
	mov	di, 304
	jmp	short loc_AAFE
; ---------------------------------------------------------------------------

loc_AA8E:
	mov	ax, di
	sar	ax, 3
	mov	dx, si
	shl	dx, 6
	add	ax, dx
	mov	dx, si
	shl	dx, 4
	add	ax, dx
	mov	[bp+@@pd], ax
	les	bx, cmt_back_PL_B
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_B
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	les	bx, cmt_back_PL_R
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_R
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	les	bx, cmt_back_PL_G
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_G
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	les	bx, cmt_back_PL_E
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_E
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	add	cx, 4
	add	di, (4 * 8)

loc_AAFE:
	cmp	di, 624
	jl	short loc_AA8E
	inc	si

loc_AB05:
	cmp	si, 80
	jl	loc_AA89
	mov	si, 80
	jmp	short loc_AB8D
; ---------------------------------------------------------------------------

loc_AB11:
	mov	di, 304
	jmp	short loc_AB86
; ---------------------------------------------------------------------------

loc_AB16:
	mov	ax, di
	sar	ax, 3
	mov	dx, si
	shl	dx, 6
	add	ax, dx
	mov	dx, si
	shl	dx, 4
	add	ax, dx
	mov	[bp+@@pd], ax
	les	bx, cmt_back_PL_B
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_B
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	les	bx, cmt_back_PL_R
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_R
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	les	bx, cmt_back_PL_G
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_G
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	les	bx, cmt_back_PL_E
	add	bx, cx
	mov	eax, es:[bx]
	les	bx, _VRAM_PLANE_E
	add	bx, [bp+@@pd]
	mov	es:[bx], eax
	add	cx, 4
	add	di, (4 * 8)

loc_AB86:
	cmp	di, 624
	jl	short loc_AB16
	inc	si

loc_AB8D:
	cmp	si, 384
	jl	loc_AB11
	pop	di
	pop	si
	leave
	retn
cmt_back_put	endp
