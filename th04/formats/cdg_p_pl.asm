	.386
	locals

include pc98.inc
include th03/formats/cdg.inc

	extrn _cdg_slots:cdg_t:CDG_SLOT_COUNT
	extern DOTS16_MASK_UNALIGNED:word:16

SHARED	segment word public 'CODE' use16
	assume cs:SHARED

public CDG_PUT_PLANE
cdg_put_plane proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@plane:word, @@slot:word, @@top:word, @@left:word
	@@first_bit_wide	equ <cx>	; Just remove this
	@@first_bit	equ <cl>
	@@carry_dots_cur	equ <dx>
	@@carry_dots_next	equ <bx>
	@@stride_backwards_tmp	equ <dx>
	@@stride_backwards	equ <bp>

	push	bp
	mov	bp, sp
	push	si
	push	di

	cdg_slot_offset	si, @@slot

	mov	@@first_bit_wide, @@left
	mov	di, @@first_bit_wide
	sar	di, 4
	shl	di, 1	; DI = @@left as word-aligned vram_x_t
	add	di, [si+cdg_t.offset_at_bottom_left]
	mov	ax, [si+cdg_t.vram_dword_w]
	shl	ax, 1	; AX = VRAM words
	mov	@@width_words, al
	and	@@first_bit_wide, 15
	mov	bx, @@first_bit_wide
	shl	bx, 1
	mov	bx, DOTS16_MASK_UNALIGNED[bx]
	mov	@@first_mask_1, bx
	mov	@@first_mask_2, bx
	jmp	short $+2
	shl	ax, 1	; AX = VRAM bytes
	add	ax, ROW_SIZE
	mov	@@stride_backwards_tmp, ax

	cdg_dst_segment	es, @@top, bx

	push	ds
	mov	ax, [si+cdg_t.seg_colors]
	mov	si, [si+cdg_t.CDG_plane_size]
	mov	ds, ax
	mov	ax, @@plane
	mov	@@stride_backwards, @@stride_backwards_tmp
	mul	si	; AX = (@@plane * cdg.plane_size)
	mov	si, ax
	cld

@@row_loop:
	@@width_words = byte ptr $+1
	mov	ch, 80h
	lodsw
	ror	ax, @@first_bit
	mov	@@carry_dots_cur, ax
	@@first_mask_1 = word ptr $+1
	and	ax, 1234h
	xor	@@carry_dots_cur, ax
	stosw
	dec	ch

@@other_words:
	lodsw
	ror	ax, @@first_bit
	mov	@@carry_dots_next, ax
	@@first_mask_2 = word ptr $+1
	and	ax, 1234h
	xor	@@carry_dots_next, ax
	or	ax, @@carry_dots_cur
	mov	@@carry_dots_cur, @@carry_dots_next
	stosw
	dec	ch
	jnz	short @@other_words

	; Any dots left at the end of the row?
	or	@@carry_dots_cur, @@carry_dots_cur
	jz	short @@next_row
	mov	es:[di], @@carry_dots_cur
	xor	@@carry_dots_cur, @@carry_dots_cur	; yeah, this one is redundant

@@next_row:
	sub	di, @@stride_backwards
	jns	short @@row_loop
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	8
cdg_put_plane endp
SHARED	ends

	end
