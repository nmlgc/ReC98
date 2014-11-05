; void __cdecl setmem(void *addr, unsigned int len, char val)
public _setmem
_setmem		proc
@@addr		= dword	ptr  6
@@len		= word ptr  0Ah
@@val		= byte ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		LES_	di, [bp+@@addr]
		mov	cx, [bp+@@len]
		mov	al, [bp+@@val]
		mov	ah, al
		cld
		test	di, 1
		jz	short @@isAligned
		jcxz	short @@done
		stosb
		dec	cx

@@isAligned:
		shr	cx, 1
		rep stosw
		jnb	short @@noOdd
		stosb

@@noOdd:
@@done:
		pop	di
		pop	si
		pop	bp
		ret
_setmem		endp

; void *__cdecl	memset(void *src, int c, size_t n)
public _memset
_memset		proc
@@src		= dword	ptr  6
@@c		= byte ptr  0Ah
@@n		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@c]
		push	[bp+@@n]
		push	word ptr [bp+@@src+2]
		push	word ptr [bp+@@src]
		call	_setmem
		add	sp, 8
		mov	dx, word ptr [bp+@@src+2]
		mov	ax, word ptr [bp+@@src]
		pop	di
		pop	si
		pop	bp
		ret
_memset		endp
