; int ioctl(int fd, int func, void *argdx, int argcx)
public _ioctl
_ioctl		proc

handle		= word ptr  6
_func		= word ptr  8
argdx		= dword	ptr  0Ah
argcx		= word ptr  0Eh

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		lds	dx, [bp+argdx]
		mov	ah, 44h
		mov	al, byte ptr [bp+_func]
		mov	bx, [bp+handle]
		mov	cx, [bp+argcx]
		int	21h
		pop	ds
		jb	short @@ioctlFailed
		cmp	[bp+_func], 0
		jnz	short @@ioctlRetJump
		mov	ax, dx
		jmp	short @@ioctlRet
; ---------------------------------------------------------------------------

@@ioctlRetJump:
		jmp	short @@ioctlRet
; ---------------------------------------------------------------------------

@@ioctlFailed:
		push	ax
		call	__IOERROR

@@ioctlRet:
		pop	di
		pop	si
		pop	bp
		ret
_ioctl		endp
