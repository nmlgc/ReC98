	.386
	.model use16 large SHARED

include pc98.inc

	extrn _bgimage:word:PLANE_COUNT

	.code SHARED

public BGIMAGE_PUT_RECT_16
bgimage_put_rect_16 proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@h:word, @@w:word, @@top:word, @@left:word
	@@planes_left	equ <dl>
	@@rows_left	equ <bx>
	@@stride	equ <bp>

	push	bp
	mov	bp, sp
	push	di
	push	si
	push	ds
	cld
	mov	ax, @@left
	mov	dx, @@top
	mov	bx, ax
	sar	bx, 4
	shl	bx, 1
	shl	dx, 6
	add	bx, dx
	shr	dx, 2
	add	bx, dx
	mov	cs:[@@vram_offset], bx
	and	ax, 0Fh
	mov	cx, ax
	add	ax, @@w
	shr	ax, 4
	or	cx, cx
	jz	short @@x_on_word_boundary
	inc	ax

@@x_on_word_boundary:
	mov	cs:[@@width_words], ax
	jmp	short $+2
	mov	cx, (ROW_SIZE / 2)
	sub	cx, ax
	shl	cx, 1
	mov	ax, @@h
	mov	@@stride, cx
	push	SEG_PLANE_E
	push	_bgimage[3 * word]
	push	SEG_PLANE_G
	push	_bgimage[2 * word]
	push	SEG_PLANE_R
	push	_bgimage[1 * word]
	push	SEG_PLANE_B
	push	_bgimage[0 * word]
	mov	@@planes_left, PLANE_COUNT

@@next_plane:
	mov	@@rows_left, ax

@@vram_offset = word ptr $+1
	mov	di, 1234h
	pop	ds
	pop	es
@@next_row:
@@width_words = word ptr $+1
	mov	cx, 1234h
	mov	si, di
	rep movsw
	add	di, @@stride
	dec	@@rows_left
if GAME eq 5
	jnz	short @@next_row
else
	jns	short @@next_row
endif
	dec	@@planes_left
	jnz	short @@next_plane
	pop	ds
	pop	si
	pop	di
	pop	bp
	retf	8
bgimage_put_rect_16 endp
	even

	end
