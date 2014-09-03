; int __stdcall	_DOSCMD(int, int, char *s, int,	int)
__DOSCMD	proc near

@@dest		= dword	ptr -0Eh
@@var_A		= dword	ptr -0Ah
@@var_6		= dword	ptr -6
@@var_2		= word ptr -2
@@arg_0		= word ptr  4
@@arg_2		= word ptr  6
@@arg_4		= dword	ptr  8
@@arg_8		= word ptr  0Ch
@@arg_A		= word ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 0Eh
		push	si
		push	di
		mov	[bp+@@var_2], 3
		mov	ax, word ptr [bp+@@arg_4]
		or	ax, word ptr [bp+@@arg_4+2]
		jz	short @@L1
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		nopcall	_strlen
		pop	cx
		pop	cx
		add	ax, [bp+@@var_2]
		inc	ax
		mov	[bp+@@var_2], ax

@@L1:
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	word ptr [bp+@@var_6+2], dx
		mov	word ptr [bp+@@var_6], ax
		jmp	short @@L3

@@L2:
		les	bx, [bp+@@var_6]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		nopcall	_strlen
		pop	cx
		pop	cx
		add	ax, [bp+@@var_2]
		inc	ax
		mov	[bp+@@var_2], ax
		add	word ptr [bp+@@var_6], 4

@@L3:
		les	bx, [bp+@@var_6]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jnz	short @@L2
		push	[bp+@@var_2]
		nopcall	_malloc
		pop	cx
		mov	word ptr [bp+@@var_A+2], dx
		mov	word ptr [bp+@@var_A], ax
		or	ax, dx
		jnz	short @@L4
		xor	dx, dx
		xor	ax, ax
		jmp	@@ret

@@L4:
		mov	dx, word ptr [bp+@@var_A+2]
		mov	ax, word ptr [bp+@@var_A]
		inc	ax
		mov	word ptr [bp+@@dest+2], dx
		mov	word ptr [bp+@@dest], ax
		les	bx, [bp+@@dest]
		mov	byte ptr es:[bx], ' '
		inc	word ptr [bp+@@dest]
		mov	ax, word ptr [bp+@@arg_4]
		or	ax, word ptr [bp+@@arg_4+2]
		jz	short @@L5
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		push	word ptr [bp+@@dest+2]
		push	word ptr [bp+@@dest]
		nopcall	_stpcpy
		add	sp, 8
		mov	word ptr [bp+@@dest+2], dx
		mov	word ptr [bp+@@dest], ax
		les	bx, [bp+@@dest]
		mov	byte ptr es:[bx], ' '
		inc	word ptr [bp+@@dest]

@@L5:
		mov	ax, [bp+@@arg_8]
		or	ax, [bp+@@arg_A]
		jz	short @@L8
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	word ptr [bp+@@var_6+2], dx
		mov	word ptr [bp+@@var_6], ax
		jmp	short @@L7

@@L6:
		les	bx, [bp+@@var_6]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		push	word ptr [bp+@@dest+2]
		push	word ptr [bp+@@dest]
		nopcall	_stpcpy
		add	sp, 8
		mov	word ptr [bp+@@dest+2], dx
		mov	word ptr [bp+@@dest], ax
		les	bx, [bp+@@dest]
		mov	byte ptr es:[bx], ' '
		inc	word ptr [bp+@@dest]
		add	word ptr [bp+@@var_6], 4

@@L7:
		les	bx, [bp+@@var_6]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jnz	short @@L6

@@L8:
		les	bx, [bp+@@dest]
		mov	byte ptr es:[bx-1], 0Dh
		mov	byte ptr es:[bx], 0
		mov	ax, word ptr [bp+@@dest]
		xor	dx, dx
		sub	ax, word ptr [bp+@@var_A]
		sbb	dx, 0
		add	al, 0FEh
		les	bx, [bp+@@var_A]
		mov	es:[bx], al
		mov	dx, word ptr [bp+@@var_A+2]
		mov	ax, word ptr [bp+@@var_A]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	0Ch
__DOSCMD	endp
