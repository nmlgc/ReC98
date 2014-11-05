; operator new[](unsigned long size)
		public @$bnwa$qul
@$bnwa$qul	proc
@@size		= dword	ptr (cPtrSize + 2)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@size+2]
		push	word ptr [bp+@@size]
		nopcall	@$bnew$qul
		pop	cx
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
@$bnwa$qul	endp
