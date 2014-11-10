; unsigned __int32 farcoreleft(void)
_farcoreleft	proc
@@value		= dword	ptr -4

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	word ptr [bp+@@value+2], 0
		mov	word ptr [bp+@@value], 0
		mov	dx, word ptr _heaptop@+2
		mov	ax, word ptr _heaptop@
		mov	cx, word ptr _brklvl@+2
		mov	bx, word ptr _brklvl@
		call	N_PSBP@
		mov	word ptr [bp+@@value+2], dx
		mov	word ptr [bp+@@value], ax
		cmp	word ptr [bp+@@value+2], 0
		jb	short @@ret
		ja	short @@sub16
		cmp	word ptr [bp+@@value], 16
		jbe	short @@ret

@@sub16:
		sub	word ptr [bp+@@value], 16
		sbb	word ptr [bp+@@value+2], 0

@@ret:
		and	word ptr [bp+@@value], 0FFF0h
		mov	dx, word ptr [bp+@@value+2]
		mov	ax, word ptr [bp+@@value]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_farcoreleft	endp ; sp-analysis failed
