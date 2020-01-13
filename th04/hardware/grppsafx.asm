public GRAPH_PUTSA_FX
graph_putsa_fx	proc far

@@str  	= dword	ptr  6
@@color	= word ptr  0Ah
@@y    	= word ptr  0Ch
@@x    	= word ptr  0Eh

	push	bp
	mov	bp, sp
	push	si
	push	di
	push	ds
	mov	dx, [bp+@@color]
	GRCG_NOINT_SETMODE_VIA_MOV al, GC_RMW
	GRCG_SETCOLOR_DIRECT_INLINED dx
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	dx, [bp+@@y]
	shl	dx, 6
	mov	di, dx
	shr	dx, 2
	add	di, dx
	mov	cx, [bp+@@x]
	mov	al, 0Bh
	out	68h, al
	mov	bx, _graph_putsa_fx_func
	add	bx, bx
	cmp	bx, 8
	jb	short @@not_masking
	cmp	bx, 16
	jnb	short @@not_masking

	mov	ax, (GLYPH_MASK_TABLE - 8)[bx]
	mov	word ptr cs:grppsafx_glyph_mask, ax
	mov	bx, 8

@@not_masking:
	mov	ax, GLYPH_WEIGHT_FUNC_TABLE_1[bx]
	mov	word ptr cs:grppsafx_glyph_func_1, ax

	mov	ax, GLYPH_WEIGHT_FUNC_TABLE_2[bx]
	mov	word ptr cs:grppsafx_glyph_func_2, ax

	mov	ax, _graph_putsa_fx_spacing
	mov	word ptr cs:grppsafx_glyph_spacing_1, ax
	mov	word ptr cs:grppsafx_glyph_spacing_2, ax
	push	ds
	pop	fs
	assume fs:_DATA
	lds	si, [bp+@@str]
	lodsb
	or	al, al
	jz	short @@EXITLOOP

@@SLOOP:
	mov	dx, cx
	shr	dx, 3
	add	di, dx
	and	cx, 7
	mov	ah, 9
	test	al, 0E0h
	jns	short @@ANK_OR_RIGHT
	jp	short @@NOT_ANK_BUT_RIGHT

@@KANJI:	mov	ah, al
		lodsb
		shl	ah, 1
		cmp	al, 9Fh
		jnb	short @@SKIP
			cmp	al, 80h
			adc	ax, 0FEDFh
@@SKIP:			sbb	al, 0FEh

	and	ax, 7F7Fh
	out	0A1h, al
	mov	al, ah
	out	0A3h, al
	nop

@@graph_double_loop_w:
	mov	al, ch
	or	al, 20h
	out	0A5h, al
	in	al, 0A9h
	mov	ah, al
	mov	al, ch
	out	0A5h, al
	in	al, 0A9h

grppsafx_glyph_func_1 equ $+1
	call	glyph_weight_2
	mov	bh, al
	mov	bl, 0
	shr	ax, cl
	shr	bx, cl
	xchg	ah, al
	stosw
	mov	es:[di], bl
	add	di, ROW_SIZE - 2
	inc	ch
	cmp	ch, GLYPH_H
	jb	short @@graph_double_loop_w
	sub	di, ROW_SIZE * GLYPH_H

grppsafx_glyph_spacing_1 equ $+1
	mov	dx, 1234h

@@next_char:
	xor	ch, ch
	add	cx, dx
	lodsb
	or	al, al
	jnz	short @@SLOOP

@@EXITLOOP:
	mov	al, 0Ah
	out	68h, al
	GRCG_OFF_VIA_XOR al
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	0Ah
; ---------------------------------------------------------------------------

@@NOT_ANK_BUT_RIGHT:
	add	ax, 80h

@@ANK_OR_RIGHT:
	cmp	al, ' '
	jz	short @@dont_print_space

	out	0A1h, al
	mov	al, ah
	out	0A3h, al
	nop

@@graph_double_loop:
	mov	al, ch
	or	al, 20h
	out	0A5h, al
	in	al, 0A9h
	xor	ah, ah

grppsafx_glyph_func_2 equ $+1
	call	glyph_weight_2
	ror	ax, cl
	stosw
	add	di, ROW_SIZE - 2
	inc	ch
	cmp	ch, GLYPH_H
	jb	short @@graph_double_loop
	sub	di, ROW_SIZE * GLYPH_H

@@dont_print_space:
grppsafx_glyph_spacing_2 equ $+1
	mov	dx, 1234h
	shr	dx, 1
	jmp	short @@next_char
graph_putsa_fx	endp
	even


glyph_weight_1	label near
	mov	dx, ax
	add	dx, dx
	or	ax, dx
glyph_weight_0	label near
	retn

glyph_weight_3	label near
	mov	dx, ax
	shl	dx, 1
	or	ax, dx
glyph_weight_2	label near
	mov	dx, ax
	mov	bp, ax
	add	bp, bp
	or	ax, bp
	xor	dx, ax
	add	dx, dx
	not	dx
	and	ax, dx
	retn

glyph_double_and_mask	proc near
	call	glyph_weight_2
	mov	bl, ch
	and	bx, 3
	add	bx, bx

grppsafx_glyph_mask equ $+3
	and	ax, fs:[bx+1234h]
	retn
glyph_double_and_mask	endp
