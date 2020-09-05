	.386
	locals

include pc98.inc
include th03/formats/cdg.inc

	extrn _cdg_slots:cdg_t:CDG_SLOT_COUNT

SEG2	segment word public 'CODE' use16
	assume cs:SEG2

public CDG_PUT_NOALPHA
cdg_put_noalpha	proc far

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

@@vram_offset_at_bottom_left equ <bx>

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@slot]
	shl	si, 4	; *= size cdg_t
	add	si, offset _cdg_slots
	mov	ax, [bp+@@left]
	sar	ax, 3
	add	ax, [si+cdg_t.offset_at_bottom_left]
	mov	di, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	word ptr cs:@@width, ax
	jmp	short $+2
	shl	ax, 2
	add	ax, ROW_SIZE
	mov	dx, ax
	mov	ax, [bp+@@top]
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
	add	ax, SEG_PLANE_B
	mov	es, ax
	push	ds
	mov	ax, [si+cdg_t.seg_colors]
	mov	ds, ax
	xor	si, si
	mov	@@vram_offset_at_bottom_left, di
	cld
	even

@@row_loop:
@@width = word ptr $+1
	mov	cx, 1234h
	rep movsd
	sub	di, dx
	jns	short @@row_loop
	mov	di, bx
	vram_plane_next es, @@row_loop

@@ret:
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_noalpha	endp
	even
SEG2	ends

	end
