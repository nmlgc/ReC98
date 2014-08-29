; xalloc::xalloc(string	const &, unsigned int)
@xalloc@$bctr$qmx6stringui proc	far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short @@xalloc_10041
		mov	ax, 6
		push	ax
		nopcall	@$bnew$qui ; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short @@xalloc_1005F

@@xalloc_10041:
		push	[bp+arg_6]
		push	[bp+arg_4]
		push	word ptr [bp+arg_0+2]
		push	word ptr [bp+arg_0]
		nopcall	@xmsg@$bctr$qmx6string	; xmsg::xmsg(string &)
		add	sp, 8
		les	bx, [bp+arg_0]
		mov	ax, [bp+arg_8]
		mov	es:[bx+4], ax

@@xalloc_1005F:
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	di
		pop	si
		pop	bp
		retf
@xalloc@$bctr$qmx6stringui endp

xalloc_1007B	dd xalloc_1015A
		db 4 dup(0)
xalloc_10083	dd xalloc_1015A
		db 4, 0, 0FAh, 0FFh, 6 dup(0)
xalloc_10091	dd xalloc_1007B
		db 0DCh, 0FFh, 2 dup(0), 5, 3 dup(0)
		dw offset xalloc_10083

; xalloc::raise(void)
@xalloc@raise$qv proc far

var_28		= dword	ptr -28h
@@src		= byte ptr -6
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= word ptr  8

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	xalloc_10091
		mov	bx, offset xalloc_10091
		nopcall	___InitExceptBlocks
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	xalloc_10117
		push	ax		; int
		mov	ax, offset xalloc_10117
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	dx, [bp+arg_2]
		mov	ax, [bp+arg_0]
		mov	word ptr [bp+var_28+2],	dx
		mov	word ptr [bp+var_28], ax
		push	dx
		push	ax
		push	ss
		lea	ax, [bp+@@src]
		push	ax
		nopcall	@xmsg@$bctr$qmx4xmsg ;	xmsg::xmsg(xmsg	&)
		add	sp, 8
		les	bx, [bp+var_28]
		mov	ax, es:[bx+4]
		mov	[bp+var_2], ax
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+@@src]
		push	ss
		push	ax		; src
		push	cs		; int
		mov	ax, offset xalloc_1015A
		push	ax		; int
		nopcall	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void *,uint,uint,uint,uchar	*)
		add	sp, 1Ah
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@xalloc@raise$qv endp

xalloc_10117	proc far

arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	word ptr [bp+0Ch]
		push	word ptr [bp+0Ah]
		push	word ptr [bp+8]
		push	word ptr [bp+6]
		nopcall	@xmsg@$bctr$qmx4xmsg ;	xmsg::xmsg(xmsg	&)
		add	sp, 8
		les	bx, [bp+0Ah]
		mov	ax, es:[bx+4]
		les	bx, [bp+6]
		mov	es:[bx+4], ax
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	dx, [bp+8]
		mov	ax, [bp+6]
		pop	di
		pop	si
		pop	bp
		retf
xalloc_10117	endp

xalloc_1015A	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
		db 0Dh dup(0), 2, 0, 2,	0
		dd xalloc_1019C
		db 5, 0, 3Eh, 0
		db 'xalloc',0
		db 0
		dd xalloc_101E9
		db 2 dup(0), 3,	0Dh dup(0)

xalloc_1019C	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+6]
		or	ax, [bp+8]
		jz	short xalloc_101E3
		nopcall	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		xor	ax, ax
		push	ax
		push	word ptr [bp+8]
		push	word ptr [bp+6]
		nopcall	@xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		add	sp, 6
		test	byte ptr [bp+0Ah], 1
		jz	short xalloc_101E1
		push	word ptr [bp+8]
		push	word ptr [bp+6]
		nopcall	@$bdele$qnv
		pop	cx
		pop	cx
		jmp	short xalloc_101E5

xalloc_101E1:
		jmp	short xalloc_101E5

xalloc_101E3:
		xor	ax, ax

xalloc_101E5:
		pop	di
		pop	si
		pop	bp
		retf
xalloc_1019C	endp

xalloc_101E9	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
		db 0Dh dup(0), 1, 0, 1,	0
		dd @xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		db 5, 0, 34h, 0
		db 'xmsg',0
		db 0Dh dup(0)
