; static void interrupt Int0Catcher(unsigned bp)
Int0Catcher	proc far
@@action		= DPTR_ -(0 + dPtrSize)

		push	ax
		push	bx
		push	cx
		push	dx
		push	es
		push	ds
		push	si
		push	di
		push	bp
		mov	bp, seg	dseg
		mov	ds, bp
		mov	bp, sp
		sub	sp, 4
		mov	dx, word ptr Dispatch+(2*4)+2
		mov	ax, word ptr Dispatch+(2*4)
		mov	word ptr [bp+@@action+2], dx
		mov	word ptr [bp+@@action], ax
		or	dx, dx
		jnz	short @@Int0Catcher_check_sigerr
		cmp	ax, 1
		jz	short @@Int0Catcher_ret

@@Int0Catcher_check_sigerr:
		mov	ax, word ptr [bp+@@action]
		or	ax, word ptr [bp+@@action+2]
		jz	short @@Int0Catcher_exit
		cmp	word ptr [bp+@@action+2], 0FFFFh
		jnz	short @@Int0Catcher_call
		cmp	word ptr [bp+@@action], 0FFFFh
		jnz	short @@Int0Catcher_call

@@Int0Catcher_exit:
		mov	ax, 1
		push	ax
		nop
		call	__exit
		pop	cx

@@Int0Catcher_call:
		mov	word ptr Dispatch+(2*4)+2, 0
		mov	word ptr Dispatch+(2*4), 0
		push	ss
		lea	ax, [bp+0]
		push	ax
		mov	ax, 7Fh
		push	ax
		mov	ax, 8
		push	ax
		call	[bp+@@action]
		add	sp, 8

@@Int0Catcher_ret:
		mov	sp, bp
		pop	bp
		pop	di
		pop	si
		pop	ds
		pop	es
		pop	dx
		pop	cx
		pop	bx
		pop	ax
		iret
Int0Catcher	endp

; static void interrupt Int4Catcher(unsigned bp)
Int4Catcher	proc far
@@action		= DPTR_ -(0 + dPtrSize)

		push	ax
		push	bx
		push	cx
		push	dx
		push	es
		push	ds
		push	si
		push	di
		push	bp
		mov	bp, seg	dseg
		mov	ds, bp
		mov	bp, sp
		sub	sp, 4
		mov	dx, word ptr Dispatch+(2*4)+2
		mov	ax, word ptr Dispatch+(2*4)
		mov	word ptr [bp+@@action+2], dx
		mov	word ptr [bp+@@action], ax
		or	dx, dx
		jnz	short @@Int4Catcher_check_sigerr
		cmp	ax, 1
		jz	short @@Int4Catcher_ret

@@Int4Catcher_check_sigerr:
		mov	ax, word ptr [bp+@@action]
		or	ax, word ptr [bp+@@action+2]
		jz	short @@Int4Catcher_exit
		cmp	word ptr [bp+@@action+2], 0FFFFh
		jnz	short @@Int4Catcher_call
		cmp	word ptr [bp+@@action], 0FFFFh
		jnz	short @@Int4Catcher_call

@@Int4Catcher_exit:
		mov	ax, 1
		push	ax
		nop
		call	__exit
		pop	cx

@@Int4Catcher_call:
		mov	word ptr Dispatch+(2*4)+2, 0
		mov	word ptr Dispatch+(2*4), 0
		push	ss
		lea	ax, [bp+0]
		push	ax
		mov	ax, 7Eh
		push	ax
		mov	ax, 8
		push	ax
		call	[bp+@@action]
		add	sp, 8

@@Int4Catcher_ret:
		mov	sp, bp
		pop	bp
		pop	di
		pop	si
		pop	ds
		pop	es
		pop	dx
		pop	cx
		pop	bx
		pop	ax
		iret
Int4Catcher	endp

; static void interrupt Int23Catcher()
Int23Catcher	proc far
@@action		= DPTR_ -(0 + dPtrSize)

		push	ax
		push	cx
		push	dx
		push	bx
		push	sp
		push	bp
		push	si
		push	di
		push	ds
		push	es
		mov	bp, seg	dseg
		mov	ds, bp
		mov	bp, sp
		sub	sp, 4
		pushf
		mov	dx, word ptr Dispatch+2
		mov	ax, word ptr Dispatch
		mov	word ptr [bp+@@action+2], dx
		mov	word ptr [bp+@@action], ax
		or	dx, dx
		jnz	short @@Int23Catcher_check_sigerr
		cmp	ax, 1
		jz	short @@Int23Catcher_ret

@@Int23Catcher_check_sigerr:
		mov	ax, word ptr [bp+@@action]
		or	ax, word ptr [bp+@@action+2]
		jz	short @@Int23Catcher_exit
		cmp	word ptr [bp+@@action+2], 0FFFFh
		jnz	short @@Int23Catcher_call
		cmp	word ptr [bp+@@action], 0FFFFh
		jnz	short @@Int23Catcher_call

@@Int23Catcher_exit:
		mov	ax, 1
		push	ax
		nop
		call	__exit
		pop	cx

@@Int23Catcher_call:
		mov	word ptr Dispatch+2, 0
		mov	word ptr Dispatch, 0
		push	word ptr OldInt23+2
		push	word ptr OldInt23
		mov	ax, 23h
		push	ax
		nop
		call	_setvect
		mov	ax, 2
		push	ax
		call	[bp+@@action]
		add	sp, 8

@@Int23Catcher_ret:
		popf
		clc
		mov	sp, bp
		pop	es
		pop	ds
		pop	di
		pop	si
		pop	bp
		pop	bx
		pop	bx
		pop	dx
		pop	cx
		pop	ax
		retf
Int23Catcher	endp

; static int GetIndex(int SigType)
GetIndex	proc DIST
SigType		= word ptr 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	dx, dx

@@GetIndex_loop:
		mov	bx, dx
		mov	al, IxGen[bx]
		mov	ah, 0
		cmp	ax, [bp+SigType]
		jnz	short @@GetIndex_check
		mov	ax, dx
		jmp	short @@GetIndex_ret

@@GetIndex_check:
		inc	dx
		cmp	dx, 6
		jl	short @@GetIndex_loop
		mov	ax, 0FFFFh

@@GetIndex_ret:
		pop	di
		pop	si
		pop	bp
		ret
GetIndex	endp

; CatcherPTR __cdecl signal(int sig, CatcherPTR *New)
signal		proc DIST
@@OldVar		= dword	ptr -6
@@Index		= word ptr -2
@@sig		= word ptr  6
@@New		= dword	ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		cmp	SignalPtrSet, 0
		jnz	short @@signal_index_check
		mov	word ptr __SignalPtr+2,	seg signal
		mov	word ptr __SignalPtr, offset signal
		mov	SignalPtrSet, 1

@@signal_index_check:
		push	[bp+@@sig]
		call	GetIndex
		pop	cx
		mov	[bp+@@Index], ax
		cmp	ax, 0FFFFh
		jnz	short @@signal_install
		mov	_errno, 13h
		mov	dx, 0FFFFh
		mov	ax, 0FFFFh
		jmp	@@signal_ret

@@signal_install:
		mov	bx, [bp+@@Index]
		mov	cl, 2
		shl	bx, cl
		mov	dx, word ptr (Dispatch+2)[bx]
		mov	ax, word ptr Dispatch[bx]
		mov	word ptr [bp+@@OldVar+2],	dx
		mov	word ptr [bp+@@OldVar], ax
		mov	bx, [bp+@@Index]
		shl	bx, cl
		mov	dx, word ptr [bp+@@New+2]
		mov	ax, word ptr [bp+@@New]
		mov	word ptr (Dispatch+2)[bx], dx
		mov	word ptr Dispatch[bx], ax
		cmp	[bp+@@sig], 2
		jnz	short @@signal_SIGFPE
		cmp	GotInt23, 0
		jnz	short @@signal_new_check
		mov	ax, 23h
		push	ax
		nop
		call	_getvect
		pop	cx
		mov	word ptr OldInt23+2, dx
		mov	word ptr OldInt23, ax
		mov	GotInt23, 1

@@signal_new_check:
		mov	ax, word ptr [bp+@@New]
		or	ax, word ptr [bp+@@New+2]
		jnz	short @@signal_Int23Catcher
		push	word ptr OldInt23+2
		push	word ptr OldInt23
		jmp	short @@signal_int23

@@signal_Int23Catcher:
		mov	ax, seg	Int23Catcher
		push	ax
		mov	ax, offset Int23Catcher
		push	ax

@@signal_int23:
		mov	ax, 23h
		jmp	short @@signal_last_vector

@@signal_SIGFPE:
		cmp	[bp+@@sig], 8
		jnz	short @@signal_ret_oldvar
		mov	ax, seg	Int0Catcher
		push	ax
		mov	ax, offset Int0Catcher
		push	ax
		xor	ax, ax
		push	ax
		nop
		call	_setvect
		add	sp, 6
		mov	ax, seg	Int4Catcher
		push	ax
		mov	ax, offset Int4Catcher
		push	ax
		mov	ax, 4

@@signal_last_vector:
		push	ax
		nop
		call	_setvect
		add	sp, 6

@@signal_ret_oldvar:
		mov	dx, word ptr [bp+@@OldVar+2]
		mov	ax, word ptr [bp+@@OldVar]

@@signal_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
signal		endp

; int raise(int SigType)
raise	proc DIST
@@action		= dword	ptr -6
@@Index		= word ptr -2
@@SigType		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		push	[bp+@@SigType]
		call	GetIndex
		pop	cx
		mov	[bp+@@Index], ax
		cmp	ax, 0FFFFh
		jnz	short @@raise_check_ignore
		mov	ax, 1
		jmp	short @@raise_ret

@@raise_check_ignore:
		mov	bx, [bp+@@Index]
		mov	cl, 2
		shl	bx, cl
		mov	dx, word ptr (Dispatch+2)[bx]
		mov	ax, word ptr Dispatch[bx]
		mov	word ptr [bp+@@action+2],	dx
		mov	word ptr [bp+@@action], ax
		or	dx, dx
		jnz	short @@raise_check_type
		cmp	ax, 1
		jz	short @@raise_ret_0

@@raise_check_type:
		mov	ax, word ptr [bp+@@action]
		or	ax, word ptr [bp+@@action+2]
		jnz	short @@raise_user
		mov	ax, [bp+@@SigType]
		cmp	ax, 2
		jz	short @@raise_SIGINT
		cmp	ax, 16h
		jnz	short @@raise_default
		nop
		call	__abort

@@raise_SIGINT:
		xor	ax, ax
		int	23h
		mov	ax, 4C03h
		int	21h

@@raise_default:
		mov	ax, 1
		push	ax
		nop
		call	__exit
		pop	cx
		jmp	short @@raise_ret_0

@@raise_user:
		mov	bx, [bp+@@Index]
		mov	cl, 2
		shl	bx, cl
		mov	word ptr (Dispatch+2)[bx], 0
		mov	word ptr Dispatch[bx], 0
		mov	bx, [bp+@@Index]
		mov	al, ExplicitVal[bx]
		mov	ah, 0
		push	ax
		push	[bp+@@SigType]
		call	[bp+@@action]
		pop	cx
		pop	cx

@@raise_ret_0:
		xor	ax, ax

@@raise_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
raise	endp
