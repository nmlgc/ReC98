__xfclose	proc
@@i		= word ptr -(dPtrSize + 2)
@@fp		= DPTR_ -(dPtrSize)

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize + 2
		push	si
		push	di
		mov	[bp+@@i], 0
if LDATA
		mov	word ptr [bp+@@fp+2], ds
endif
		mov	word ptr [bp+@@fp], offset _streams
		jmp	short @@check

@@loop:
		LES_	bx, [bp+@@fp]
		test	byte ptr ES_[bx+FILE.flags], 3
		jz	short @@next
		push	word ptr [bp+@@fp+2]
		push	bx
		nopcall	_fclose
if LDATA
		pop	cx
endif
		pop	cx

@@next:
		add	word ptr [bp+@@fp], size FILE
		inc	[bp+@@i]

@@check:
		mov	ax, [bp+@@i]
		cmp	ax, __nfile
		jb	short @@loop
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__xfclose	endp
