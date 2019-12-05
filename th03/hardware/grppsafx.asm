; (identical to the already decompiled TH02 version, except that it now uses
; Pascal calling convention and clamps the color parameter to the 0~15 range.)

public GRAPH_PUTSA_FX
graph_putsa_fx	proc far
@@glyph		= byte ptr -32h
var_12		= word ptr -12h
@@spacing	= word ptr -10h
@@weight	= word ptr -0Eh
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= dword	ptr -8
var_4		= word ptr -4
var_2		= word ptr -2

if GAME eq 2
@@x  	= word ptr  6
@@y  	= word ptr  8
@@fx 	= word ptr  0Ah
@@str	= dword	ptr  0Ch
else
@@str	= dword	ptr  6
@@fx 	= word ptr  0Ah
@@y  	= word ptr  0Ch
@@x  	= word ptr  0Eh
endif
	enter	32h, 0
	push	si
	push	di
	mov	di, [bp+@@x]
	mov	ax, [bp+@@fx]
	sar	ax, 4
	and	ax, 3
	mov	[bp+@@weight], ax
	mov	ax, [bp+@@fx]
	sar	ax, 6
	and	ax, 7
	mov	[bp+@@spacing], ax
	push	GC_RMW
	mov	ax, [bp+@@fx]
if GAME eq 3
	and	ax, 0Fh
	push	ax
endif
	call	grcg_setcolor
	mov	dx, 68h	; 'h'
	mov	al, 0Bh
	out	dx, al
	jmp	loc_AD92
; ---------------------------------------------------------------------------

loc_AB82:
	mov	ax, [bp+@@y]
	imul	ax, 50h
	push	ax
	mov	ax, di
	mov	bx, 8
	cwd
	idiv	bx
	pop	dx
	add	dx, ax
	mov	word ptr [bp+var_8+2], 0A800h
	mov	word ptr [bp+var_8], dx
	mov	ax, di
	cwd
	idiv	bx
	mov	[bp+var_C], dx
	les	bx, [bp+@@str]
if GAME eq 3
	assume es:nothing
endif
	mov	al, es:[bx]
	mov	ah, 0
	mov	bx, ax
	test	__mbctype+1[bx], 4
	jz	short loc_ABD7
	mov	bx, word ptr [bp+@@str]
	mov	al, es:[bx]
	cbw
	shl	ax, 8
	mov	dl, es:[bx+1]
	mov	dh, 0
	add	ax, dx
	push	ax
	call	__mbcjmstojis
	pop	cx
	mov	[bp+var_2], ax
	add	word ptr [bp+@@str], 2
	jmp	short loc_AC1D
; ---------------------------------------------------------------------------

loc_ABD7:
	les	bx, [bp+@@str]
	mov	al, es:[bx]
	mov	ah, 0
	mov	bx, ax
	test	__mbctype+1[bx], 3
	jz	short loc_ABF5
	mov	bx, word ptr [bp+@@str]
	mov	al, es:[bx]
	mov	ah, 0
	add	ax, 2980h
	jmp	short loc_AC10
; ---------------------------------------------------------------------------

loc_ABF5:
	les	bx, [bp+@@str]
	mov	al, es:[bx]
	cbw
	mov	bx, ax
	test	byte ptr __ctype+1[bx], 5Eh
	jz	short loc_AC15_
	mov	bx, word ptr [bp+@@str]
	mov	al, es:[bx]
	mov	ah, 0
	add	ax, 2900h

loc_AC10:
	mov	[bp+var_2], ax
	jmp	short loc_AC1A_
; ---------------------------------------------------------------------------

loc_AC15_:
	mov	[bp+var_2], 2B21h

loc_AC1A_:
	inc	word ptr [bp+@@str]

loc_AC1D:
	mov	al, byte ptr [bp+var_2]
	and	al, 0FFh
	mov	dx, 0A1h
	out	dx, al
	mov	ax, [bp+var_2]
	shr	ax, 8
	sub	al, 20h	; ' '
	mov	dx, 0A3h
	out	dx, al
	cmp	[bp+var_2], 2921h
	jb	short loc_AC7E
	cmp	[bp+var_2], 2B7Eh
	ja	short loc_AC7E
	cmp	di, 278h
	jg	loc_AD9D
	mov	[bp+var_12], 0
	jmp	short loc_AC71
; ---------------------------------------------------------------------------

loc_AC4F:
	mov	al, byte ptr [bp+var_12]
	or	al, 20h
	mov	dx, 0A5h
	out	dx, al
	mov	dx, 0A9h
	in	al, dx
	mov	ah, 0
	shl	ax, 8
	mov	bx, [bp+var_12]
	add	bx, bx
	lea	dx, [bp+@@glyph]
	add	bx, dx
	mov	ss:[bx], ax
	inc	[bp+var_12]

loc_AC71:
	cmp	[bp+var_12], 10h
	jl	short loc_AC4F
	mov	[bp+var_A], 0
	jmp	short loc_ACD4
; ---------------------------------------------------------------------------

loc_AC7E:
	cmp	di, 270h
	jg	loc_AD9D
	mov	[bp+var_12], 0
	jmp	short loc_ACC9
; ---------------------------------------------------------------------------

loc_AC8D:
	mov	al, byte ptr [bp+var_12]
	or	al, 20h
	mov	dx, 0A5h
	out	dx, al
	mov	dx, 0A9h
	in	al, dx
	mov	ah, 0
	shl	ax, 8
	mov	bx, [bp+var_12]
	add	bx, bx
	lea	dx, [bp+@@glyph]
	add	bx, dx
	mov	ss:[bx], ax
	mov	dx, 0A5h
	mov	al, byte ptr [bp+var_12]
	out	dx, al
	mov	dx, 0A9h
	in	al, dx
	mov	ah, 0
	mov	bx, [bp+var_12]
	add	bx, bx
	lea	dx, [bp+@@glyph]
	add	bx, dx
	add	ss:[bx], ax
	inc	[bp+var_12]

loc_ACC9:
	cmp	[bp+var_12], 10h
	jl	short loc_AC8D
	mov	[bp+var_A], 1

loc_ACD4:
	mov	[bp+var_12], 0
	jmp	loc_AD79
; ---------------------------------------------------------------------------

loc_ACDC:
	mov	bx, [bp+var_12]
	add	bx, bx
	lea	ax, [bp+@@glyph]
	add	bx, ax
	mov	ax, ss:[bx]
	mov	[bp+var_4], ax
	mov	ax, [bp+@@weight]
	cmp	ax, 1
	jz	short loc_AD00
	cmp	ax, 2
	jz	short loc_AD16
	cmp	ax, 3
	jz	short loc_AD0C
	jmp	short loc_AD2C
; ---------------------------------------------------------------------------

loc_AD00:
	mov	si, [bp+var_4]
	mov	ax, si
	add	ax, ax
	or	[bp+var_4], ax
	jmp	short loc_AD2C
; ---------------------------------------------------------------------------

loc_AD0C:
	mov	si, [bp+var_4]
	mov	ax, si
	add	ax, ax
	or	[bp+var_4], ax

loc_AD16:
	mov	si, [bp+var_4]
	mov	ax, si
	add	ax, ax
	or	[bp+var_4], ax
	xor	si, [bp+var_4]
	mov	ax, si
	add	ax, ax
	not	ax
	and	[bp+var_4], ax

loc_AD2C:
	cmp	[bp+var_C], 0
	jz	short loc_AD5F
	mov	cl, byte ptr [bp+var_C]
	add	cl, 8
	mov	ax, [bp+var_4]
	shr	ax, cl
	les	bx, [bp+var_8]
	mov	es:[bx], al
	mov	ax, [bp+var_4]
	mov	cl, byte ptr [bp+var_C]
	shr	ax, cl
	mov	es:[bx+1], al
	mov	cl, 8
	sub	cl, byte ptr [bp+var_C]
	mov	al, byte ptr [bp+var_4]
	shl	al, cl
	mov	es:[bx+2], al
	jmp	short loc_AD72
; ---------------------------------------------------------------------------

loc_AD5F:
	mov	ax, [bp+var_4]
	shr	ax, 8
	les	bx, [bp+var_8]
	mov	es:[bx], al
	mov	al, byte ptr [bp+var_4]
	mov	es:[bx+1], al

loc_AD72:
	add	word ptr [bp+var_8], 50h ; 'P'
	inc	[bp+var_12]

loc_AD79:
	cmp	[bp+var_12], 10h
	jl	loc_ACDC
	cmp	[bp+var_A], 0
	jz	short loc_AD8A
	add	di, 8

loc_AD8A:
	mov	ax, [bp+@@spacing]
	add	ax, 8
	add	di, ax

loc_AD92:
	les	bx, [bp+@@str]
	cmp	byte ptr es:[bx], 0
	jnz	loc_AB82

loc_AD9D:
	mov	dx, 68h	; 'h'
	mov	al, 0Ah
	out	dx, al
	call	grcg_off
	pop	di
	pop	si
	leave
if GAME eq 2
	retf
else
	retf	0Ah
endif
graph_putsa_fx	endp
