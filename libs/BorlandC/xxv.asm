; terminate(void)
		public @terminate$qv
@terminate$qv	proc far
		push	si
		push	di
		nopcall	_abort
		pop	di
		pop	si
		retf
@terminate$qv	endp


; set_terminate(void (*)(void))
		public @set_terminate$qnqv$v
@set_terminate$qnqv$v proc far

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+0Ch]
		mov	ax, es:[bx+0Ah]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short xxv_10060
		les	bx, ss:16h
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	es:[bx+0Ch], dx
		mov	es:[bx+0Ah], ax

xxv_10060:
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@set_terminate$qnqv$v endp

xxv_1006C	dd 0
		dd xxv_100FA
		db 10h dup(0)
xxv_10084	dd 0
		dw 0FFE2h
		dw 0
		dw 3
		dd xxv_1006C
		dw 0
		db 4, 0

		public ___call_terminate
___call_terminate proc far

@@var_26		= dword	ptr -26h
@@var_22		= word ptr -22h
@@var_20		= word ptr -20h
@@var_1E		= word ptr -1Eh
@@var_12		= word ptr -12h

		push	bp
		mov	bp, sp
		sub	sp, 26h
		push	si
		push	di
		mov	ax, seg	xxv_10084
		mov	bx, offset xxv_10084
		nopcall	___InitExceptBlocks
		mov	[bp+@@var_22], ds
		nopcall	_flushall
		les	bx, ss:16h
		mov	dx, es:[bx+0Ch]
		mov	ax, es:[bx+0Ah]
		mov	word ptr [bp+@@var_26+2],	dx
		mov	word ptr [bp+@@var_26], ax
		mov	[bp+@@var_12], 6
		les	bx, ss:16h
		cmp	word ptr es:[bx+12h], 0
		jnz	short xxv_100DE
		les	bx, ss:16h
		mov	word ptr es:[bx+12h], ds

xxv_100DE:
		les	bx, ss:16h
		mov	ax, es:[bx+12h]
		mov	[bp+@@var_20], ax
		mov	ds, [bp+@@var_20]
		call	[bp+@@var_26]
		mov	ds, [bp+@@var_22]
		mov	[bp+@@var_12], 0
		jmp	short xxv_10102

xxv_100FA:
		mov	ds, [bp+@@var_22]
		nopcall	@_CatchCleanup$qv ; _CatchCleanup(void)

xxv_10102:
		nopcall	_abort
		push	[bp+@@var_1E]
		nopcall	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
___call_terminate endp


; unexpected(void)
		public @unexpected$qv
@unexpected$qv	proc far
		push	si
		push	di
		call	___call_terminate
		pop	di
		pop	si
		retf
@unexpected$qv	endp


; set_unexpected(void (*)(void))
		public @set_unexpected$qnqv$v
@set_unexpected$qnqv$v proc far

@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+10h]
		mov	ax, es:[bx+0Eh]
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+@@arg_2]
		jz	short xxv_10154
		les	bx, ss:16h
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	es:[bx+10h], dx
		mov	es:[bx+0Eh], ax

xxv_10154:
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@set_unexpected$qnqv$v endp


		public ___call_unexpected
___call_unexpected proc	far

@@var_6		= dword	ptr -6
@@var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		les	bx, ss:16h
		mov	dx, es:[bx+10h]
		mov	ax, es:[bx+0Eh]
		mov	word ptr [bp+@@var_6+2], dx
		mov	word ptr [bp+@@var_6], ax
		les	bx, ss:16h
		cmp	word ptr es:[bx+14h], 0
		jnz	short xxv_10190
		les	bx, ss:16h
		mov	word ptr es:[bx+14h], ds

xxv_10190:
		les	bx, ss:16h
		mov	ax, es:[bx+14h]
		mov	[bp+@@var_2], ax
		push	ds
		mov	ds, [bp+@@var_2]
		call	[bp+@@var_6]
		pop	ds
		nopcall	_abort
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
___call_unexpected endp


; __GetPolymorphicDTC(void *, unsigned int)
		public @__GetPolymorphicDTC$qnvui
@__GetPolymorphicDTC$qnvui proc	far

@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short xxv_101C3
		xor	ax, ax
		jmp	short xxv_101FD

xxv_101C3:
		les	bx, [bp+@@arg_0]
		add	bx, [bp+@@arg_4]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_4+2], ds
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		sub	ax, es:[bx-2]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx-6]
		mov	ax, es:[bx-8]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		mov	ax, es:[bx+1Ah]

xxv_101FD:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@__GetPolymorphicDTC$qnvui endp


; __GetPolymorphicDTCfar(void *, unsigned int)
		public @__GetPolymorphicDTCfar$qnvui
@__GetPolymorphicDTCfar$qnvui proc far

@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short xxv_10217
		xor	ax, ax
		jmp	short xxv_10255

xxv_10217:
		les	bx, [bp+@@arg_0]
		add	bx, [bp+@@arg_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		sub	ax, es:[bx-2]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		les	bx, [bp+@@var_4]
		mov	dx, es:[bx-6]
		mov	ax, es:[bx-8]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		les	bx, [bp+@@var_8]
		mov	ax, es:[bx+1Ah]

xxv_10255:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@__GetPolymorphicDTCfar$qnvui endp


		public __ExceptInit
__ExceptInit	proc far
		push	si
		push	di
		mov	word ptr ss:12h, 0
		mov	word ptr ss:10h, 0
		mov	word ptr ss:18h, ds
		mov	word ptr ss:16h, offset	___CPPexceptionList
		mov	word ptr ss:1Ah, 0FEEDh
		mov	ax, ds
		mov	ds:___unexpectd_DS, ax
		mov	ds:___terminate_DS, ax
		mov	dx, ss:18h
		mov	ax, ss:16h
		add	ax, 0A8h ; '¨'
		les	bx, ss:16h
		mov	es:[bx+22h], dx
		mov	es:[bx+20h], ax
		mov	word ptr ss:14h, 0FFFFh
		pop	di
		pop	si
		retf
__ExceptInit	endp
