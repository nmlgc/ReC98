; char *_stpcpy(char *to, const char *from)
public _stpcpy
_stpcpy		proc DIST

@@len		= word ptr -2
@@to		= dword	ptr  6
@@from		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		push	word ptr [bp+@@from+2]
		push	word ptr [bp+@@from]	; s
		nop
		call	_strlen
		pop	cx
		pop	cx
		mov	[bp+@@len], ax
		inc	ax
		push	ax		; n
		push	word ptr [bp+@@from+2]
		push	word ptr [bp+@@from]	; src
		push	word ptr [bp+@@to+2]
		push	word ptr [bp+@@to] ; dest
		nop
		call	_memcpy
		add	sp, 0Ah
		mov	dx, word ptr [bp+@@to+2]
		mov	ax, word ptr [bp+@@to]
		add	ax, [bp+@@len]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_stpcpy		endp
