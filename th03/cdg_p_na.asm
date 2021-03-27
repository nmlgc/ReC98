	.386
	locals

include pc98.inc
include th03/formats/cdg.inc

	extrn _cdg_slots:cdg_t:CDG_SLOT_COUNT

SHARED	segment word public 'CODE' use16
	assume cs:SHARED

public CDG_PUT_NOALPHA_8
cdg_put_noalpha_8 proc far

@@slot	= word ptr  6
@@top 	= word ptr  8
@@left	= word ptr  10

@@vram_offset_at_bottom_left equ <bx>

	push	bp
	mov	bp, sp
	push	si
	push	di

	cdg_slot_offset	si, [bp+@@slot]
	cdg_dst_offset	ax, si, [bp+@@left]

	mov	di, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	word ptr cs:@@width, ax
	jmp	short $+2
	shl	ax, 2
	add	ax, ROW_SIZE
	mov	dx, ax

	cdg_dst_segment	es, [bp+@@top], bx

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
cdg_put_noalpha_8 endp
	even
SHARED	ends

	end
