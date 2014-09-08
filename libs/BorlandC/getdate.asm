; void __cdecl getdate(struct date *datep)
_getdate	proc DIST
@@datep		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 2Ah
		int	21h
		LES_	bx, [bp+@@datep]
		mov	es:[bx], cx
		mov	es:[bx+2], dx
		pop	di
		pop	si
		pop	bp
		ret
_getdate	endp

; void __cdecl gettime(struct time *timep)
_gettime	proc DIST
@@timep		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ah, 2Ch
		int	21h	
		LES_	bx, [bp+@@timep]
		mov	es:[bx], cx
		mov	es:[bx+2], dx
		pop	di
		pop	si
		pop	bp
		ret
_gettime	endp
