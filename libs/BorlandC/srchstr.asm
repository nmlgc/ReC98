; void __cdecl _searchstr(const	char *file, const char *ipath, char *pathname)
		public __searchstr
__searchstr	proc
@@temp		= dword	ptr -4
@@file		= dword	ptr  6
@@ipath		= dword	ptr  0Ah
@@pathname	= dword	ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	ax, 80
		push	ax
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		xor	ax, ax
		push	ax
		nopcall	__getdcwd
		add	sp, 8
		or	ax, dx
		jnz	short @@loc_10045
		xor	dx, dx
		jmp	short @@loc_10054

@@loc_10045:
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		nopcall	_strlen
		pop	cx
		pop	cx
		mov	dx, ax

@@loc_10054:
		les	bx, [bp+@@pathname]
		add	bx, dx
		mov	byte ptr es:[bx], 0
		or	dx, dx
		jz	short @@loc_100A9
		mov	bx, dx
		add	bx, word ptr [bp+@@pathname]
		mov	bl, es:[bx-1]
		mov	al, bl
		cmp	al, '\'
		jz	short @@loc_1007A
		cmp	bl, '/'
		jz	short @@loc_1007A
		cmp	bl, ':'
		jnz	short @@loc_10096

@@loc_1007A:
		mov	ax, word ptr [bp+@@pathname]
		add	ax, dx
		dec	ax
		push	word ptr [bp+@@pathname+2]
		push	ax
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		nopcall	___path_issbcs
		add	sp, 8
		or	ax, ax
		jnz	short @@loc_100A9

@@loc_10096:
		push	ds
		mov	ax, offset srchstr_backslash
		push	ax
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		nopcall	_strcat
		add	sp, 8

@@loc_100A9:
		push	word ptr [bp+@@file+2]
		push	word ptr [bp+@@file]
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		nopcall	_strcat
		add	sp, 8
		xor	ax, ax
		push	ax
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		nopcall	__access
		add	sp, 6
		or	ax, ax
		jz	short @@loc_1011D
		les	bx, [bp+@@ipath]
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_100E4
		les	bx, [bp+@@pathname]
		mov	byte ptr es:[bx], 0
		jmp	short @@loc_1015C

@@loc_100E4:
		xor	dx, dx
		jmp	short @@loc_100FC

@@loc_100E8:
		les	bx, [bp+@@pathname]
		add	bx, dx
		push	es
		les	si, [bp+@@ipath]
		mov	al, es:[si]
		pop	es
		mov	es:[bx], al
		inc	word ptr [bp+@@ipath]
		inc	dx

@@loc_100FC:
		les	bx, [bp+@@ipath]
		cmp	byte ptr es:[bx], ';'
		jz	short @@loc_1010B
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_100E8

@@loc_1010B:
		les	bx, [bp+@@ipath]
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_10117
		jmp	@@loc_10054

@@loc_10117:
		inc	word ptr [bp+@@ipath]
		jmp	@@loc_10054

@@loc_1011D:
		mov	ax, 80
		push	ax
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		xor	ax, ax
		push	ax
		push	ax
		nopcall	__fullpath
		add	sp, 0Ah
		mov	word ptr [bp+@@temp+2],	dx
		mov	word ptr [bp+@@temp], ax
		or	ax, dx
		jz	short @@loc_1015C
		push	word ptr [bp+@@temp+2]
		push	word ptr [bp+@@temp]
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		nopcall	_strcpy
		push	word ptr [bp+@@temp+2]
		push	word ptr [bp+@@temp]
		nopcall	_free
		add	sp, 0Ch

@@loc_1015C:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__searchstr	endp
