; int execl(char *pathP, char *arg0, ...)
		public _execl
_execl		proc DIST
@@pathP		= DPTR_ 2 + dPtrSize
@@arg0		= DPTR_ 2 + (dPtrSize * 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ss
		lea	ax, [bp+@@arg0]
		push	ax
		push	word ptr [bp+@@pathP+2]
		push	word ptr [bp+@@pathP]
		mov	ax, offset __exec
		push	ax
		call	__LoadProg
		add	sp, 10h
		pop	di
		pop	si
		pop	bp
		ret
_execl		endp
