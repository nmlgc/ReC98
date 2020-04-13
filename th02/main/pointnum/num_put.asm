public POINTNUM_PUT
pointnum_put	proc near

@@num 	= word ptr  4
@@top 	= word ptr  6
@@left	= word ptr  8

@@first_byte_shr equ <dl>
@@second_byte_shl equ <dh>
@@cx_tmp equ <bx>

	enter	0, 0
	push	si
	push	di
	mov	ax, [bp+@@left]
	sar	ax, 3
	mov	dx, [bp+@@top]
	shl	dx, 6
	add	ax, dx
	shr	dx, 2
	add	ax, dx
	mov	di, ax
	mov	ax, [bp+@@left]
	and	ax, 7
	mov	@@first_byte_shr, al
	mov	bl, 8
	sub	bl, al
	mov	@@second_byte_shl, bl
	mov	si, [bp+@@num]
	shl	si, 3
	add	si, offset _sPOINTNUMS
	mov	cx, POINTNUM_H
	cmp	ax, 0
	jnz	short @@YLOOP

@@BYTEALIGNED:
	movsb
	add	di, (ROW_SIZE - byte)
	cmp	di, PLANE_SIZE
	jl	short @@BYTEALIGNED_more?
	sub	di, PLANE_SIZE

@@BYTEALIGNED_more?:
	loop	@@BYTEALIGNED
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@YLOOP:
	mov	al, [si]
	mov	ah, al
	mov	@@cx_tmp, cx
	mov	cl, @@first_byte_shr
	shr	al, cl
	mov	cl, @@second_byte_shl
	shl	ah, cl
	mov	cx, @@cx_tmp
	mov	es:[di], ax
	add	di, ROW_SIZE
	cmp	di, PLANE_SIZE
	jl	short @@YLOOP_more?
	sub	di, PLANE_SIZE

@@YLOOP_more?:
	inc	si
	loop	@@YLOOP

@@ret:
	pop	di
	pop	si
	leave
	retn	6
pointnum_put	endp
