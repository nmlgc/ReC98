; int __cdecl __far _access(const char *filename, int amode)
__access	proc DIST
@@filename	= dword	ptr  6
@@amode		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@filename+2]
		push	word ptr [bp+@@filename]
		nopcall	__chmod
		add	sp, 6
		mov	dx, ax
		cmp	dx, 0FFFFh
		jnz	short @@check
		jmp	short @@ret

@@check:
		test	[bp+@@amode], 2
		jz	short @@ret0
		test	dl, 1
		jnz	short @@EACCES

@@ret0:
		xor	ax, ax
		jmp	short @@ret

@@EACCES:
		mov	_errno, 5
		mov	ax, -1

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
__access	endp
