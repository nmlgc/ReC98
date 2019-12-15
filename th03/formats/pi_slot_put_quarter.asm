proc_defconv pi_slot_put_quarter
	arg @@x:word, @@y:word, @@slot:word, @@quarter:word
	local @@row_num:word, @@row_buf:dword

	push	si
	push	di
	mov	si, @@y
	mov	di, @@quarter
	mov	bx, @@slot
	shl	bx, 2
	mov	ax, word ptr (_pi_slot_buffers+2)[bx]
	mov	dx, word ptr _pi_slot_buffers[bx]
	mov	word ptr @@row_buf+2, ax
	mov	word ptr @@row_buf, dx
	cmp	di, 1
	jnz	short @@bottom_left?
	add	word ptr @@row_buf, (320 / 2)
	jmp	short @@first

@@bottom_left?:
	cmp	di, 2
	jnz	short @@bottom_right?
	add	word ptr @@row_buf, (640 * 200) / 2
	jmp	short @@first

@@bottom_right?:
	cmp	di, 3
	jnz	short @@first
	add	word ptr @@row_buf, ((640 * 200) + 320) / 2

@@first:
	mov	eax, @@row_buf
	shr	eax, 10h
	mov	dx, word ptr @@row_buf
	shr	dx, 4
	add	ax, dx
	mov	dx, word ptr @@row_buf
	and	dx, 0Fh
	mov	word ptr @@row_buf+2, ax
	mov	word ptr @@row_buf, dx
	mov	@@row_num, 0
	jmp	short @@check

@@put:
	call	graph_pack_put_8 pascal, @@x, si, @@row_buf, 320
	inc	si
	cmp	si, 400
	jl	short @@next_row
	sub	si, 400

@@next_row:
	add	word ptr @@row_buf, 320
	mov	eax, @@row_buf
	shr	eax, 10h
	mov	dx, word ptr @@row_buf
	shr	dx, 4
	add	ax, dx
	mov	dx, word ptr @@row_buf
	and	dx, 0Fh
	mov	word ptr @@row_buf+2, ax
	mov	word ptr @@row_buf, dx
	inc	@@row_num

@@check:
	cmp	@@row_num, 200
	jl	short @@put
	pop	di
	pop	si
	ret
endp_defconv
