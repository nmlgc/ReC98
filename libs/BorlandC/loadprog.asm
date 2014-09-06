loadprog_strchr	proc DIST
@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  6
@@arg_2		= word ptr  8
@@arg_4		= word ptr  0Ah
@@arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 8
		push	si
		push	di
		mov	dx, [bp+@@arg_2]
		mov	ax, [bp+@@arg_0]
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		jmp	short @@loc_100A1

@@loc_10046:
		les	bx, [bp+@@var_4]
		mov	al, es:[bx]
		push	ax
		nopcall	___path_isdbcsleadbyte
		pop	cx
		or	ax, ax
		jz	short @@loc_10065
		inc	word ptr [bp+@@var_4]
		les	bx, [bp+@@var_4]
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_1009E
		jmp	short @@loc_100AA

@@loc_10065:
		mov	dx, [bp+@@arg_6]
		mov	ax, [bp+@@arg_4]
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		jmp	short @@loc_10084

@@loc_10073:
		les	bx, [bp+@@var_4]
		mov	al, es:[bx]
		les	bx, [bp+@@var_8]
		cmp	al, es:[bx]
		jz	short @@loc_1008D
		inc	word ptr [bp+@@var_8]

@@loc_10084:
		les	bx, [bp+@@var_8]
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_10073

@@loc_1008D:
		les	bx, [bp+@@var_8]
		cmp	byte ptr es:[bx], 0
		jz	short @@loc_1009E
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		jmp	short @@loc_100AE

@@loc_1009E:
		inc	word ptr [bp+@@var_4]

@@loc_100A1:
		les	bx, [bp+@@var_4]
		cmp	byte ptr es:[bx], 0
		jnz	short @@loc_10046

@@loc_100AA:
		xor	dx, dx
		xor	ax, ax

@@loc_100AE:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
loadprog_strchr	endp


; int __cdecl __far loadprog_search(const char *pathP, char *fullname, const char *ext, int UsePath)
loadprog_search	proc DIST
@@name		= byte ptr -50h
@@pathP		= dword	ptr  6
@@fullname	= dword	ptr  0Ah
@@ext		= dword	ptr  0Eh
@@UsePath	= dword	ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 50h
		push	si
		push	di
		push	word ptr [bp+@@pathP+2]
		push	word ptr [bp+@@pathP]
		push	ss
		lea	ax, [bp+@@name]
		push	ax
		nopcall	_strcpy
		push	word ptr [bp+@@ext+2]
		push	word ptr [bp+@@ext]
		push	ss
		lea	ax, [bp+@@name]
		push	ax
		nopcall	_strcat
		add	sp, 10h
		cmp	word ptr [bp+@@UsePath], 0
		jz	short @@dontUsePath
		push	word ptr [bp+@@fullname+2]
		push	word ptr [bp+@@fullname]
		push	ds
		mov	ax, offset loadprog_PATH ; "PATH"
		push	ax
		push	ss
		lea	ax, [bp+@@name]
		push	ax
		nopcall	__searchenv
		add	sp, 0Ch
		les	bx, [bp+@@fullname]
		cmp	byte ptr es:[bx], 0
		jz	short @@ret0
		jmp	short @@ret1

@@dontUsePath:
		push	ss
		lea	ax, [bp+@@name]
		push	ax
		push	word ptr [bp+@@fullname+2]
		push	word ptr [bp+@@fullname]
		nopcall	_strcpy
		add	sp, 8
		mov	ax, 4
		push	ax
		push	ss
		lea	ax, [bp+@@name]
		push	ax
		nopcall	__access
		add	sp, 6
		or	ax, ax
		jnz	short @@ret0

@@ret1:
		mov	ax, 1
		jmp	short @@ret

@@ret0:
		xor	ax, ax

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
loadprog_search	endp


		public __LoadProg
__LoadProg	proc near
@@var_9C		= byte ptr -9Ch
@@var_1A		= word ptr -1Ah
@@var_18		= word ptr -18h
@@var_16		= word ptr -16h
@@var_14		= dword	ptr -14h
@@var_10		= dword	ptr -10h
@@var_C		= dword	ptr -0Ch
@@var_8		= dword	ptr -8
@@var_4		= dword	ptr -4
@@arg_0		= word ptr  4
@@arg_2		= dword	ptr  6
@@arg_6		= dword	ptr  0Ah
@@arg_A		= dword	ptr  0Eh
@@arg_E		= word ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 9Ch
		push	si
		push	di
		les	bx, [bp+@@arg_2]
		mov	al, es:[bx]
		cbw
		mov	dx, ax
		cmp	ax, 'a'
		jb	short @@loc_10157
		sub	dx, 20h	; ' '

@@loc_10157:
		cmp	dx, 'A'
		jb	short @@loc_1016B
		cmp	dx, 'Z'
		ja	short @@loc_1016B
		les	bx, [bp+@@arg_2]
		cmp	byte ptr es:[bx+1], ':'
		jz	short @@loc_10181

@@loc_1016B:
		push	ds
		mov	ax, offset loadprog_slashes ; "/\\"
		push	ax
		push	word ptr [bp+@@arg_2+2]
		push	word ptr [bp+@@arg_2]
		call	loadprog_strchr
		add	sp, 8
		or	ax, dx
		jz	short @@loc_10186

@@loc_10181:
		mov	[bp+@@arg_E], 0

@@loc_10186:
		mov	[bp+@@var_1A], 0
		mov	ax, '.'
		push	ax
		push	word ptr [bp+@@arg_2+2]
		push	word ptr [bp+@@arg_2]
		nopcall	_strrchr
		add	sp, 6
		mov	word ptr [bp+@@var_10+2],	dx
		mov	word ptr [bp+@@var_10], ax
		or	ax, dx
		jz	short @@loc_101E5
		push	[bp+@@arg_E]
		push	ds
		mov	ax, offset loadprog_empty
		push	ax
		push	ss
		lea	ax, [bp+@@var_9C]
		push	ax
		push	word ptr [bp+@@arg_2+2]
		push	word ptr [bp+@@arg_2]
		call	loadprog_search
		add	sp, 0Eh
		mov	[bp+@@var_18], ax
		or	ax, ax
		jnz	short @@loc_101CC
		jmp	@@loc_10250

@@loc_101CC:
		push	ds
		mov	ax, offset loadprog_BAT	; ".BAT"
		push	ax
		push	word ptr [bp+@@var_10+2]
		push	word ptr [bp+@@var_10]
		nopcall	_stricmp
		add	sp, 8
		or	ax, ax
		jnz	short @@loc_10250
		jmp	short @@loc_1024B

@@loc_101E5:
		push	[bp+@@arg_E]
		push	ds
		mov	ax, offset loadprog_COM	; ".COM"
		push	ax
		push	ss
		lea	ax, [bp+@@var_9C]
		push	ax
		push	word ptr [bp+@@arg_2+2]
		push	word ptr [bp+@@arg_2]
		call	loadprog_search
		add	sp, 0Eh
		mov	[bp+@@var_18], ax
		or	ax, ax
		jnz	short @@loc_10250
		push	[bp+@@arg_E]
		push	ds
		mov	ax, offset loadprog_EXE	; ".EXE"
		push	ax
		push	ss
		lea	ax, [bp+@@var_9C]
		push	ax
		push	word ptr [bp+@@arg_2+2]
		push	word ptr [bp+@@arg_2]
		call	loadprog_search
		add	sp, 0Eh
		mov	[bp+@@var_18], ax
		or	ax, ax
		jnz	short @@loc_10250
		push	[bp+@@arg_E]
		push	ds
		mov	ax, offset loadprog_BAT_0 ; ".BAT"
		push	ax
		push	ss
		lea	ax, [bp+@@var_9C]
		push	ax
		push	word ptr [bp+@@arg_2+2]
		push	word ptr [bp+@@arg_2]
		call	loadprog_search
		add	sp, 0Eh
		mov	[bp+@@var_18], ax
		or	ax, ax
		jz	short @@loc_10250

@@loc_1024B:
		mov	[bp+@@var_1A], 1

@@loc_10250:
		cmp	[bp+@@var_18], 0
		jz	short @@ENOENT
		cmp	[bp+@@var_1A], 0
		jz	short @@loc_1027B
		push	ds
		mov	ax, offset loadprog_COMSPEC ; "COMSPEC"
		push	ax
		nopcall	_getenv
		pop	cx
		pop	cx
		mov	word ptr [bp+@@var_4+2], dx
		mov	word ptr [bp+@@var_4], ax
		or	ax, dx
		jnz	short @@loc_1027B

@@ENOENT:
		mov	word ptr ds:_errno, 2
		jmp	@@retMinus1

@@loc_1027B:
		cmp	[bp+@@var_1A], 0
		jz	short @@loc_10294
		push	word ptr [bp+@@var_4+2]
		push	word ptr [bp+@@var_4]
		push	ds
		mov	ax, offset loadprog_SLASH_C ; "/c"
		push	ax
		push	word ptr [bp+@@arg_6+2]
		push	word ptr [bp+@@arg_6]
		jmp	short @@loc_102A8

@@loc_10294:
		push	ss
		lea	ax, [bp+@@var_9C]
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	ax, word ptr [bp+@@arg_6]
		add	ax, 4
		push	word ptr [bp+@@arg_6+2]
		push	ax

@@loc_102A8:
		call	__DOSCMD
		mov	word ptr [bp+@@var_8+2], dx
		mov	word ptr [bp+@@var_8], ax
		mov	ax, word ptr [bp+@@var_8]
		or	ax, word ptr [bp+@@var_8+2]
		jnz	short @@loc_102C2
		mov	word ptr ds:_errno, 8
		; Hack (jmp @@retMinus1)
		db 0e9h, 07fh, 000h

@@loc_102C2:
		mov	ax, word ptr [bp+@@var_8]
		inc	ax
		push	word ptr [bp+@@var_8+2]
		push	ax
		nopcall	_strlen
		pop	cx
		pop	cx
		cmp	ax, 80h
		jb	short @@loc_102EB
		mov	word ptr ds:_errno, 14h
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		nopcall	_free
		pop	cx
		pop	cx
		jmp	short @@retMinus1

@@loc_102EB:
		mov	ax, word ptr [bp+@@arg_A]
		or	ax, word ptr [bp+@@arg_A+2]
		jnz	short @@loc_10300
		mov	dx, word ptr ds:environ@+2
		mov	ax, word ptr ds:environ@
		mov	word ptr [bp+@@arg_A+2], dx
		mov	word ptr [bp+@@arg_A], ax

@@loc_10300:
		push	word ptr [bp+@@arg_A+2]
		push	word ptr [bp+@@arg_A]
		cmp	[bp+@@var_1A], 0
		jz	short @@loc_10314
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		jmp	short @@loc_1031A

@@loc_10314:
		mov	dx, ss
		lea	ax, [bp+@@var_9C]

@@loc_1031A:
		push	dx
		push	ax
		push	ss
		lea	ax, [bp+@@var_14]
		push	ax
		call	__DOSENV
		mov	word ptr [bp+@@var_C+2], dx
		mov	word ptr [bp+@@var_C], ax
		or	ax, dx
		jnz	short @@loc_10346
		mov	word ptr ds:_errno, 8
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		nopcall	_free
		pop	cx
		pop	cx

@@retMinus1:
		mov	ax, -1
		jmp	short @@ret

@@loc_10346:
		call	dword ptr ds:_exitbuf
		push	word ptr [bp+@@var_C+2]
		push	word ptr [bp+@@var_C]
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		cmp	[bp+@@var_1A], 0
		jz	short @@loc_10364
		mov	dx, word ptr [bp+@@var_4+2]
		mov	ax, word ptr [bp+@@var_4]
		jmp	short @@loc_1036A

@@loc_10364:
		mov	dx, ss
		lea	ax, [bp+@@var_9C]

@@loc_1036A:
		push	dx
		push	ax
		call	[bp+@@arg_0]
		add	sp, 0Ch
		mov	[bp+@@var_16], ax
		push	word ptr [bp+@@var_14+2]
		push	word ptr [bp+@@var_14]
		nopcall	_free
		push	word ptr [bp+@@var_8+2]
		push	word ptr [bp+@@var_8]
		nopcall	_free
		add	sp, 8
		mov	ax, [bp+@@var_16]

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
__LoadProg	endp
