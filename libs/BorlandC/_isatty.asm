; int __cdecl isatty(int handle)
public _isatty

_isatty		proc DIST

if LDATA
@@handle		= word ptr  6
else
@@handle		= word ptr  4
endif

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, 4400h
		mov	bx, [bp+@@handle]
		int	21h		; DOS -	2+ - IOCTL - GET DEVICE	INFORMATION
					; BX = file or device handle
		xchg	ax, dx
		and	ax, 80h
		pop	di
		pop	si
		pop	bp
		ret
_isatty		endp
