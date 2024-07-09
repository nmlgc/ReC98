public @pointnum_put
@pointnum_put	proc near

@@top equ <ax>
@@left equ <dx>
@@num equ <cx>

	push	si
	push	di
	push	ax
	push	dx
	mov	si, @@left
	mov	bx, @@top
	sar	dx, 3
	shl	ax, 6
	add	dx, ax
	shr	ax, 2
	add	dx, ax
	mov	di, dx
	and	si, 7
	mov	ax, si
	shl	si, 4
	add	si, offset _sPOINTNUMS
	shl	@@num, 7
	add	si, @@num

	blit_dots16_empty2opt_emptyopt_roll	<bx>, POINTNUM_H

@@ret:
	pop	dx
	pop	ax
	add	dx, POINTNUM_W
	pop	di
	pop	si
	retn
@pointnum_put	endp
