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
		cmp	dx, e_dosFinalError
		jle	short @@ser_dosError

@@ser_errorFault:
		mov	dx, e_parameter

@@ser_dosError:
		mov	__doserrno, dx
		mov	bx, dx
		mov	al, __dosErrorToSV[bx]
		cbw
		mov	dx, ax
		jmp	short @@ser_end

@@ser_maybeSVerr:
		neg	dx
		cmp	dx, __sys_nerr
		jg	short @@ser_errorFault
		mov	__doserrno, -1

@@ser_end:
		mov	_errno, dx
		mov	ax, -1
		pop	di
		pop	si
		pop	bp
		ret	2
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
		ret	2
__DOSERROR	endp
