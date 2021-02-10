public Z_SUPER_ROLL_PUT_16X16_MONO_RAW
z_super_roll_put_16x16_mono_raw	proc near

; Parameters
arg_bx near, @patnum:word
@@left equ cx
@@top equ ax

; Locals
@@PATTERN_HEIGHT = 16
@@rows_left equ ch
@@carry_pixels equ bl

	push	ds
	push	si
	push	di
	mov	di, @@top
	shl	@@top, 2
	add	di, @@top
	shl	di, 4
	mov	ax, @@left
	shr	ax, 3
	add	di, ax
	mov	bx, @patnum
	shl	bx, 1
	mov	ds, super_patdata[bx]
	xor	si, si
	mov	@@rows_left, @@PATTERN_HEIGHT
	and	cl, 7
	jz	short @@BYTEALIGNED
	mov	dx, 0FFFFh
	shr	dl, cl
	xor	dh, dl
	test	al, 1
	jnz	short @@ODD

@@EVEN:
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@EVEN_YLOOP2
	even

@@EVEN_YLOOP1:
	lodsw
	ror	ax, cl
	mov	@@carry_pixels, al
	and	al, dl
	or	ax, ax
	jz	short @@EVEN_YLOOP1_SKIP_BLANK_WORD
	mov	es:[di], ax

@@EVEN_YLOOP1_SKIP_BLANK_WORD:
	and	@@carry_pixels, dh
	jz	short @@EVEN_YLOOP1_SKIP_BLANK_3RD
	mov	es:[di+2], @@carry_pixels

@@EVEN_YLOOP1_SKIP_BLANK_3RD:
	add	di, ROW_SIZE
	dec	@@rows_left
	cmp	di, PLANE_SIZE
	jb	short @@EVEN_YLOOP1
	sub	di, PLANE_SIZE
	nop

@@EVEN_YLOOP2:
	lodsw
	ror	ax, cl
	mov	@@carry_pixels, al
	and	al, dl
	or	ax, ax
	jz	short @@EVEN_YLOOP2_SKIP_BLANK_WORD
	mov	es:[di], ax

@@EVEN_YLOOP2_SKIP_BLANK_WORD:
	and	@@carry_pixels, dh
	jz	short @@EVEN_YLOOP2_SKIP_BLANK_3RD
	mov	es:[di+2], @@carry_pixels

@@EVEN_YLOOP2_SKIP_BLANK_3RD:
	add	di, ROW_SIZE
	dec	@@rows_left
	jnz	short @@EVEN_YLOOP2
	jmp	short @@RETURN
; ---------------------------------------------------------------------------

@@BYTEALIGNED:
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@BYTEALIGNED_YLOOP2
	even

@@BYTEALIGNED_YLOOP1:
	lodsw
	or	ax, ax
	jz	short @@BYTEALIGNED_YLOOP1_SKIP_BLANK
	mov	es:[di], ax

@@BYTEALIGNED_YLOOP1_SKIP_BLANK:
	add	di, ROW_SIZE
	dec	@@rows_left
	cmp	di, (ROW_SIZE * RES_Y)
	jb	short @@BYTEALIGNED_YLOOP1
	sub	di, (ROW_SIZE * RES_Y)
	even

@@BYTEALIGNED_YLOOP2:
	lodsw
	or	ax, ax
	jz	short @@BYTEALIGNED_YLOOP2_SKIP_BLANK
	mov	es:[di], ax

@@BYTEALIGNED_YLOOP2_SKIP_BLANK:
	add	di, ROW_SIZE
	dec	@@rows_left
	jnz	short @@BYTEALIGNED_YLOOP2
	jmp	short @@RETURN
; ---------------------------------------------------------------------------

@@ODD:
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@ODD_YLOOP2
	even

@@ODD_YLOOP1:
	lodsw
	ror	ax, cl
	mov	bh, al
	and	al, dl
	jz	short @@ODD_YLOOP1_SKIP_BLANK_1ST
	mov	es:[di], al

@@ODD_YLOOP1_SKIP_BLANK_1ST:
	and	bh, dh
	mov	@@carry_pixels, ah
	or	bx, bx
	jz	short @@ODD_YLOOP1_SKIP_BLANK_WORD
	mov	es:[di+1], bx

@@ODD_YLOOP1_SKIP_BLANK_WORD:
	add	di, ROW_SIZE
	dec	@@rows_left
	cmp	di, PLANE_SIZE
	jb	short @@ODD_YLOOP1
	sub	di, PLANE_SIZE
	even

@@ODD_YLOOP2:
	lodsw
	ror	ax, cl
	mov	bh, al
	and	al, dl
	jz	short @@ODD_YLOOP2_SKIP_BLANK_1ST
	mov	es:[di], al

@@ODD_YLOOP2_SKIP_BLANK_1ST:
	and	bh, dh
	mov	@@carry_pixels, ah
	or	bx, bx
	jz	short @@ODD_YLOOP2_SKIP_BLANK_WORD
	mov	es:[di+1], bx

@@ODD_YLOOP2_SKIP_BLANK_WORD:
	add	di, ROW_SIZE
	dec	@@rows_left
	jnz	short @@ODD_YLOOP2

@@RETURN:
	pop	di
	pop	si
	pop	ds
	ret_bx
z_super_roll_put_16x16_mono_raw endp
	even
