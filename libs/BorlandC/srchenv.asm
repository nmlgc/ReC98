; void __cdecl __far _searchenv(const char *file, const char *varname, const char *pathname)
		public __searchenv
__searchenv	proc DIST
@@env		= dword	ptr -4
@@file		= dword	ptr  6
@@varname	= dword	ptr  0Ah
@@pathname	= dword	ptr  0Eh

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		push	word ptr [bp+@@varname+2]
		push	word ptr [bp+@@varname]
		nopcall	_getenv
		pop	cx
		pop	cx
		mov	word ptr [bp+@@env+2], dx
		mov	word ptr [bp+@@env], ax
		or	ax, dx
		jnz	short @@search
		mov	word ptr [bp+@@env+2], ds
		mov	word ptr [bp+@@env], offset srchenv_empty

@@search:
		push	word ptr [bp+@@pathname+2]
		push	word ptr [bp+@@pathname]
		push	word ptr [bp+@@env+2]
		push	word ptr [bp+@@env]
		push	word ptr [bp+@@file+2]
		push	word ptr [bp+@@file]
		nopcall	__searchstr
		add	sp, 0Ch
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
__searchenv	endp
