MAXDIR equ 66
GETDCWD_STACK_SIZE equ 2 + MAXDIR + 4

; char *__cdecl	_getdcwd(int drive, char *bufP, int bufL)
public __getdcwd
__getdcwd	proc
@@bufI		= byte ptr -GETDCWD_STACK_SIZE
@@drv		= word ptr -2
@@drive		= word ptr dPtrSize + 2
@@bufP		= DPTR_  dPtrSize + 4
@@bufL		= word ptr dPtrSize + 4 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, GETDCWD_STACK_SIZE
		push	si
		push	di
		mov	ax, [bp+@@drive]
		mov	[bp+@@drv], ax
		or	ax, ax
		jnz	short @@getdcwdDo
		mov	ah, 19h
		int	21h
		mov	ah, 0
		inc	ax
		mov	[bp+@@drv], ax

@@getdcwdDo:
		mov	al, byte ptr [bp+@@drv]
		add	al, 'A'-1
		mov	[bp+@@bufI], al
		mov	[bp+@@bufI+1], ':'
		mov	[bp+@@bufI+2], '\'
if LDATA
		push	ds
		mov	ax, ss
		mov	ds, ax
endif
		lea	si, [bp+@@bufI+3]
		mov	ah, 47h
		mov	dl, byte ptr [bp+@@drv]
		int	21h
if LDATA
		pop	ds
endif
		jb	short @@getdcwdRet0
		push	ss
		lea	ax, [bp+@@bufI]
		push	ax
		nopcall	_strlen
		pop	cx
		pop	cx
		cmp	ax, [bp+@@bufL]
		jb	short @@getdcwdAlloc
		mov	_errno, 22h
		jmp	short @@getdcwdRet0

@@getdcwdAlloc:
		mov	ax, word ptr [bp+@@bufP]
		or	ax, word ptr [bp+@@bufP+2]
		jnz	short @@getdcwdCopy
		push	[bp+@@bufL]
		nopcall	_malloc
		pop	cx
		mov	word ptr [bp+@@bufP+2],	dx
		mov	word ptr [bp+@@bufP], ax
		or	ax, dx
		jnz	short @@getdcwdCopy
		mov	_errno, 8

@@getdcwdRet0:
		xor	dx, dx
		xor	ax, ax
		jmp	short @@getdcwdRet

@@getdcwdCopy:
		push	ss
		lea	ax, [bp+@@bufI]
		push	ax
		push	word ptr [bp+@@bufP+2]
		push	word ptr [bp+@@bufP]
		nopcall	_strcpy
		add	sp, 8
		mov	dx, word ptr [bp+@@bufP+2]
		mov	ax, word ptr [bp+@@bufP]

@@getdcwdRet:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__getdcwd	endp
