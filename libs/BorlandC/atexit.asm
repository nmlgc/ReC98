MAX_ATEXIT	equ 32

; int atexit(atexit_t func)
public _atexit
_atexit		proc

_func		= DPTR_  2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	_atexitcnt, 20h	; ' '
		jnz	short @@_atexit_do
		mov	ax, 1
		jmp	short @@_atexit_ret
; ---------------------------------------------------------------------------

@@_atexit_do:
		mov	bx, _atexitcnt
if LDATA
		mov	cl, 2
		shl	bx, cl
		mov	dx, word ptr [bp+_func+2]
		mov	ax, word ptr [bp+_func]
		mov	word ptr _atexittbl+2[bx], dx
else
		add	bx, bx
		mov	ax, word ptr [bp+_func]
endif
		mov	word ptr _atexittbl[bx], ax
		inc	_atexitcnt
		xor	ax, ax

@@_atexit_ret:
		pop	di
		pop	si
		pop	bp
		ret
_atexit		endp
