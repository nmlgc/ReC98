; ReC98 fork of PiLoad. The full list of changes:
; • Added support for ZUN's .GRP files with a 'NZ' signature (lol)
; • Removed the default palette
; • Removed the Pascal entry points (might restore them if other PC-98 homebrew
;   developers actually need them)
; ----------------------------------------------------------------------------

;//////////////////////////////////////////////////////////////////////////////
;
;        Ｐｉ １６色　グラフィック・ローダ	1990	やなぎさわ
;						1991-3	電脳科学研究所/BERO
;
;//////////////////////////////////////////////////////////////////////////////
line	=	1280	;最大横幅
lin	=	4

shl1	macro	reg
	add	reg,reg
	endm
rcl1	macro	reg
	adc	reg,reg
	endm

;	out	cy=bit
get1bit	macro	n
	dec	dh
	jz	gb0&n
gb1&n:	shl1	dl
	endm

bitsub	macro	n
gb0&n:
	mov	dl,[bx]
	inc	bx
	mov	dh,8
;	cmp	bx,buffend
	db	81h,0fbh
gw&n	dw	?
	jnz	gb1&n
	call	fread
	jmp	short	gb1&n
	endm

	.model	small
	.186
coltbl	=	0
PaletteBuff =	100h
x_pos	=	word ptr ds:[130h]
y_pos	=	word ptr ds:[132h]
x_wid	=	word ptr ds:[134h]
y_wid	=	word ptr ds:[136h]
tone	=	byte ptr ds:[138h]
option	=	byte ptr ds:[139h]
tcol	=	byte ptr ds:[13ah]
flg800	=	byte ptr ds:[13bh]
line4	=	word ptr ds:[13ch]
vadr	=	word ptr ds:[13eh]
fhandle	=	word ptr ds:[140h]
bufbgn	=	word ptr ds:[142h]
bufend	=	word ptr ds:[144h]
bufsize	=	word ptr ds:[146h]
yscroll	=	word ptr ds:[148h] ; unused
y_wid2	=	word ptr ds:[14ah]
x_wid2	=	word ptr ds:[14ch]
;bfseg	=	word ptr ds:[14eh]
tonetbl	=	150h
gbuff	=	160h
buffer	=	160h+line*(lin+2)
parasize =	buffer
	.code
	locals
spreg	dw	?
dsseg	dw	?

	public	_PiLoad,_ToneSet
_PiLoad	proc	near
	arg		nam:word,buf,bufsiz,x,y,ton,opt:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,ds
	mov	es,bx
	mov	dx,nam
	mov	ax,buf
	add	ax,15
	shr	ax,4
	add	ax,bx
	mov	ds,ax
	mov	si,bufsiz
	mov	ax,buf
	and	ax,15
	sub	si,ax
	mov	bx,x
	mov	cx,y
	mov	di,ton
	mov	ax,opt
	call	piload0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiLoad	endp

_ToneSet	proc	near
	mov	bx,sp
	push	ds
	push	si
	push	di
	mov	ax,dsseg
	mov	ds,ax
	mov	es,ax
	mov	al,ss:[bx+2]
	mov	tone,al
	call	palset
	pop	di
	pop	si
	pop	ds
	ret
_ToneSet	endp

	public	_PiLoadL,_ToneSetL
_PiLoadL	proc	far
	arg		nam:dword,buf:dword,bufsiz,x,y,ton,opt:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	les	dx,nam
	mov	ax,word ptr buf
	add	ax,15
	shr	ax,4
	add	ax,word ptr buf+2
	mov	ds,ax
	mov	si,bufsiz
	mov	ax,word ptr buf
	and	ax,15
	sub	si,ax
	mov	bx,x
	mov	cx,y
	mov	di,ton
	mov	ax,opt
	call	piload0
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf
_PiLoadL	endp

_ToneSetL	proc	far
	mov	bx,sp
	push	ds
	push	si
	push	di
	mov	ax,dsseg
	mov	ds,ax
	mov	es,ax
	mov	al,ss:[bx+4]
	mov	tone,al
	call	palset
	pop	di
	pop	si
	pop	ds
	retf
_ToneSetL	endp

	public	_PiLoadC
_PiLoadC	proc	near
	arg		nam:dword,buf:dword,bufsiz,x,y,ton,opt:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	les	dx,nam
	mov	ax,word ptr buf
	add	ax,15
	shr	ax,4
	add	ax,word ptr buf+2
	mov	ds,ax
	mov	si,bufsiz
	mov	ax,word ptr buf
	and	ax,15
	sub	si,ax
	mov	bx,x
	mov	cx,y
	mov	di,ton
	mov	ax,opt
	call	piload0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiLoadC	endp


;	in	es:dx	= filename
;		ds:0	= buff
;		si	= size(paragraph)
;		bx	= x
;		cx	= y
;		di	= tone
;		al	= option
;		ah	= tcol
	public	piload0
error0:
	ret
piload0:
	cld
	mov	spreg,sp
	mov	dsseg,ds
	mov	x_pos,bx
	mov	y_pos,cx
	mov	word ptr option,ax
	mov	ax,di
	mov	tone,al

	xor	ax,ax
	mov	flg800,al

	mov	ax,-8
	cmp	si,parasize+18+48
	jb	error0
	mov	ax,si
	sub	ax,parasize
	mov	bufsize,ax
	add	ax,buffer
;	mov	buffend,ax
;	push	cs
;	pop	ds
;	assume	ds:_TEXT
	irp	n,<0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f,g,h,i,j,k,l>
	mov	word ptr gw&n,ax	;自己書換(^^;)
	endm

	push	es
	pop	ds
	call	fopen
	mov	bx,dsseg
	mov	ds,bx
	mov	es,bx
	jc	error
	mov	fhandle,ax
	call	fread
	mov	si,bx
	lodsw
	mov	cx,ax
	mov	ax,-31
	cmp	cx,'iP'	;ID check
	jz	pilop
	cmp	cx,'NZ'
	jz	pilop
error:	ret
pilop:
	test	option,4
	jz	@@lop2
@@lop:
	lodsb
	cmp	al,1ah
	jz	@@lop2
	mov	dl,al
	mov	ah,2
	int	21h
	jmp	short	@@lop
@@lop2:
	lodsb
	or	al,al
	jnz	@@lop2
	lodsb
	mov	bl,al	;palet flag
	lodsw		;ドット比率
	mov	cx,ax
	lodsb
	cmp	al,4	;plane check
	mov	ax,-32
	jnz	error
	test	option,8
	jz	@@skip
	mov	ax,cx
	call	gmode
@@skip:
	add	si,4	;machine code skip
	lodsw
	xchg	ah,al	;dmy
	xor	cx,cx
	mov	dx,cx
	mov	di,ax
	add	di,si
	and	ax,ax
	jz	codee

ccode:
	cmp	si,di
	jz	codee
	lodsb
	cmp	al,1
	jz	code1
	cmp	al,2
	jz	code2
	jmp	short	codee

code1:
	lodsw
	xchg	ah,al
	mov	cx,ax
	lodsw
	xchg	ah,al
	mov	dx,ax
	jmp	short	ccode

code2:
	add	si,3
	lodsb
	test	option,40h
	jnz	ccode
	cmp	tcol,0ffh
	jz	ccode
	mov	tcol,al
	or	option,40h
	jmp	short	ccode

codee:
	mov	si,di
	cmp	x_pos,0
	jge	@@jmp@
	mov	x_pos,cx
@@jmp@:
	cmp	y_pos,0
	jge	@@jmp
	mov	y_pos,dx
@@jmp:

	mov	cx,x_pos
	mov	ax,y_pos
	shr	cx,3
	shl	ax,4
	add	cx,ax
	shl	ax,2
	add	cx,ax
	mov	vadr,cx

	lodsw
	xchg	ah,al
	mov	x_wid,ax

	mov	cx,ax		;自己書換(^^;)
	neg	ax
	mov	line1,ax	;-x_wid
	inc	ax
	mov	line11,ax	;-x_wid+1
	dec	ax
	shl1	ax
	mov	line2,ax	;-x_wid*2
	shl1	cx
	mov	ax,cx
	add	ax,gbuff
	mov	bufbgn,ax
	shl1	cx
	mov	line4,cx
	add	ax,cx
	mov	bufend,ax
	mov	bufend2,ax
	mov	bufend3,ax
	mov	bufend4,ax

	mov	ax,x_pos
	and	ax,7
	add	ax,x_wid
	mov	x_wid2,ax
	mov	cx,ax
	lodsw
	xchg	ah,al
	mov	y_wid,ax
	mov	y_wid2,ax

	test	bl,080h	;palet	check
	jnz	nopalet
	mov	cx,48
	mov	di,PaletteBuff
@@lop1:
	lodsb
	shr	al,4
	stosb
	loop	@@lop1
nopalet:
	mov	bx,si
	test	option,1
	jz	@@skip
	call	palset
@@skip:
	call	maketbl
	mov	dh,1
	mov	di,gbuff
	xor	al,al
	call	color	;ax=col
	mov	cx,x_wid
	rep	stosw
	xor	bp,bp
	jmp	while1

	bitsub	6
	bitsub	7
pos2:
	get1bit	6
	db	0BEh	;mov si,nn
line2	dw	?
	jnc	brk
	get1bit	7
	db	0BEh	;mov si,nn
line11	dw	?
	jnc	brk
	dec	si
	dec	si
	jmp	short	brk


	bitsub	8
	bitsub	9
	bitsub	a
	bitsub	b
bit0:
	movsw
	db	81h,0ffh;cmp di,nn
bufend4	dw	?
	jnz	while1
	call	gtrans
;	jmp	while1
while1:
	get1bit	8
	jc	pos2
	get1bit	9
	db	0BEh	;mov si,nn
line1	dw	?
	jc	brk
	mov	si,-4
	mov	ax,[di-2]
	cmp	ah,al
	jz	pos00
brk:
	cmp	si,bp
	mov	bp,si
	jz	nopres
	add	si,di
bjmp:	get1bit	a
	jnc	bit0
	mov	ax,1
	xor	cx,cx
llop:	inc	cx
	get1bit	b
	jc	llop
bitcx:	get1bit	c
	rcl1	ax
	loop	bitcx
;	call	getnbit
	jc	jmp0
jmp1:
	mov	cx,ax
	db	0B8h	;mov ax,nn
bufend2	dw	?
	sub	ax,di
	shr	ax,1
	cmp	cx,ax
	jae	jmp2
	rep	movsw
	jmp	while1

;	get1bit	c
	bitsub	c

pos00:
	cmp	si,bp
	mov	bp,si
	jz	nopres
	lea	si,[di-2]
	jmp	short	bjmp

nopres:
	mov	al,[di-1]
noplop:	call	color
	stosw
	mov	al,ah
	db	81h,0ffh;cmp di,nn
bufend3	dw	?
	jz	cjmp01
cjmp02:
	get1bit	d
	jc	noplop
	xor	bp,bp
	jmp	while1
cjmp01:	call	gtrans
	jmp	cjmp02

jmp2:
	sub	cx,ax
	xchg	cx,ax
	rep	movsw
	call	gtrans
	sub	si,line4
	jmp	short jmp1

jmp0:
	xor	cx,cx
lop0:
	movsw
	cmp	di,bufend
	loopnz	lop0
	jnz	jmp1
	call	gtrans
	sub	si,line4
	jcxz	jmp1
	jmp	short	lop0

	bitsub	d

	bitsub	e
	bitsub	0
	bitsub	1
	bitsub	2
	bitsub	3
	bitsub	4

bit01:
	get1bit	e
	jc	@@jmp
	lodsb
	jmp	short color2
@@jmp:
	mov	ax,[si]
	xchg	ah,al
	mov	[si],ax
	xor	ah,ah
	jmp	short color2

;	in	al=color
;	out	al,ah=color
color:
	mov	bp,di
	xor	ah,ah
	mov	si,ax
;	add	si,coltbl

	get1bit	0
	jc	bit01
	get1bit	1
	mov	cx,1
	jnc	bit1
	get1bit	2
	jnc	bit2
	get1bit	3
	rcl1	cx
bit2:	get1bit	4
	rcl1	cx
bit1:	get1bit	5
	rcl1	cx
	add	si,cx
	std
	lodsb
	lea	di,[si+1]
	rep	movsb
	stosb
	jmp	short	color2

	bitsub	5
	bitsub	g

color2:
	xor	ah,ah
	mov	si,ax
;	add	si,coltbl

	get1bit	g
	jc	@bit01
	get1bit	h
	mov	cx,1
	jnc	@bit1
	get1bit	i
	jnc	@bit2
	get1bit	j
	rcl1	cx
@bit2:	get1bit	k
	rcl1	cx
@bit1:	get1bit	l
	rcl1	cx
	add	si,cx
	std
	mov	ah,al
	lodsb
	lea	di,[si+1]
	rep	movsb
	stosb
	xchg	ah,al
	mov	di,bp
	cld
	ret

@bit01:
	get1bit	f
	jc	@@jmp
	mov	ah,[si]
	mov	di,bp
	cld
	ret
@@jmp:
	mov	cx,[si]
	xchg	ch,cl
	mov	[si],cx
	mov	ah,cl
	mov	di,bp
	cld
	ret

	bitsub	h
	bitsub	i
	bitsub	j
	bitsub	k
	bitsub	l
	bitsub	f

maketbl:
;	mov	di,coltbl
	xor	di,di
	mov	ax,1000h
@@lop1:	mov	cx,16
@@lop2:	;and	al,0f0h
	stosb
	sub	al,10h
	loop	@@lop2
	add	al,10h
	dec	ah
	jnz	@@lop1
	ret

;-----------------------------------------------------------------------------
;	ＭＳ－ＤＯＳ依存部
;-----------------------------------------------------------------------------
fopen:
	mov	ax,3d00h
	int	21h
	ret

fread:
	push	ax
	push	cx
	push	dx
	mov	bx,fhandle
	mov	dx,buffer
	push	dx
	mov	cx,bufsize
	mov	ah,3fh
	int	21h
	jc	@err
	pop	bx
	pop	dx
	pop	cx
	pop	ax
	ret

@err:
	call	fclose
	mov	sp,spreg
	ret

fclose:
	mov	bx,fhandle
	mov	ah,3eh
	int	21h
	ret

;-----------------------------------------------------------------------------
;	９８依存部
;-----------------------------------------------------------------------------

;	画面モード設定
;	in	ax=ドット比率データ
gmode:
	cmp	ax,102h
	jz	@@next
;	or	ax,ax
;	mov	ax,-32
;	jnz	error
	mov	ch,0c0h
	mov	ah,42h
	int	18h
	mov	ah,40h
	int	18h
	mov	al,1
	out	6ah,al
	ret
@@next:
	mov	ch,080h
	mov	ah,42h
	int	18h
	mov	al,8
	out	68h,al
	mov	ah,40h
	int	18h
	mov	al,1
	out	6ah,al
	or	flg800,4
	ret


;	gbuffからlinライン分表示(gbuff->VRAM)
gtrans:
	pusha
	push	es
	cmp	vadr,32000
	jl	@@skip
	sub	vadr,32000
	or	flg800,1
	mov	al,1
	out	0a6h,al
;	out	0a4h,al
@@skip:

disp:
	mov	si,bufend
	mov	di,gbuff
	mov	cx,x_wid
	sub	si,cx
	sub	si,cx
	rep	movsw
	mov	si,di
	mov	cx,lin
ylop:
	push	cx
	mov	di,vadr
	mov	ax,x_pos
	and	ax,7
	jz	@@skip
	mov	cx,8
	sub	cx,ax
	push	cx
	mov	ah,0ffh
	shl	ah,cl
	not	al
	xor	bx,bx
	mov	dx,bx
@@lop:
	lodsb
	shl1	al
	rcl1	bl
	shl1	al
	rcl1	bh
	shl1	al
	rcl1	dl
	shl1	al
	rcl1	dh
	loop	@@lop
	mov	cx,0a800h
	mov	es,cx

	mov	al,0c0h
	out	7ch,al
	mov	al,dh
	out	7eh,al
	mov	al,dl
	out	7eh,al
	mov	al,bh
	out	7eh,al
	mov	al,bl
	out	7eh,al
	mov	al,ah
	test	option,40h
	jz	@@skip0
	mov	ah,tcol
	shr	ah,1
	jnc	@@jmp1
	not	dh
@@jmp1:
	shr	ah,1
	jnc	@@jmp2
	not	dl
@@jmp2:
	shr	ah,1
	jnc	@@jmp3
	not	bh
@@jmp3:
	shr	ah,1
	jnc	@@jmp4
	not	bl
@@jmp4:
	or	bx,dx
	or	bl,bh
	or	al,bl
@@skip0:
	stosb
	xor	al,al
	out	7ch,al

	pop	ax
	mov	cx,x_wid
	sub	cx,ax
	shr	cx,3
	jmp	short	xlop
@@skip:
	mov	cx,x_wid
	shr	cx,3
xlop:
	rept	4
	lodsw
	shl1	al
	rcl1	bl
	shl1	ah
	rcl1	bl
	shl1	al
	rcl1	bh
	shl1	ah
	rcl1	bh
	shl1	al
	rcl1	dl
	shl1	ah
	rcl1	dl
	shl1	al
	rcl1	dh
	shl1	ah
	rcl1	dh
	endm
	mov	ax,0a800h
	mov	es,ax

	test	option,40h
	jnz	@@jmp0
	mov	es:[di],dh
	mov	es:[di+8000h],dl
	mov	ah,0b8h
	mov	es,ax
	mov	es:[di],bh
	mov	ah,0e0h
	mov	es,ax
	mov	al,bl
	stosb
	dec	cx
	jz	xend
	jmp	xlop
@@jmp0:
	mov	ah,tcol
	mov	al,0c0h
	out	7ch,al
	mov	al,dh
	out	7eh,al
	mov	al,dl
	out	7eh,al
	mov	al,bh
	out	7eh,al
	mov	al,bl
	out	7eh,al

	shr	ah,1
	jnc	@@jmp1
	not	dh
@@jmp1:
	shr	ah,1
	jnc	@@jmp2
	not	dl
@@jmp2:
	shr	ah,1
	jnc	@@jmp3
	not	bh
@@jmp3:
	shr	ah,1
	jnc	@@jmp4
	not	bl
@@jmp4:
	mov	ax,dx
	or	ax,bx
	or	al,ah
	stosb
	dec	cx
	jz	xend
	jmp	xlop

xend:
	xor	al,al
	out	7ch,al
	mov	cx,x_wid2
	and	cx,7
	jz	ext
	mov	ah,8
	sub	ah,cl
	xor	bx,bx
	mov	dx,bx
@@lop:
	lodsb
	shl1	al
	rcl1	bl
	shl1	al
	rcl1	bh
	shl1	al
	rcl1	dl
	shl1	al
	rcl1	dh
	loop	@@lop
	mov	cl,ah
	mov	ch,0ffh
	shl	ch,cl
	shl	bx,cl
	shl	dx,cl
	mov	ax,0a800h
	mov	es,ax

	mov	al,0c0h
	out	7ch,al
	mov	al,dh
	out	7eh,al
	mov	al,dl
	out	7eh,al
	mov	al,bh
	out	7eh,al
	mov	al,bl
	out	7eh,al
	mov	al,ch
	test	option,40h
	jz	@@skip0
	mov	ah,tcol
	shr	ah,1
	jnc	@@jmp1
	not	dh
@@jmp1:
	shr	ah,1
	jnc	@@jmp2
	not	dl
@@jmp2:
	shr	ah,1
	jnc	@@jmp3
	not	bh
@@jmp3:
	shr	ah,1
	jnc	@@jmp4
	not	bl
@@jmp4:
	or	bx,dx
	or	bl,bh
	or	al,bl
@@skip0:
	stosb
	xor	al,al
	out	7ch,al

ext:
	pop	cx
	add	vadr,80
	dec	y_wid2
	jz	fin
	dec	cx
	jz	ext2
	jmp	ylop
ext2:
	pop	es
	popa
	mov	di,bufbgn
	ret
fin:
	test	flg800,1
	jle	@@jmp
	mov	al,0
;	out	0a4h,al
	out	0a6h,al
	and	flg800,not 2
@@jmp:
	call	fclose
	mov	sp,spreg
	xor	ax,ax
	ret

;	パレット設定

;	in	al=tone	[PaletteBuff]=palet

mul38	dw	0,38,76,114,152,190,228,266,304,342,380,418,456,494,532,570
mul75	dw	0,75,150,225,300,375,450,525,600,675,750,825,900,975,1050,1125
mul15	dw	0,15,30,45,60,75,90,105,120,135,150,165,180,195,210,225
palset:
	push	bx
	mov	bl,tone
	mov	bh,100
	mov	di,tonetbl
	xor	cx,cx
@@plop:
	mov	al,cl
	mul	bl
	div	bh
	stosb
	inc	cl
	cmp	cl,16
	jnz	@@plop

	mov	si,PaletteBuff
	mov	bx,tonetbl
	mov	cx,16
	xor	ah,ah
	test	option,16
	jnz	@@lop2
@@lop:				;通常
	mov	al,ah
	out	0a8h,al	;palet	no
	lodsb
	xlat	[bx]
	out	0ach,al	;red
	lodsb
	xlat	[bx]
	out	0aah,al	;green
	lodsb
	xlat	[bx]
	out	0aeh,al	;blue
	inc	ah
	loop	@@lop
	pop	bx
	ret
@@lop2:				;NOTE用
	mov	al,16
	sub	al,cl
	out	0a8h,al	;palet	no
	mov	dx,64
	lodsb
	shl1	al
	mov	di,ax
	add	dx,mul38[di]
	lodsb
	shl1	al
	mov	di,ax
	add	dx,mul75[di]
	lodsb
	shl1	al
	mov	di,ax
	add	dx,mul15[di]
	mov	al,7
	sub	al,dh
	xlat	[bx]
	mov	dl,al
	irp	port,<0aeh,0ach,0aah>
	shr	dl,1
	sbb	al,al
	out	port,al
	endm
	loop	@@lop2
	pop	bx
	ret

	end

