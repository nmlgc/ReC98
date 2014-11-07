MARGIN	equ 512

; int near __brk(void *addr)
___brk		proc near

@@addr		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+@@addr]
		mov	dx, sp
		sub	dx, MARGIN
		cmp	ax, dx
		jnb	short @@brkerr
		mov	word ptr __brklvl@, ax
		xor	ax, ax
		jmp	short @@brkret
; ---------------------------------------------------------------------------

@@brkerr:
		mov	_errno, 8
		mov	ax, -1

@@brkret:
		pop	di
		pop	si
		pop	bp
		retn
___brk		endp

; void * near __sbrk(long incr)
___sbrk		proc near

incr		= dword ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+incr]
		mov	dx, word ptr [bp+incr+2]
		add	ax, word ptr __brklvl@
		adc	dx, 0
		mov	cx, ax
		or	dx, dx
		jnz	short @@sbrkErr
		add	cx, MARGIN
		jb	short @@sbrkErr
		cmp	cx, sp
		jnb	short @@sbrkErr
		xchg	ax, word ptr __brklvl@
		jmp	short @@sbrkRet
; ---------------------------------------------------------------------------

@@sbrkErr:
		mov	_errno, 8
		mov	ax, -1

@@sbrkRet:
		pop	di
		pop	si
		pop	bp
		retn
___sbrk		endp

; int brk(void *addr)
_brk		proc near

@@addr		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@addr]
		call	___brk
		pop	cx
		pop	di
		pop	si
		pop	bp
		retn
_brk		endp

; void *sbrk(int incr)
_sbrk		proc near

incr		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+incr]
		cwd
		push	dx
		push	ax
		call	___sbrk
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		retn
_sbrk		endp
