; int __cdecl __far string__string(__int32, char *s, int)
		public @string@$bctr$qnxc
@string@$bctr$qnxc proc	far

@@var_22		= word ptr -22h
@@var_16		= word ptr -16h
@@var_4		= word ptr -4
@@var_2		= word ptr -2
@@arg_0		= dword	ptr  6
@@s		= word ptr  0Ah
@@arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	ctor3_1003F
		mov	bx, offset ctor3_1003F
		call	___InitExceptBlocks
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short @@ctor3_1013F
		mov	ax, 4
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+@@arg_0+2], dx
		mov	word ptr [bp+@@arg_0], ax
		or	ax, dx
		jz	short @@ctor3_101B3

@@ctor3_1013F:
		mov	ax, 0Ch
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	[bp+@@var_2], dx
		mov	[bp+@@var_4], ax
		or	ax, dx
		jz	short @@ctor3_101A3
		mov	[bp+@@var_16], 0Eh
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		mov	ax, [bp+@@s]
		or	ax, [bp+@@arg_6]
		jz	short @@ctor3_10175
		push	[bp+@@arg_6]
		push	[bp+@@s]		; s
		call	_strlen
		pop	cx
		pop	cx
		jmp	short @@ctor3_10177

@@ctor3_10175:
		xor	ax, ax

@@ctor3_10177:
		push	ax
		push	[bp+@@arg_6]
		push	[bp+@@s]
		push	[bp+@@var_2]
		push	[bp+@@var_4]
		nopcall	@TStringRef@$bctr$qnxcuit1uiui ; TStringRef::TStringRef(char *,uint,char *,uint,uint)
		add	sp, 12h
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	[bp+@@var_16], 6

@@ctor3_101A3:
		mov	dx, [bp+@@var_2]
		mov	ax, [bp+@@var_4]
		les	bx, [bp+@@arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax

@@ctor3_101B3:
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		push	[bp+@@var_22]
		call	___ExitExceptBlocks
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@$bctr$qnxc endp

ctor3_101D9	db 4, 0, 90h, 20h, 0Ah,	0
		dd ctor3_102B8
		db 'TStringRef *',0
ctor3_101F0	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
		db 0Dh dup(0), 2, 0, 2,	0
		dd ctor3_10055
		db 5, 0, 4Ah, 0
		db 'string::lengtherror',0
		dd ctor3_10280
		dw 0
		db 3, 0Dh dup(0)
ctor3_1023E	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
		db 0Dh dup(0), 2, 0, 2,	0
		dd ctor3_100A2
		dw 5
		dw 3Eh
		db 'xalloc',0
		db 0
		dd ctor3_10280
		db 2 dup(0), 3,	0Dh dup(0)
ctor3_10280	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
		db 0Dh dup(0), 1, 0, 1,	0
		dd @xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		dw 5
		dw 34h
		db 'xmsg',0
		dd 0
		dd 0
		dd 0
		db 0
ctor3_102B8	db 0Ch,	0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 32h, 0, 3Eh
		db 0Dh dup(0), 1, 0, 1,	0
		dd @TStringRef@$bdtr$qv	; TStringRef::~TStringRef(void)
		db 5, 0, 42h, 0, 54h, 53h, 74h,	72h, 69h, 6Eh, 67h, 52h
		db 65h,	66h, 2 dup(0)
		dd ctor3_102FE
		dw 0
		db 3, 0Dh dup(0)
ctor3_102FE	dw 2
		dw 3
		dw 1Ah
		dw 0FFFFh
		dw 1
		dw 26h
		dw 2Ah
		dd 0
		dd 0
		dd 0
aTreference	db 'TReference',0
		dd 0
		dd 0
		db 0
