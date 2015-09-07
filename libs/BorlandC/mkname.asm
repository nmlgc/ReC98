; char *__pascal __near _MKNAME(char *s, char *prefix, unsigned int num)
		public __MKNAME
__MKNAME	proc near
@@num		= word ptr  4
@@prefix	= dword	ptr  6
@@s		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+@@s]
		or	ax, word ptr [bp+@@s+2]
		jnz	short @@haveS
		mov	word ptr [bp+@@s+2], ds
		mov	word ptr [bp+@@s], offset mkname_template

@@haveS:
		push	[bp+@@num]
		mov	ax, word ptr [bp+@@prefix]
		or	ax, word ptr [bp+@@prefix+2]
		jnz	short @@havePrefix
		mov	dx, ds
		mov	ax, offset mkname_TMP
		jmp	short @@build

@@havePrefix:
		mov	dx, word ptr [bp+@@prefix+2]
		mov	ax, word ptr [bp+@@prefix]

@@build:
		push	dx
		push	ax
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]
		nopcall	_stpcpy
		add	sp, 8
		push	dx
		push	ax
		call	__UTOA
		push	ds
		mov	ax, offset mkname_$$$
		push	ax
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]
		nopcall	_strcat
		add	sp, 8
		mov	dx, word ptr [bp+@@s+2]
		mov	ax, word ptr [bp+@@s]
		pop	di
		pop	si
		pop	bp
		retn	0Ah
__MKNAME	endp

; char *__pascal __near _TMPNAM(char *s, unsigned int *numP)
		public __TMPNAM
__TMPNAM	proc near
@@attr		= byte ptr -2
@@numP		= dword	ptr  4
@@s		= dword	ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di

@@loop:
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]
		xor	ax, ax
		push	ax
		push	ax
		LES_	bx, [bp+@@numP]
		cmp	word ptr ES_[bx], -1
		jnz	short @@incNumP
		mov	ax, 2
		jmp	short @@mkname

@@incNumP:
		mov	ax, 1

@@mkname:
		LES_	bx, [bp+@@numP]
		add	ES_[bx], ax
		mov	ax, ES_[bx]
		push	ax
		call	__MKNAME
		mov	word ptr [bp+@@s+2], dx
		mov	word ptr [bp+@@s], ax
		push	ss
		lea	ax, [bp+@@attr]
		push	ax
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]
		nopcall	__dos_getfileattr
		add	sp, 8
		or	ax, ax
		jz	short @@loop
		mov	dx, word ptr [bp+@@s+2]
		mov	ax, word ptr [bp+@@s]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	8
__TMPNAM	endp
