xmsg_10020	dd xmsg_1038E
		db 87h,	20h, 0FCh, 0FFh, 6 dup(0)
xmsg_1002E	db 4 dup(0), 0DEh, 0FFh, 2 dup(0), 5, 3	dup(0),	2 dup(0FFh)
		db 6, 0, 5, 3 dup(0)
		dw offset xmsg_10020

; xmsg::xmsg(string const &)
		public @xmsg@$bctr$qmx6string
@xmsg@$bctr$qmx6string proc far

var_22		= word ptr -22h
var_16		= word ptr -16h
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	xmsg_1002E
		mov	bx, offset xmsg_1002E
		nopcall	___InitExceptBlocks
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short @@xmsg_10073
		mov	ax, 4
		push	ax
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short @@xmsg_100C5

@@xmsg_10073:
		mov	ax, 4
		push	ax
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	[bp+var_2], dx
		mov	[bp+var_4], ax
		or	ax, dx
		jz	short @@xmsg_100B5
		mov	[bp+var_16], 0Eh
		push	[bp+arg_6]
		push	[bp+arg_4]
		push	dx
		push	[bp+var_4]
		call	@string@$bctr$qmx6string ; string::string(string &)
		add	sp, 8
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	[bp+var_16], 6

@@xmsg_100B5:
		mov	dx, [bp+var_2]
		mov	ax, [bp+var_4]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax

@@xmsg_100C5:
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		push	[bp+var_22]
		nopcall	___ExitExceptBlocks
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@xmsg@$bctr$qmx6string endp

xmsg_100EB	dd xmsg_1038E
		db 87h,	20h, 0FCh, 0FFh, 6 dup(0)
xmsg_100F9	db 4 dup(0), 0DEh, 0FFh, 2 dup(0), 5, 3	dup(0),	2 dup(0FFh)
		db 6, 0, 5, 3 dup(0)
		dw offset xmsg_100EB

; xmsg::xmsg(xmsg const	&)
		public @xmsg@$bctr$qmx4xmsg
@xmsg@$bctr$qmx4xmsg proc far

var_22		= word ptr -22h
var_16		= word ptr -16h
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	xmsg_100F9
		mov	bx, offset xmsg_100F9
		nopcall	___InitExceptBlocks
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short @@xmsg_1013E
		mov	ax, 4
		push	ax
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short @@xmsg_10194

@@xmsg_1013E:
		mov	ax, 4
		push	ax
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	[bp+var_2], dx
		mov	[bp+var_4], ax
		or	ax, dx
		jz	short @@xmsg_10184
		mov	[bp+var_16], 0Eh
		les	bx, [bp+arg_4]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		push	dx
		push	[bp+var_4]
		call	@string@$bctr$qmx6string ; string::string(string &)
		add	sp, 8
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	[bp+var_16], 6

@@xmsg_10184:
		mov	dx, [bp+var_2]
		mov	ax, [bp+var_4]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax

@@xmsg_10194:
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		push	[bp+var_22]
		nopcall	___ExitExceptBlocks
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@xmsg@$bctr$qmx4xmsg endp

; int __cdecl __far xmsg___xmsg(void *,	int, char)
		public @xmsg@$bdtr$qv
@xmsg@$bdtr$qv	proc far

arg_0		= word ptr  6
arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, [bp+arg_0]
		or	ax, [bp+8]
		jz	short @@xmsg_10214
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	ax, 3
		push	ax
		les	bx, dword ptr [bp+arg_0]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		call	@string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		test	[bp+arg_4], 1
		jz	short @@xmsg_10214
		push	word ptr [bp+8]
		push	[bp+arg_0]	; void *
		nopcall	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx

@@xmsg_10214:
		pop	di
		pop	si
		pop	bp
		retf
@xmsg@$bdtr$qv	endp

xmsg_10218	dd xmsg_10356
		dd 0
xmsg_10220	dd xmsg_10218
		db 0E2h, 0FFh

; xmsg::raise(void)
		public @xmsg@raise$qv
@xmsg@raise$qv	proc far

var_22		= byte ptr -22h
arg_0		= word ptr  6
arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	xmsg_10220
		mov	bx, offset xmsg_10220
		nopcall	___InitExceptBlocks
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, seg	@xmsg@$bctr$qmx4xmsg
		push	ax
		mov	ax, offset @xmsg@$bctr$qmx4xmsg	; xmsg::xmsg(xmsg &)
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		push	[bp+arg_2]
		push	[bp+arg_0]
		push	ss
		lea	ax, [bp+var_22]
		push	ax
		call	@xmsg@$bctr$qmx4xmsg ;	xmsg::xmsg(xmsg	&)
		add	sp, 8
		lea	ax, [bp+var_22]
		push	ss
		push	ax
		push	cs
		mov	ax, offset xmsg_10356
		push	ax
		nopcall	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@xmsg@raise$qv	endp

xmsg_10279	dd xmsg_1038E
		db 87h,	20h, 0FCh, 0FFh, 6 dup(0)
xmsg_10287	db 4 dup(0), 0DEh, 0FFh, 2 dup(0), 5, 3	dup(0),	2 dup(0FFh)
		db 6, 0, 5, 3 dup(0)
		dw offset xmsg_10279

; xmsg::operator=(xmsg const &)
		public @xmsg@$basg$qmx4xmsg
@xmsg@$basg$qmx4xmsg proc far

var_22		= word ptr -22h
var_16		= word ptr -16h
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	xmsg_10287
		mov	bx, offset xmsg_10287
		nopcall	___InitExceptBlocks
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		cmp	dx, word ptr [bp+arg_4+2]
		jnz	short @@xmsg_102C0
		cmp	ax, word ptr [bp+arg_4]
		jz	short @@xmsg_1033E

@@xmsg_102C0:
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	ax, 3
		push	ax
		les	bx, [bp+arg_0]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		call	@string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	ax, 4
		push	ax
		nopcall	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	[bp+var_2], dx
		mov	[bp+var_4], ax
		or	ax, dx
		jz	short @@xmsg_1032E
		mov	[bp+var_16], 0Eh
		les	bx, [bp+arg_4]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx]
		push	dx
		push	[bp+var_4]
		call	@string@$bctr$qmx6string ; string::string(string &)
		add	sp, 8
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	[bp+var_16], 6

@@xmsg_1032E:
		mov	dx, [bp+var_2]
		mov	ax, [bp+var_4]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax

@@xmsg_1033E:
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		push	dx
		push	ax
		push	[bp+var_22]
		nopcall	___ExitExceptBlocks
		pop	ax
		pop	dx
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@xmsg@$basg$qmx4xmsg endp

xmsg_10356	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h ;	...
		db 0Dh dup(0), 1, 0, 1,	0
		dd @xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		db    5
		db    0
		db  34h	; 4
		db    0
aXmsg		db 'xmsg',0
		db 0Dh dup(0)
xmsg_1038E	db 4, 0, 10h, 20h, 0Ah,	0
		dd xmsg_103A1
		db 'string *',0
xmsg_103A1	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Eh, 0, 32h ;	...
		db 0Dh dup(0), 1, 0, 1,	0
		dd @string@$bdtr$qv	; string::~string(void)
		db    5
		db    0
		db  36h	; 6
		db    0
		db 'string',0
		db 0Dh dup(0)
