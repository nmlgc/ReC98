; unsigned int __cdecl _dos_getfileattr(const char *filename, unsigned int *attrib)
__dos_getfileattr proc DIST
@@filename	= DPTR_ 2 + dPtrSize
@@attrib	= DPTR_ 2 + (dPtrSize * 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		pushDS_
		mov	ah, 43h
		xor	al, al
		LDS_	dx, [bp+@@filename]
		int	21h
		popDS_
		jb	short @@_getFailed
		LES_	bx, [bp+@@attrib]
		mov	ES_[bx], cx
		xor	ax, ax
		jmp	short @@ret

@@_getFailed:
		push	ax
		call	__DOSERROR

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
__dos_getfileattr endp

; unsigned int __cdecl _dos_setfileattr(const char *filename, unsigned int attrib)
__dos_setfileattr proc DIST
@@filename	= DPTR_ 2 + dPtrSize
@@attrib	= DPTR_ 2 + (dPtrSize * 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		pushDS_
		mov	ah, 43h
		mov	al, 1
		LDS_	dx, [bp+@@filename]
		mov	cx, word ptr [bp+@@attrib]
		int	21h
		popDS_
		jb	short @@_setFailed
		xor	ax, ax
		jmp	short @@ret

@@_setFailed:
		push	ax
		call	__DOSERROR

@@ret:
		pop	di
		pop	si
		pop	bp
		ret
__dos_setfileattr endp
