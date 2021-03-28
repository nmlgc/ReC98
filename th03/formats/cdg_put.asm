	.386
	.model use16 large
	locals

include pc98.inc
include libs/master.lib/master.inc
include th03/formats/cdg.inc

	extrn _cdg_slots:cdg_t:CDG_SLOT_COUNT
	extern _hflip_lut:byte:256

SHARED	segment word public 'CODE' use16
	assume cs:SHARED

public CDG_PUT_8
cdg_put_8 proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@slot:word, @@top:word, @@left:word

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0

	cdg_slot_offset	si, @@slot

	mov	ax, [si+cdg_t.seg_colors]
	mov	@@seg_colors, ax

	cdg_dst_offset	ax, si, @@left

	mov	di, ax
	mov	@@offset_at_bottom_left, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	@@width_for_alpha_loop, ax
	mov	@@width_for_colors_loop, ax
	shl	ax, 2	; *= size dword
	add	ax, ROW_SIZE
	mov	@@stride, ax
	jmp	short $+2

	cdg_dst_segment	es, @@top, bx

	push	ds
	mov	ax, [si+cdg_t.seg_alpha]
	mov	ds, ax
	xor	si, si
	@@stride = word ptr $+1
	mov	dx, 1234h
	cld

@@loop_alpha:
	@@width_for_alpha_loop = word ptr $+1
	mov	cx, 1234h
	rep movsd
	sub	di, dx
	jns	short @@loop_alpha

	GRCG_OFF_VIA_XOR	al

	@@offset_at_bottom_left = word ptr $+1
	mov	bx, 1234h
	mov	di, bx
	xor	si, si
	@@seg_colors = word ptr $+1
	mov	ax, 1234h
	mov	ds, ax

@@loop_colors:
	@@width_for_colors_loop = word ptr $+1
	mov	cx, 1234h

@@row_colors:
	mov	eax, [si]
	or	es:[di], eax
	add	si, dword
	add	di, dword
	loop	@@row_colors
	sub	di, dx
	jns	short @@loop_colors
	mov	di, bx
	vram_plane_next es, @@loop_colors

@@ret:
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_8 endp
	even


public CDG_PUT_HFLIP_8
cdg_put_hflip_8 proc
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@slot:word, @@top:word, @@left:word

	; DS is the segment of [hflip_lut], and mustn't be changed here
	@@seg_src	equ <fs>

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 0

	cdg_slot_offset	si, @@slot
	cdg_dst_offset	ax, si, @@left

	mov	bx, [si+cdg_t.vram_dword_w]
	shl	bx, 2	; *= size dword
	add	ax, bx
	dec	ax
	mov	di, ax
	mov	@@last_x_alpha, ax
	mov	@@last_x_colors, ax
	mov	@@width_bytes_alpha, bx
	mov	@@width_bytes_colors, bx
	mov	ax, ROW_SIZE
	sub	ax, bx
	mov	@@stride_alpha, ax
	mov	@@stride_colors, ax
	jmp	short $+2

	cdg_dst_segment	es, @@top, bx

	mov	bx, offset _hflip_lut
	mov	@@seg_src, [si+cdg_t.seg_alpha]
	xor	si, si
	@@stride_alpha = word ptr $+1
	mov	dx, 1234h
	even

@@loop_alpha:
	@@width_bytes_alpha = word ptr $+1
	mov	cx, 1234h

@@row_alpha:
	mov	al, @@seg_src:[si]
	xlat	;
	mov	es:[di], al
	inc	si
	dec	di
	loop	@@row_alpha
	sub	di, dx
	jns	short @@loop_alpha

	GRCG_OFF_VIA_XOR	al

	@@last_x_alpha = word ptr $+1
	mov	di, 1234h

	cdg_slot_offset	si, @@slot

	mov	@@seg_src, [si+cdg_t.seg_colors]
	xor	si, si
	@@stride_colors = word ptr $+1
	mov	dx, 1234h
	even

@@loop_colors:
	@@width_bytes_colors = word ptr $+1
	mov	cx, 1234

@@row_colors:
	mov	al, @@seg_src:[si]
	xlat	;
	or	es:[di], al
	inc	si
	dec	di
	loop	@@row_colors
	sub	di, dx
	jns	short @@loop_colors

	@@last_x_colors = word ptr $+1
	mov	di, 1234h
	vram_plane_next es, @@loop_colors

@@ret:
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_hflip_8 endp
	even
SHARED	ends

	end
