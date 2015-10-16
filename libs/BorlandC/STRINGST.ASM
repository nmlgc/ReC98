; int __cdecl __far string___string(void *, int, char)
		public @string@$bdtr$qv
@string@$bdtr$qv proc far

@@var_1E		= word ptr -1Eh
@@arg_0		= word ptr  6
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	strings_10039
		mov	bx, offset strings_10039
		call	___InitExceptBlocks
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+8]
		jz	short @@strings_10378
		les	bx, dword ptr [bp+@@arg_0]
		les	bx, es:[bx]
		dec	word ptr es:[bx]
		mov	ax, es:[bx]
		or	ax, ax
		jnz	short @@strings_10365
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	ax, 3
		push	ax		; char
		les	bx, dword ptr [bp+@@arg_0]
		push	word ptr es:[bx+2] ; int
		push	word ptr es:[bx] ; void	*
		nopcall	@TStringRef@$bdtr$qv ; TStringRef::~TStringRef(void)
		add	sp, 6

@@strings_10365:
		test	[bp+@@arg_4], 1
		jz	short @@strings_10378
		push	word ptr [bp+8]
		push	[bp+@@arg_0]	; void *
		call	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx

@@strings_10378:
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@$bdtr$qv endp


; string::assert_element(unsigned int)const
		public @string@assert_element$xqui
@string@assert_element$xqui proc far

@@var_28		= word ptr -28h
@@var_26		= word ptr -26h
@@var_1A		= word ptr -1Ah
@@var_8		= byte ptr -8
@@var_4		= byte ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	strings_1006D
		mov	bx, offset strings_1006D
		call	___InitExceptBlocks
		mov	ax, [bp+@@arg_4]
		mov	[bp+@@var_28], ax
		les	bx, [bp+@@arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+@@var_28]
		jbe	short @@strings_103B3
		mov	ax, 1
		jmp	short @@strings_103B5

@@strings_103B3:
		xor	ax, ax

@@strings_103B5:
		or	ax, ax
		jnz	short @@strings_10436
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, seg	strings_1015F
		push	ax
		mov	ax, offset strings_1015F
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	[bp+@@var_1A], 6
		push	ds
		mov	ax, offset aStringReferenc ; "String reference out of range"
		push	ax
		push	ss
		lea	ax, [bp+@@var_4]
		push	ax
		nopcall	@string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+@@var_4]
		push	ss
		push	ax
		push	ss
		lea	ax, [bp+@@var_8]
		push	ax
		call	@xmsg@$bctr$qmx6string ; xmsg::xmsg(string &)
		add	sp, 8
		mov	[bp+@@var_1A], 0Eh
		mov	ax, 2
		push	ax		; char
		push	ss		; int
		lea	ax, [bp+@@var_4]
		push	ax		; void *
		call	@string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	[bp+@@var_1A], 6
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+@@var_8]
		push	ss
		push	ax
		push	cs
		mov	ax, offset strings_10BF5
		push	ax
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

@@strings_10436:
		push	[bp+@@var_26]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@assert_element$xqui endp


; string::assert_index(unsigned	int)const
		public @string@assert_index$xqui
@string@assert_index$xqui proc far

@@var_28		= word ptr -28h
@@var_26		= word ptr -26h
@@var_1A		= word ptr -1Ah
@@var_8		= byte ptr -8
@@var_4		= byte ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	strings_100B1
		mov	bx, offset strings_100B1
		call	___InitExceptBlocks
		mov	ax, [bp+@@arg_4]
		mov	[bp+@@var_28], ax
		les	bx, [bp+@@arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+@@var_28]
		jb	short @@strings_10471
		mov	ax, 1
		jmp	short @@strings_10473

@@strings_10471:
		xor	ax, ax

@@strings_10473:
		or	ax, ax
		jnz	short @@strings_104F4
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, seg	strings_1015F
		push	ax
		mov	ax, offset strings_1015F
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	[bp+@@var_1A], 6
		push	ds
		mov	ax, offset aStringRefere_0 ; "String reference out of range"
		push	ax
		push	ss
		lea	ax, [bp+@@var_4]
		push	ax
		nopcall	@string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+@@var_4]
		push	ss
		push	ax
		push	ss
		lea	ax, [bp+@@var_8]
		push	ax
		call	@xmsg@$bctr$qmx6string ; xmsg::xmsg(string &)
		add	sp, 8
		mov	[bp+@@var_1A], 0Eh
		mov	ax, 2
		push	ax		; char
		push	ss		; int
		lea	ax, [bp+@@var_4]
		push	ax		; void *
		call	@string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	[bp+@@var_1A], 6
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+@@var_8]
		push	ss
		push	ax
		push	cs
		mov	ax, offset strings_10BF5
		push	ax
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

@@strings_104F4:
		push	[bp+@@var_26]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@assert_index$xqui endp


; TSubString::assert_element(unsigned int)const
		public @TSubString@assert_element$xqui
@TSubString@assert_element$xqui	proc far

@@var_28		= word ptr -28h
@@var_26		= word ptr -26h
@@var_1A		= word ptr -1Ah
@@var_8		= byte ptr -8
@@var_4		= byte ptr -4
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	strings_100F5
		mov	bx, offset strings_100F5
		call	___InitExceptBlocks
		mov	ax, [bp+@@arg_4]
		mov	[bp+@@var_28], ax
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+@@var_28]
		jbe	short @@strings_1052C
		mov	ax, 1
		jmp	short @@strings_1052E

@@strings_1052C:
		xor	ax, ax

@@strings_1052E:
		or	ax, ax
		jnz	short @@strings_105AF
		xor	ax, ax
		push	ax
		push	ax
		push	ax
		push	ax
		mov	ax, 5
		push	ax
		mov	ax, seg	strings_1015F
		push	ax
		mov	ax, offset strings_1015F
		push	ax
		xor	ax, ax
		push	ax
		push	ax
		mov	[bp+@@var_1A], 6
		push	ds
		mov	ax, offset aStringRefere_1 ; "String reference out of range"
		push	ax
		push	ss
		lea	ax, [bp+@@var_4]
		push	ax
		nopcall	@string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+@@var_4]
		push	ss
		push	ax
		push	ss
		lea	ax, [bp+@@var_8]
		push	ax
		call	@xmsg@$bctr$qmx6string ; xmsg::xmsg(string &)
		add	sp, 8
		mov	[bp+@@var_1A], 0Eh
		mov	ax, 2
		push	ax		; char
		push	ss		; int
		lea	ax, [bp+@@var_4]
		push	ax		; void *
		call	@string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	[bp+@@var_1A], 6
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+@@var_8]
		push	ss
		push	ax
		push	cs
		mov	ax, offset strings_10BF5
		push	ax
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

@@strings_105AF:
		push	[bp+@@var_26]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TSubString@assert_element$xqui	endp


; int __cdecl __far TStringRef__TStringRef(__int32, size_t n, int, int,	int, int, int, int)
		public @TStringRef@$bctr$qnxcuit1uiui
@TStringRef@$bctr$qnxcuit1uiui proc far

@@arg_0		= dword	ptr  6
n		= word ptr  0Ah
@@arg_6		= word ptr  0Ch
@@arg_8		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h
@@arg_E		= word ptr  14h
@@arg_10		= word ptr  16h

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+@@arg_0]
		or	ax, word ptr [bp+@@arg_0+2]
		jnz	short @@strings_105E1
		mov	ax, 0Ch
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+@@arg_0+2], dx
		mov	word ptr [bp+@@arg_0], ax
		or	ax, dx
		jnz	short @@strings_105E1
		jmp	@@strings_10687

@@strings_105E1:
		les	bx, [bp+@@arg_0]
		mov	word ptr es:[bx], 1
		mov	word ptr es:[bx+0Ah], 0
		mov	ax, [bp+@@arg_8]
		add	ax, [bp+@@arg_E]
		mov	es:[bx+6], ax
		mov	ax, es:[bx+6]
		add	ax, [bp+@@arg_10]
		push	ax
		nopcall	@TStringRef@round_capacity$qui ; TStringRef::round_capacity(uint)
		pop	cx
		les	bx, [bp+@@arg_0]
		mov	es:[bx+8], ax
		mov	ax, es:[bx+8]
		inc	ax
		push	ax		; size
		call	_malloc
		pop	cx
		les	bx, [bp+@@arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short @@strings_1063B
		push	ds
		mov	ax, offset ___xalloc
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

@@strings_1063B:
		push	[bp+@@arg_8]
		push	[bp+@@arg_6]
		push	[bp+n]		; n
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+4] ; src
		push	word ptr es:[bx+2] ; dest
		call	_memcpy
		push	[bp+@@arg_E]
		push	[bp+@@arg_C]
		push	[bp+@@arg_A]	; n
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+2]
		add	ax, [bp+@@arg_8]
		push	word ptr es:[bx+4] ; src
		push	ax		; dest
		call	_memcpy
		add	sp, 14h
		les	bx, [bp+@@arg_0]
		les	bx, es:[bx+2]
		mov	ax, [bp+@@arg_8]
		add	ax, [bp+@@arg_E]
		add	bx, ax
		mov	byte ptr es:[bx], 0

@@strings_10687:
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	dx, word ptr [bp+@@arg_0+2]
		mov	ax, word ptr [bp+@@arg_0]
		pop	di
		pop	si
		pop	bp
		retf
@TStringRef@$bctr$qnxcuit1uiui endp


; int __cdecl __far TStringRef___TStringRef(void *, int, char)
		public @TStringRef@$bdtr$qv
@TStringRef@$bdtr$qv proc far

@@var_1E		= word ptr -1Eh
@@arg_0		= word ptr  6
@@arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	strings_1010F
		mov	bx, offset strings_1010F
		call	___InitExceptBlocks
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, [bp+@@arg_0]
		or	ax, [bp+8]
		jz	short @@strings_106F5
		les	bx, dword ptr [bp+@@arg_0]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2] ; block
		call	_farfree
		pop	cx
		pop	cx
		test	[bp+@@arg_4], 1
		jz	short @@strings_106F5
		push	word ptr [bp+8]
		push	[bp+@@arg_0]	; void *
		call	@$bdele$qnv	; operator delete(void *)
		pop	cx
		pop	cx

@@strings_106F5:
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TStringRef@$bdtr$qv endp


; TStringRef::reserve(unsigned int)
		public @TStringRef@reserve$qui
@TStringRef@reserve$qui	proc far

@@var_20		= word ptr -20h
@@var_1E		= word ptr -1Eh
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	strings_10121
		mov	bx, offset strings_10121
		call	___InitExceptBlocks
		les	bx, [bp+@@arg_0]
		or	word ptr es:[bx+0Ah], 1
		mov	ax, [bp+@@arg_4]
		inc	ax
		push	ax
		nopcall	@TStringRef@round_capacity$qui ; TStringRef::round_capacity(uint)
		pop	cx
		mov	[bp+@@var_20], ax
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+8]
		sub	ax, [bp+@@var_20]
		cmp	ax, ds:@string@freeboard ; string::freeboard
		jbe	short @@strings_10763
		mov	ax, [bp+@@var_20]
		inc	ax
		push	ax
		push	word ptr es:[bx+4] ; size
		push	word ptr es:[bx+2] ; block
		call	_realloc
		add	sp, 6
		les	bx, [bp+@@arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, [bp+@@var_20]
		mov	es:[bx+8], ax

@@strings_10763:
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TStringRef@reserve$qui	endp


; TStringRef::check_freeboard(void)
		public @TStringRef@check_freeboard$qv
@TStringRef@check_freeboard$qv proc far

@@var_20		= word ptr -20h
@@var_1E		= word ptr -1Eh
@@arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	strings_1012B
		mov	bx, offset strings_1012B
		call	___InitExceptBlocks
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+6]
		nopcall	@TStringRef@round_capacity$qui ; TStringRef::round_capacity(uint)
		pop	cx
		mov	[bp+@@var_20], ax
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+8]
		sub	ax, [bp+@@var_20]
		cmp	ax, ds:@string@freeboard ; string::freeboard
		jbe	short @@strings_107CB
		mov	ax, [bp+@@var_20]
		inc	ax
		push	ax
		push	word ptr es:[bx+4] ; size
		push	word ptr es:[bx+2] ; block
		call	_realloc
		add	sp, 6
		les	bx, [bp+@@arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, [bp+@@var_20]
		mov	es:[bx+8], ax

@@strings_107CB:
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TStringRef@check_freeboard$qv endp


; TStringRef::grow_to(unsigned int)
		public @TStringRef@grow_to$qui
@TStringRef@grow_to$qui	proc far

@@var_1E		= word ptr -1Eh
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	strings_1013D
		mov	bx, offset strings_1013D
		call	___InitExceptBlocks
		les	bx, [bp+@@arg_0]
		mov	ax, [bp+@@arg_4]
		mov	es:[bx+8], ax
		mov	ax, es:[bx+8]
		inc	ax
		push	ax
		push	word ptr es:[bx+4] ; size
		push	word ptr es:[bx+2] ; block
		call	_realloc
		add	sp, 6
		les	bx, [bp+@@arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short @@strings_1082D
		push	ds
		mov	ax, offset ___xalloc
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

@@strings_1082D:
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TStringRef@grow_to$qui	endp


; TStringRef::round_capacity(unsigned int)
		public @TStringRef@round_capacity$qui
@TStringRef@round_capacity$qui proc far

@@var_20		= word ptr -20h
@@var_1E		= word ptr -1Eh
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	strings_10147
		mov	bx, offset strings_10147
		call	___InitExceptBlocks
		mov	ax, ds:@string@initial_capac ; string::initial_capac
		mov	[bp+@@var_20], ax
		mov	cx, ds:@string@resize_inc ; string::resize_inc
		mov	ax, [bp+@@arg_0]
		sub	ax, [bp+@@var_20]
		add	ax, cx
		dec	ax
		xor	dx, dx
		div	cx
		imul	cx
		add	ax, [bp+@@var_20]
		push	ax
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	ax
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TStringRef@round_capacity$qui endp


; int __cdecl __far TStringRef__splice(__int32,	int, int, size_t n, int, int)
		public @TStringRef@splice$quiuinxcui
@TStringRef@splice$quiuinxcui proc far

@@var_26		= word ptr -26h
@@var_24		= word ptr -24h
@@src		= word ptr -22h
@@var_1E		= word ptr -1Eh
@@arg_0		= dword	ptr  6
@@arg_4		= word ptr  0Ah
@@arg_6		= word ptr  0Ch
n		= word ptr  0Eh
@@arg_A		= word ptr  10h
@@arg_C		= word ptr  12h

		push	bp
		mov	bp, sp
		sub	sp, 26h
		push	si
		push	di
		mov	ax, seg	strings_10159
		mov	bx, offset strings_10159
		call	___InitExceptBlocks
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+6]
		add	ax, [bp+@@arg_C]
		sub	ax, [bp+@@arg_6]
		mov	[bp+@@var_24], ax
		push	ax
		call	@TStringRef@round_capacity$qui	; TStringRef::round_capacity(uint)
		pop	cx
		mov	[bp+@@var_26], ax
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+8]
		cmp	ax, [bp+@@var_26]
		jnb	short @@strings_108C2
		push	[bp+@@var_26]
		push	word ptr [bp+@@arg_0+2]
		push	bx
		call	@TStringRef@grow_to$qui ; TStringRef::grow_to(uint)
		add	sp, 6
		jmp	short @@strings_10931

@@strings_108C2:
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+8]
		sub	ax, [bp+@@var_26]
		cmp	ax, ds:@string@freeboard ; string::freeboard
		jbe	short @@strings_10931
		test	byte ptr es:[bx+0Ah], 1
		jnz	short @@strings_10931
		mov	ax, [bp+@@var_26]
		inc	ax
		push	ax		; size
		call	_malloc
		pop	cx
		mov	[bp+@@src+2], dx
		mov	[bp+@@src], ax
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short @@strings_10903
		push	ds
		mov	ax, offset ___xalloc
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

@@strings_10903:
		cmp	[bp+@@arg_4], 0
		jz	short @@strings_10925
		push	[bp+@@arg_4]
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2] ; n
		push	[bp+@@src+2]	; src
		push	[bp+@@src]	; dest
		call	_memcpy
		add	sp, 0Ah

@@strings_10925:
		les	bx, [bp+@@arg_0]
		mov	ax, [bp+@@var_26]
		mov	es:[bx+8], ax
		jmp	short @@strings_10942

@@strings_10931:
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		mov	[bp+@@src+2], dx
		mov	[bp+@@src], ax

@@strings_10942:
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		cmp	dx, [bp+@@src+2]
		jnz	short @@strings_1095F
		cmp	ax, [bp+@@src]
		jnz	short @@strings_1095F
		mov	ax, [bp+@@arg_C]
		cmp	ax, [bp+@@arg_6]
		jz	short @@strings_10991

@@strings_1095F:
		les	bx, [bp+@@arg_0]
		mov	ax, es:[bx+6]
		sub	ax, [bp+@@arg_4]
		sub	ax, [bp+@@arg_6]
		push	ax
		mov	ax, es:[bx+2]
		add	ax, [bp+@@arg_4]
		add	ax, [bp+@@arg_6]
		push	word ptr es:[bx+4]
		push	ax		; n
		mov	ax, [bp+@@src]
		add	ax, [bp+@@arg_4]
		add	ax, [bp+@@arg_C]
		push	[bp+@@src+2]	; src
		push	ax		; dest
		call	_memmove
		add	sp, 0Ah

@@strings_10991:
		cmp	[bp+@@arg_C], 0
		jz	short @@strings_109D5
		mov	ax, [bp+n]
		or	ax, [bp+@@arg_A]
		jz	short @@strings_109BC
		push	[bp+@@arg_C]
		push	[bp+@@arg_A]
		push	[bp+n]		; n
		mov	ax, [bp+@@src]
		add	ax, [bp+@@arg_4]
		push	[bp+@@src+2]	; src
		push	ax		; dest
		call	_memmove
		add	sp, 0Ah
		jmp	short @@strings_109D5

@@strings_109BC:
		push	[bp+@@arg_C]
		mov	ax, 20h	; ' '
		push	ax		; n
		mov	ax, [bp+@@src]
		add	ax, [bp+@@arg_4]
		push	[bp+@@src+2]	; c
		push	ax		; s
		call	_memset
		add	sp, 8

@@strings_109D5:
		les	bx, [bp+@@arg_0]
		mov	ax, [bp+@@var_24]
		mov	es:[bx+6], ax
		push	es
		les	ax, dword ptr [bp+@@src]
		mov	dx, es
		pop	es
		add	ax, es:[bx+6]
		mov	bx, ax
		mov	es, dx
		mov	byte ptr es:[bx], 0
		les	bx, [bp+@@arg_0]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		cmp	dx, [bp+@@src+2]
		jnz	short @@strings_10A07
		cmp	ax, [bp+@@src]
		jz	short @@strings_10A2A

@@strings_10A07:
		les	bx, [bp+@@arg_0]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2] ; block
		call	_farfree
		pop	cx
		pop	cx
		les	bx, [bp+@@arg_0]
		mov	dx, [bp+@@src+2]
		mov	ax, [bp+@@src]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax

@@strings_10A2A:
		push	[bp+@@var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TStringRef@splice$quiuinxcui endp


; string::set_case_sensitive(int)
		public @string@set_case_sensitive$qi
@string@set_case_sensitive$qi proc far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ds:@string@case_sensitive ;	string::case_sensitive
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_0]
		mov	ds:@string@case_sensitive, ax ;	string::case_sensitive
		mov	ax, [bp+@@var_2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@set_case_sensitive$qi endp


; string::set_paranoid_check(int)
		public @string@set_paranoid_check$qi
@string@set_paranoid_check$qi proc far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ds:@string@paranoid_check ;	string::paranoid_check
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_0]
		mov	ds:@string@paranoid_check, ax ;	string::paranoid_check
		mov	ax, [bp+@@var_2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@set_paranoid_check$qi endp


; string::skip_whitespace(int)
		public @string@skip_whitespace$qi
@string@skip_whitespace$qi proc	far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ds:@string@skip_white ; string::skip_white
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_0]
		mov	ds:@string@skip_white, ax ; string::skip_white
		mov	ax, [bp+@@var_2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@skip_whitespace$qi endp


; string::initial_capacity(unsigned int)
		public @string@initial_capacity$qui
@string@initial_capacity$qui proc far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ds:@string@initial_capac ; string::initial_capac
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_0]
		mov	ds:@string@initial_capac, ax ; string::initial_capac
		mov	ax, [bp+@@var_2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@initial_capacity$qui endp


; string::resize_increment(unsigned int)
		public @string@resize_increment$qui
@string@resize_increment$qui proc far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ds:@string@resize_inc ; string::resize_inc
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_0]
		mov	ds:@string@resize_inc, ax ; string::resize_inc
		cmp	ds:@string@resize_inc, 0 ; string::resize_inc
		jnz	short @@strings_10ACD
		mov	ds:@string@resize_inc, 1 ; string::resize_inc

@@strings_10ACD:
		mov	ax, [bp+@@var_2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@resize_increment$qui endp


; string::max_waste(unsigned int)
		public @string@max_waste$qui
@string@max_waste$qui proc far

@@var_2		= word ptr -2
@@arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	ax, ds:@string@freeboard ; string::freeboard
		mov	[bp+@@var_2], ax
		mov	ax, [bp+@@arg_0]
		mov	ds:@string@freeboard, ax ; string::freeboard
		mov	ax, [bp+@@var_2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@max_waste$qui endp

strings_10AF3	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h ;	...
		db 0Dh dup(0), 2, 0, 2,	0
		dd strings_10194
		db 5, 0, 4Ah, 0
		db 'string::lengtherror',0
		dd strings_10B83
		db 2 dup(0), 3,	0Dh dup(0)
strings_10B41	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah ;	...
		db 0Dh dup(0), 2, 0, 2,	0
		dd strings_101E1
		dw 5
		dw 3Eh
aXalloc		db 'xalloc',0
		db    0
		dd strings_10B83
		db 2 dup(0), 3,	0Dh dup(0)
strings_10B83	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h ;	...
		db 0Dh dup(0), 1, 0, 1,	0
		dd @xmsg@$bdtr$qv	; xmsg::~xmsg(void)
		dw 5
		dw 34h
		db 'xmsg',0
		dd 0
		dd 0
		dd 0
		db 0
strings_10BBB	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Eh, 0, 32h ;	...
		db 0Dh dup(0), 1, 0, 1,	0
		dd @string@$bdtr$qv	; string::~string(void)
		dw 5
		dw 36h
aString		db 'string',0
		dd 0
		dd 0
		dd 0
		db 0
strings_10BF5	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h ;	...
		db 0Dh dup(0), 2, 0, 2,	0
		dd strings_1022E
		db 5, 0, 4Ah, 0
aStringOutofran	db 'string::outofrange',0
		db 0
		dd strings_10B83
		dw 0
		dw 3
		dd 0
		dd 0
		dd 0
