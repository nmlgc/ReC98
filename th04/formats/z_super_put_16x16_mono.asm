public @Z_SUPER_PUT_16X16_MONO_RAW$QI
@z_super_put_16x16_mono_raw$qi proc near
	; Parameters
	arg_bx near, @patnum:word
	@@left	equ <cx>
	@@top 	equ <ax>

	; Locals
	@@PATTERN_HEIGHT = 16
	@@first_bit	equ <cl>
	@@vo       	equ <di>

	push	ds
	push	si
	push	di

	; v o = (top * ROW_SIZE)
	mov	@@vo, @@top
	shl	@@top, 2
	add	@@vo, @@top
	shl	@@vo, 4

	; vo += (left >> BYTE_BITS);
	; first_bit = (left & BYTE_MASK);
	mov	ax, @@left
	and	@@left, 7
	shr	ax, 3
	add	@@vo, ax

	mov	bx, @patnum
	shl	bx, 1
	mov	ds, _super_patdata[bx]
	xor	si, si
	mov	ch, @@PATTERN_HEIGHT

	; ZUN bloat: Never taken because CX is never 0 here, thanks to the
	; instruction immediately above.
	jcxz	short @@BYTEALIGNED

	mov	dx, 0FFFFh
	shr	dl, @@first_bit
	mov	dh, dl
	not	dh
	test	@@vo, 1
	jnz	short @@ODD

@@EVEN:
	lodsw
	ror	ax, @@first_bit
	mov	bl, al
	and	al, dl
	and	bl, dh
	mov	es:[@@vo], ax
	mov	es:[@@vo+2], bl
	add	@@vo, ROW_SIZE
	dec	ch
	jnz	short @@EVEN
	jmp	short @@RETURN
	even

@@ODD:
	lodsw
	ror	ax, @@first_bit
	mov	bh, al
	and	al, dl
	and	bh, dh
	mov	bl, ah
	mov	es:[@@vo], al
	mov	es:[@@vo+1], bx
	add	@@vo, ROW_SIZE
	dec	ch
	jnz	short @@ODD
	jmp	short @@RETURN
	even

@@BYTEALIGNED:
	lodsw
	mov	es:[di], ax
	add	di, ROW_SIZE
	dec	ch
	jnz	short @@BYTEALIGNED

@@RETURN:
	pop	di
	pop	si
	pop	ds
	ret_bx
@z_super_put_16x16_mono_raw$qi endp
	even
