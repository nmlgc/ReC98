; operator new[](unsigned int)
		public @$bnwa$qui
@$bnwa$qui	proc DIST
@@size		= word ptr 2 + dPtrSize

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	[bp+@@size]
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		pop	di
		pop	si
		pop	bp
		ret
@$bnwa$qui	endp
