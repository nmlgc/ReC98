; void near cdecl _fperror(void)
fperror	proc near
@@func		= dword	ptr -8
@@a		= dword	ptr -4

		push	bp
		mov	bp, sp
		sub	sp, 8
		mov	word ptr [bp+@@a+2], ss
		mov	word ptr [bp+@@a], bx
		mov	ax, word ptr __SignalPtr
		or	ax, word ptr __SignalPtr+2
		jz	short @@default_actions
		xor	ax, ax
		push	ax
		push	ax
		mov	ax, 8
		push	ax
		call	__SignalPtr
		add	sp, 6
		mov	word ptr [bp+@@func+2], dx
		mov	word ptr [bp+@@func], ax
		push	dx
		push	ax
		mov	ax, 8
		push	ax
		call	__SignalPtr
		add	sp, 6
		cmp	word ptr [bp+@@func+2], 0
		jnz	short @@user_actions
		cmp	word ptr [bp+@@func], 1
		jz	short @@fperror_ret

@@user_actions:
		mov	ax, word ptr [bp+@@func]
		or	ax, word ptr [bp+@@func+2]
		jz	short @@default_actions
		xor	ax, ax
		push	ax
		push	ax
		mov	ax, 8
		push	ax
		call	__SignalPtr
		les	bx, [bp+@@a]
		mov	ax, 6
		imul	word ptr es:[bx]
		mov	bx, ax
		push	word ptr (fp_errors - size f_errors)[bx]
		mov	ax, 8
		push	ax
		call	[bp+@@func]
		add	sp, 0Ah
		mov	sp, bp
		pop	bp
		retn

@@default_actions:
		les	bx, [bp+@@a]
		mov	ax, 6
		imul	word ptr es:[bx]
		mov	dx, offset (fp_errors - size f_errors)
		add	dx, 2
		add	ax, dx
		mov	bx, ax
		push	word ptr [bx+2]
		push	word ptr [bx]
		push	ds
		mov	ax, offset aFloatingPointE
		push	ax
		push	ds
		mov	ax, offset stderr
		push	ax
		nop
		call	_fprintf
		add	sp, 0Ch
		nop
		call	_abort

@@fperror_ret:
		mov	sp, bp
		pop	bp
		retn
fperror	endp
