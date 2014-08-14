; int pascal near __IOerror(int dosErr)
; int pascal near __DOSerror(int dosErr)
public __IOERROR
public __DOSERROR

__IOERROR	proc near

@@dosErr		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, [bp+@@dosErr]
		or	dx, dx
		jl	short @@ser_maybeSVerr
		cmp	dx, 58h	; 'X'
		jle	short @@ser_dosError

@@ser_errorFault:
		mov	dx, 57h	; 'W'

@@ser_dosError:
		mov	__doserrno, dx
		mov	bx, dx
		mov	al, __dosErrorToSV[bx]
		cbw
		mov	dx, ax
		jmp	short @@ser_end
; ---------------------------------------------------------------------------

@@ser_maybeSVerr:
		neg	dx
		cmp	dx, __sys_nerr
		jg	short @@ser_errorFault
		mov	__doserrno, 0FFFFh

@@ser_end:
		mov	__errno, dx
		mov	ax, 0FFFFh
		pop	di
		pop	si
		pop	bp
		retn	2
__IOERROR	endp

__DOSERROR	proc near

@@dosErr		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@dosErr]
		call	__IOERROR
		mov	ax, [bp+@@dosErr]
		pop	di
		pop	si
		pop	bp
		retn	2
__DOSERROR	endp
