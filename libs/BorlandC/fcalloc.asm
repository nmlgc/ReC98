ife LDATA
; void __pascal __near _lsetmem(char far *p, unsigned int n, unsigned __int8 val)
_lsetmem	proc
@@val		= byte ptr (cPtrSize + 2)
@@n		= word ptr (cPtrSize + 4)
@@p		= dword ptr (cPtrSize + 6)

		push	bp
		mov	bp, sp
		push	si
		push	di
		cld
		les	di, [bp+@@p]
		mov	cx, [bp+@@n]
		mov	al, [bp+@@val]
		rep	stosb
		pop	di
		pop	si
		pop	bp
		ret	8
_lsetmem	endp
endif

; void far *__cdecl farcalloc(unsigned __int32 nunits, unsigned __int32 unitsz)
_farcalloc	proc
@@sval		= word ptr -0Ah
@@scp		= dword	ptr -8
@@cp		= dword	ptr -4
@@nunits	= dword	ptr (cPtrSize + 2)
@@unitsz	= dword	ptr (cPtrSize + 6)

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		push	di
		mov	cx, word ptr [bp+@@unitsz+2]
		mov	bx, word ptr [bp+@@unitsz]
		mov	dx, word ptr [bp+@@nunits+2]
		mov	ax, word ptr [bp+@@nunits]
		call	N_LXMUL@
		mov	word ptr [bp+@@nunits+2], dx
		mov	word ptr [bp+@@nunits],	ax
		push	dx
		push	ax
		nopcall	_farmalloc
		pop	cx
		pop	cx
		mov	word ptr [bp+@@cp+2], dx
		mov	word ptr [bp+@@cp], ax
		or	ax, dx
		jz	short @@ret
		mov	ax, word ptr [bp+@@cp]
		mov	word ptr [bp+@@scp+2], dx
		mov	word ptr [bp+@@scp], ax
		jmp	short @@nunitsLeft?

@@loop:
		cmp	word ptr [bp+@@nunits+2], 0
		jb	short @@nunitsTake
		ja	short @@nunitsClamp
		cmp	word ptr [bp+@@nunits],	64000
		jbe	short @@nunitsTake

@@nunitsClamp:
		mov	ax, 64000
		jmp	short @@setmem

@@nunitsTake:
		mov	ax, word ptr [bp+@@nunits]

@@setmem:
		mov	[bp+@@sval], ax
ife LDATA
		push	word ptr [bp+@@scp+2]
		push	word ptr [bp+@@scp]
		push	ax
endif
		mov	al, 0
		push	ax
if LDATA
		push	[bp+@@sval]
		push	word ptr [bp+@@scp+2]
		push	word ptr [bp+@@scp]
		nopcall	_setmem
		add	sp, 8
else
		call	_lsetmem
endif
		mov	bx, [bp+@@sval]
		xor	cx, cx
		mov	dx, ss
		lea	ax, [bp+@@scp]
		call	N_PADA@
		mov	ax, [bp+@@sval]
		sub	word ptr [bp+@@nunits],	ax
		sbb	word ptr [bp+@@nunits+2], 0

@@nunitsLeft?:
		mov	ax, word ptr [bp+@@nunits]
		or	ax, word ptr [bp+@@nunits+2]
		jnz	short @@loop

@@ret:
		mov	dx, word ptr [bp+@@cp+2]
		mov	ax, word ptr [bp+@@cp]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_farcalloc	endp
