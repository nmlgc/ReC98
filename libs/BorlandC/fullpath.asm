isSlash		proc near
@@c		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@c]
		cmp	ax, '\'
		jz	short @@ret1
		cmp	ax, '/'
		jnz	short @@ret0

@@ret1:
		mov	ax, 1
		jmp	short @@ret

@@ret0:
		xor	ax, ax

@@ret:
		pop	di
		pop	si
		pop	bp
		retn	2
isSlash		endp


fullpath_1003F	proc near
@@arg_0		= dword	ptr  4
@@arg_4		= dword	ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		les	bx, [bp+@@arg_0]
		mov	al, es:[bx]
		mov	ah, 0
		push	ax
		call	isSlash
		or	ax, ax
		jz	short @@ret0
		push	word ptr [bp+@@arg_0+2]
		push	word ptr [bp+@@arg_0]
		push	word ptr [bp+@@arg_4+2]
		push	word ptr [bp+@@arg_4]
		nopcall	___path_issbcs
		add	sp, 8
		or	ax, ax
		jz	short @@ret0
		mov	ax, 1
		jmp	short @@ret

@@ret0:
		xor	ax, ax

@@ret:
		pop	di
		pop	si
		pop	bp
		retn	8
fullpath_1003F	endp


; int __cdecl __far _fullpath(char *buffer, int pathname, int maxlen)
		public __fullpath
__fullpath	proc DIST
@@drive		= word ptr -12h
@@driveletter	= word ptr -10h
@@c		= word ptr -0Eh
@@src		= dword	ptr -0Ch
@@dst		= dword	ptr -8
@@tempbuf	= dword	ptr -4
@@buffer	= dword	ptr  6
@@pathname	= dword	ptr  0Ah
@@maxlen	= dword	ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 12h
		push	si
		push	di
		mov	ax, 160+1
		push	ax
		nopcall	_malloc
		pop	cx
		mov	word ptr [bp+@@tempbuf+2], dx
		mov	word ptr [bp+@@tempbuf], ax
		or	ax, dx
		jnz	short @@loc_10098
		jmp	@@loc_102DB

@@loc_10098:
		mov	dx, word ptr [bp+@@pathname+2]
		mov	ax, word ptr [bp+@@pathname]
		mov	word ptr [bp+@@src+2], dx
		mov	word ptr [bp+@@src], ax
		les	bx, [bp+@@src]
		mov	al, es:[bx]
		cbw
		mov	bx, ax
		test	ds:(__ctype+1)[bx], 0Ch
		jz	short @@loc_100D8
		mov	bx, word ptr [bp+@@src]
		cmp	byte ptr es:[bx+1], ':'
		jnz	short @@loc_100D8
		mov	al, es:[bx]
		cbw
		mov	[bp+@@driveletter], ax
		push	ax
		nopcall	_toupper
		pop	cx
		add	ax, -64
		mov	[bp+@@drive], ax
		add	word ptr [bp+@@src], 2
		jmp	short @@loc_100EE

@@loc_100D8:
		push	ss
		lea	ax, [bp+@@drive]
		push	ax
		nopcall	__dos_getdrive
		pop	cx
		pop	cx
		mov	ax, [bp+@@drive]
		add	ax, 'A'
		dec	ax
		mov	[bp+@@driveletter], ax

@@loc_100EE:
		les	bx, [bp+@@src]
		mov	al, es:[bx]
		cbw
		push	ax
		call	isSlash
		or	ax, ax
		jnz	short @@loc_10156
		mov	ax, 160+1
		push	ax
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		push	[bp+@@drive]
		nopcall	__getdcwd
		add	sp, 8
		or	ax, dx
		jnz	short @@loc_10126
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_free
		pop	cx
		pop	cx
		jmp	@@loc_102DB

@@loc_10126:
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_strlen
		pop	cx
		pop	cx
		mov	dx, word ptr [bp+@@tempbuf+2]
		add	ax, word ptr [bp+@@tempbuf]
		mov	word ptr [bp+@@dst+2], dx
		mov	word ptr [bp+@@dst], ax
		push	dx
		push	word ptr [bp+@@tempbuf]
		dec	ax
		push	dx
		push	ax
		call	fullpath_1003F
		or	ax, ax
		jnz	short @@loc_10178
		les	bx, [bp+@@dst]
		mov	byte ptr es:[bx], '\'
		jmp	short @@loc_10175

@@loc_10156:
		mov	dx, word ptr [bp+@@tempbuf+2]
		mov	ax, word ptr [bp+@@tempbuf]
		mov	word ptr [bp+@@dst+2], dx
		mov	word ptr [bp+@@dst], ax
		les	bx, [bp+@@dst]
		mov	al, byte ptr [bp+@@driveletter]
		mov	es:[bx], al
		inc	word ptr [bp+@@dst]
		les	bx, [bp+@@dst]
		mov	byte ptr es:[bx], ':'

@@loc_10175:
		inc	word ptr [bp+@@dst]

@@loc_10178:
		push	word ptr [bp+@@src+2]
		push	word ptr [bp+@@src]
		push	word ptr [bp+@@dst+2]
		push	word ptr [bp+@@dst]
		nopcall	_strcpy
		add	sp, 8
		mov	dx, word ptr [bp+@@tempbuf+2]
		mov	ax, word ptr [bp+@@tempbuf]
		mov	word ptr [bp+@@dst+2], dx
		mov	word ptr [bp+@@dst], ax
		mov	word ptr [bp+@@src+2], dx
		mov	word ptr [bp+@@src], ax

@@loc_1019E:
		les	bx, [bp+@@src]
		inc	word ptr [bp+@@src]
		mov	al, es:[bx]
		cbw
		mov	[bp+@@c], ax
		or	ax, ax
		jz	short @@loc_101BA
		push	ax
		call	isSlash
		or	ax, ax
		jnz	short @@loc_101BA
		jmp	@@loc_102EC

@@loc_101BA:
		les	bx, [bp+@@dst]
		cmp	byte ptr es:[bx-1], '.'
		jnz	short @@loc_101E1
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		mov	ax, word ptr [bp+@@dst]
		add	ax, 0FFFEh
		push	word ptr [bp+@@dst+2]
		push	ax
		call	fullpath_1003F
		or	ax, ax
		jz	short @@loc_101E1
		sub	word ptr [bp+@@dst], 2
		jmp	short @@loc_10258

@@loc_101E1:
		les	bx, [bp+@@dst]
		cmp	byte ptr es:[bx-1], '.'
		jnz	short @@loc_10258
		cmp	byte ptr es:[bx-2], '.'
		jnz	short @@loc_10258
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		mov	ax, word ptr [bp+@@dst]
		add	ax, 0FFFDh
		push	word ptr [bp+@@dst+2]
		push	ax
		call	fullpath_1003F
		or	ax, ax
		jz	short @@loc_10258
		sub	word ptr [bp+@@dst], 3
		les	bx, [bp+@@dst]
		cmp	byte ptr es:[bx-1], ':'
		jnz	short @@loc_10241
		mov	ax, word ptr [bp+@@dst]
		dec	ax
		push	word ptr [bp+@@dst+2]
		push	ax
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	___path_issbcs
		add	sp, 8
		or	ax, ax
		jz	short @@loc_10241
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_free
		pop	cx
		pop	cx
		jmp	@@loc_102DB

@@loc_10241:
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		dec	word ptr [bp+@@dst]
		mov	ax, word ptr [bp+@@dst]
		push	word ptr [bp+@@dst+2]
		push	ax
		call	fullpath_1003F
		or	ax, ax
		jz	short @@loc_10241

@@loc_10258:
		cmp	[bp+@@c], 0
		jz	short @@loc_10261
		jmp	@@loc_102E1

@@loc_10261:
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		mov	ax, word ptr [bp+@@dst]
		dec	ax
		push	word ptr [bp+@@dst+2]
		push	ax
		call	fullpath_1003F
		or	ax, ax
		jz	short @@loc_10279
		dec	word ptr [bp+@@dst]

@@loc_10279:
		les	bx, [bp+@@dst]
		cmp	byte ptr es:[bx-1], ':'
		jnz	short @@loc_102A7
		mov	ax, word ptr [bp+@@dst]
		dec	ax
		push	word ptr [bp+@@dst+2]
		push	ax
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	___path_issbcs
		add	sp, 8
		or	ax, ax
		jz	short @@loc_102A7
		les	bx, [bp+@@dst]
		mov	byte ptr es:[bx], '\'
		inc	word ptr [bp+@@dst]

@@loc_102A7:
		les	bx, [bp+@@dst]
		mov	byte ptr es:[bx], 0
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_strlen
		pop	cx
		pop	cx
		inc	ax
		mov	dx, ax
		mov	ax, word ptr [bp+@@buffer]
		or	ax, word ptr [bp+@@buffer+2]
		jnz	short @@loc_102C9
		jmp	@@loc_1034D

@@loc_102C9:
		cmp	dx, word ptr [bp+@@maxlen]
		jbe	short @@loc_10326
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_free
		pop	cx
		pop	cx

@@loc_102DB:
		xor	dx, dx
		xor	ax, ax
		jmp	short @@loc_1035C

@@loc_102E1:
		les	bx, [bp+@@dst]
		mov	al, byte ptr [bp+@@c]
		mov	es:[bx], al
		jmp	short @@loc_10320

@@loc_102EC:
		les	bx, [bp+@@dst]
		mov	al, byte ptr [bp+@@c]
		mov	es:[bx], al
		inc	word ptr [bp+@@dst]
		push	[bp+@@c]
		nopcall	___path_isdbcsleadbyte
		pop	cx
		or	ax, ax
		jnz	short @@loc_10308
		jmp	@@loc_1019E

@@loc_10308:
		les	bx, [bp+@@src]
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_10314
		jmp	@@loc_1019E

@@loc_10314:
		mov	al, es:[bx]
		les	bx, [bp+@@dst]
		mov	es:[bx], al
		inc	word ptr [bp+@@src]

@@loc_10320:
		inc	word ptr [bp+@@dst]
		jmp	@@loc_1019E

@@loc_10326:
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		push	word ptr [bp+@@buffer+2]
		push	word ptr [bp+@@buffer]
		nopcall	_strcpy
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_free
		add	sp, 0Ch
		mov	dx, word ptr [bp+@@buffer+2]
		mov	ax, word ptr [bp+@@buffer]
		jmp	short @@loc_1035C

@@loc_1034D:
		push	dx
		push	word ptr [bp+@@tempbuf+2]
		push	word ptr [bp+@@tempbuf]
		nopcall	_realloc
		add	sp, 6

@@loc_1035C:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__fullpath	endp
