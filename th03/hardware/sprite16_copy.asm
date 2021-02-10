src_seg equ <bx>
dst_seg equ <dx>

; void __fastcall near page_blit(page_t dst_page)
page_blit proc near
	mov	cx, (SPRITE16_PLANE_SIZE / 4)
	xor	al, 1
	out	0A6h, al	; graph_accesspage
	mov	ds, src_seg
	mov	es, dst_seg
	xor	di, di
	mov	si, di
	rep movsd
	xchg	src_seg, dst_seg
	retn
page_blit endp
	even


public SPRITE16_SPRITES_COPY_PAGE
SPRITE16_SPRITES_COPY_PAGE proc far

	xor	dst_seg, dst_seg
	mov	bx, SPRITE16_PLANE_SIZE
	push	bx
	nopcall	smem_wget
	xchg	ax, dst_seg
	jb	short @@ret

arg_bx	far, @dst_page:word

	mov	ax, @dst_page
	push	si
	push	di
	push	ds
	mov	src_seg, (SEG_PLANE_B + (SPRITE16_SPRITES_OFFSET / 16))
	call	page_blit
	call	page_blit
	mov	src_seg, (SEG_PLANE_R + (SPRITE16_SPRITES_OFFSET / 16))
	call	page_blit
	call	page_blit
	mov	src_seg, (SEG_PLANE_G + (SPRITE16_SPRITES_OFFSET / 16))
	call	page_blit
	call	page_blit
	mov	src_seg, (SEG_PLANE_E + (SPRITE16_SPRITES_OFFSET / 16))
	call	page_blit
	call	page_blit
	pop	ds
	pop	di
	pop	si
	push	dst_seg
	nopcall	smem_release
	mov	ax, 1

@@ret:
	ret_bx
SPRITE16_SPRITES_COPY_PAGE endp

src_seg equ <>
dst_seg equ <>
