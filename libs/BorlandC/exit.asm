; static void dummy(void)
public dummy
dummy	proc
		push	si
		push	di
		pop	di
		pop	si
		ret
dummy	endp

; static void pascal near ___exit(int quick, int dontexit, int errcode)
public ___exit
___exit	proc near

@@errcode		= word ptr  4
@@dontexit		= word ptr  6
@@quick		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	[bp+@@quick], 0
		jnz	short @@exit_part2
		jmp	short @@exit_slow
; ---------------------------------------------------------------------------

@@atexit_loop:
		dec	_atexitcnt
		mov	bx, _atexitcnt
if LDATA
		mov	cl, 2
		shl	bx, cl
else
		add	bx, bx
endif
		call	_atexittbl[bx]

@@exit_slow:
		cmp	_atexitcnt, 0
		jnz	short @@atexit_loop
		nopcall	__cleanup
		call	_exitbuf

@@exit_part2:
		nopcall	__restorezero
		nopcall	__checknull
		cmp	[bp+@@dontexit], 0
		jnz	short @@___exit_ret
		cmp	[bp+@@quick], 0
		jnz	short @@exit_terminate
		call	_exitfopen
		call	_exitopen

@@exit_terminate:
		push	[bp+@@errcode]
		nopcall	__terminate
		pop	cx

@@___exit_ret:
		pop	di
		pop	si
		pop	bp
		retn	6
___exit	endp

; void __cdecl exit(int	status)
public _exit
_exit		proc
@@status		= word ptr 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+@@status]
		call	___exit
		pop	di
		pop	si
		pop	bp
		ret
_exit		endp

; void __cdecl _exit(int status)
public _exit
__exit		proc
@@status		= word ptr 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, 1
		push	ax
		xor	ax, ax
		push	ax
		push	[bp+@@status]
		call	___exit
		pop	di
		pop	si
		pop	bp
		ret
__exit		endp

; void _cexit(void)
public __cexit
__cexit		proc
		push	si
		push	di
		xor	ax, ax
		push	ax
		mov	ax, 1
		push	ax
		xor	ax, ax
		push	ax
		call	___exit
		pop	di
		pop	si
		ret
__cexit		endp

; void _c_exit(void)
public __c_exit
__c_exit	proc
		push	si
		push	di
		mov	ax, 1
		push	ax
		push	ax
		xor	ax, ax
		push	ax
		call	___exit
		pop	di
		pop	si
		ret
__c_exit	endp
