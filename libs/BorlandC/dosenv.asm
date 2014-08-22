; char* pascal near __DOSenv(char **envV, char *pathP, void **envSave)
public __DOSENV
__DOSENV	proc near

@@bufP		= dword	ptr -0Ah
@@envS		= word ptr -6
@@envW		= dword	ptr -4
@@envSave		= dword	ptr  4
@@pathP		= dword	ptr  8
@@envV		= dword	ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		push	di
		mov	[bp+@@envS], 1
		mov	dx, word ptr [bp+@@envV+2]
		mov	ax, word ptr [bp+@@envV]
		mov	word ptr [bp+@@envW+2], dx
		mov	word ptr [bp+@@envW], ax
		or	ax, dx
		jz	short @@DOSENV_got_size
		mov	[bp+@@envS], 0
		jmp	short @@DOSENV_compute_loop

@@DOSENV_compute_size:
		les	bx, [bp+@@envW]
		add	word ptr [bp+@@envW], 4
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		nopcall	_strlen
		pop	cx
		pop	cx
		inc	ax
		add	[bp+@@envS], ax

@@DOSENV_compute_loop:
		les	bx, [bp+@@envW]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jz	short @@DOSENV_got_size
		les	bx, es:[bx]
		cmp	byte ptr es:[bx], 0
		jnz	short @@DOSENV_compute_size

@@DOSENV_got_size:
		inc	[bp+@@envS]
		mov	ax, word ptr [bp+@@pathP]
		or	ax, word ptr [bp+@@pathP+2]
		jz	short @@DOSENV_size_check
		push	word ptr [bp+@@pathP+2]
		push	word ptr [bp+@@pathP]
		nopcall	_strlen
		pop	cx
		pop	cx
		add	ax, 3
		add	[bp+@@envS], ax

@@DOSENV_size_check:
		cmp	[bp+@@envS], 8000h
		jb	short @@DOSENV_alloc
		jmp	@@DOSENV_ret_0

@@DOSENV_alloc:
		mov	ax, [bp+@@envS]
		add	ax, 0Fh
		push	ax
		nopcall	_malloc
		pop	cx
		mov	word ptr [bp+@@bufP+2], dx
		mov	word ptr [bp+@@bufP], ax
		or	ax, dx
		jnz	short @@DOSENV_align
		jmp	@@DOSENV_ret_0

@@DOSENV_align:
		les	bx, [bp+@@envSave]
		mov	ax, word ptr [bp+@@bufP]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		add	word ptr [bp+@@bufP], 0Fh
		and	word ptr [bp+@@bufP], 0FFF0h
		mov	dx, word ptr [bp+@@envV+2]
		mov	ax, word ptr [bp+@@envV]
		mov	word ptr [bp+@@envW+2], dx
		mov	word ptr [bp+@@envW], ax
		or	ax, dx
		jz	short @@DOSENV_append_check
		les	bx, [bp+@@envW]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jz	short @@DOSENV_append_check
		jmp	short @@DOSENV_concat_loop

@@DOSENV_concat:
		les	bx, [bp+@@envW]
		add	word ptr [bp+@@envW], 4
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		push	word ptr [bp+@@bufP+2]
		push	word ptr [bp+@@bufP]
		nopcall	_stpcpy
		add	sp, 8
		mov	word ptr [bp+@@bufP+2], dx
		mov	word ptr [bp+@@bufP], ax
		les	bx, [bp+@@bufP]
		mov	byte ptr es:[bx], 0
		inc	word ptr [bp+@@bufP]

@@DOSENV_concat_loop:
		les	bx, [bp+@@envW]
		mov	ax, es:[bx]
		or	ax, es:[bx+2]
		jz	short @@DOSENV_append
		les	bx, es:[bx]
		cmp	byte ptr es:[bx], 0
		jnz	short @@DOSENV_concat
		jmp	short @@DOSENV_append

@@DOSENV_append_check:
		les	bx, [bp+@@bufP]
		mov	byte ptr es:[bx], 0
		inc	word ptr [bp+@@bufP]

@@DOSENV_append:
		les	bx, [bp+@@bufP]
		mov	byte ptr es:[bx], 0
		inc	word ptr [bp+@@bufP]
		mov	ax, word ptr [bp+@@pathP]
		or	ax, word ptr [bp+@@pathP+2]
		jz	short @@DOSENV_ret_buf
		les	bx, [bp+@@bufP]
		mov	word ptr es:[bx], 1
		add	word ptr [bp+@@bufP], 2
		push	word ptr [bp+@@pathP+2]
		push	word ptr [bp+@@pathP]
		push	word ptr [bp+@@bufP+2]
		push	word ptr [bp+@@bufP]
		nopcall	_stpcpy
		add	sp, 8
		mov	word ptr [bp+@@bufP+2], dx
		mov	word ptr [bp+@@bufP], ax
		les	bx, [bp+@@bufP]
		mov	byte ptr es:[bx], 0
		inc	word ptr [bp+@@bufP]

@@DOSENV_ret_buf:
		mov	dx, word ptr [bp+@@bufP+2]
		mov	ax, word ptr [bp+@@bufP]
		sub	ax, [bp+@@envS]
		jmp	short @@DOSENV_ret

@@DOSENV_ret_0:
		xor	dx, dx
		xor	ax, ax

@@DOSENV_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	0Ch
__DOSENV	endp
