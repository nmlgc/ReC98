; int __cdecl access(const char *filename, int amode)
_access		proc
@@filename	= DPTR_ (2 + cPtrSize)
@@amode		= byte ptr (2 + cPtrSize + dPtrSize)

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+@@amode]
if LDATA
		push	word ptr [bp+@@filename+2]
endif
		push	word ptr [bp+@@filename]
		nopcall	__access
		add	sp, 2 + dPtrSize
		pop	di
		pop	si
		pop	bp
		ret
_access		endp
