; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of the segment declarations (for obvious reasons)
; * no segment prefixes in the constant macros (and instead on every single
;   reference to them), as TASM somehow parses these as duplicated definitions
;   (???), resulting in a "symbol already defined elsewhere" error
; * the "piloadc_" prefix on constants
; * the @@ prefix on function parameters
; * unique label names to make up for JWasm's lack of support for truly block-
;   scoped symbols
; * "rep segcs movsw" being spelled out to what it's actually supposed to mean
;   (movs word ptr es:[di], word ptr cs:[si])
; * the ID check being changed from 'iP' to 'NZ' (lol ZUN)
; * word alignment at the end of the file

;//////////////////////////////////////////////////////////////////////////////
;
;        Ｐｉ １６色　グラフィック・ローダ	1990	やなぎさわ
;						1991-3	電脳科学研究所/BERO
;
;//////////////////////////////////////////////////////////////////////////////
line	=	1280	;最大横幅
lin	=	4
comment	|
Ｃからの利用
 int	PiLoad(char *name,int buff,int Size,int X,int Y,int tone,int option)

PASCALからの利用
 functuon PiLoad( name:string; buff,Size,X,Y,tone,option:integer):integer;

Assemblerからの利用
 piload0 proc near
	es:dx	= name(asciz)
	ds:0	= buff
	si	= size
	bx	= x
	cx	= y
	al	= tone
	ah	= option

 引数
	name	ファイル名
	buff	バッファのセグメント
	Size	バッファのサイズ
	X	表示アドレスのＸ座標
	Y	表示アドレスのＹ座標
	tone	トーン（１～１００％）
	option	オプション（下記のビットで指定）通常は15(01111b)
	   (lsb)0 .. パレット設定	する／しない = 1/0
	   	1 .. 常駐パレット設定	する／しない = 1/0
		2 .. コメント表示	する／しない = 1/0
		3 .. 画面設定		する／しない = 1/0
		     (VRAMのON,400/200line設定)
		4 .. ノート用パレット	する／しない = 1/0
		5 .. スクロールロード	する／しない = 1/0
		6 .. 透明色利用		する／しない = 1/0

 戻り値
	  0	正常終了
	 -8	バッファが足りない
	-31	Piではない
	-32	サポートされていない
	他	エラー（ＭＳＤＯＳのＤＯＳコールエラー参照)

|

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

piloadc_coltbl	=	0
piloadc_PaletteBuff =	100h
piloadc_x_pos	=	word ptr [130h]
piloadc_y_pos	=	word ptr [132h]
piloadc_x_wid	=	word ptr [134h]
piloadc_y_wid	=	word ptr [136h]
piloadc_tone	=	byte ptr [138h]
piloadc_option	=	byte ptr [139h]
piloadc_tcol	=	byte ptr [13ah]
piloadc_flg800	=	byte ptr [13bh]
piloadc_line4	=	word ptr [13ch]
piloadc_vadr	=	word ptr [13eh]
piloadc_fhandle	=	word ptr [140h]
piloadc_bufbgn	=	word ptr [142h]
piloadc_bufend	=	word ptr [144h]
piloadc_bufsize	=	word ptr [146h]
piloadc_yscroll	=	word ptr [148h]
piloadc_y_wid2	=	word ptr [14ah]
piloadc_x_wid2	=	word ptr [14ch]
;piloadc_bfseg	=	word ptr [14eh]
piloadc_tonetbl	=	150h
piloadc_gbuff	=	160h
piloadc_buffer	=	160h+line*(lin+2)
piloadc_parasize =	piloadc_buffer

	locals
dftpal	db	0,0,0,	0,0,07h,	7h,0,0,		7h,0,7h
	db	0,7h,0,	0,7h,7h,	7h,7h,0,	7h,7h,7h
	db	0,0,0,	0,0,0fh,	0fh,0,0,	0fh,0,0fh
	db	0,0fh,0,0,0fh,0fh,	0fh,0fh,0,	0fh,0fh,0fh
spreg	dw	?
dsseg	dw	?

	public	PiLoad,ToneSet
PiLoad	proc	near
@@opt	=	word ptr 4
@@ton	=	word ptr 6
@@y	=	word ptr 8
@@x	=	word ptr 10
@@bufsiz	=	word ptr 12
@@buf	=	dword ptr 14
@@nam	=	dword ptr 18
	push	bp
	mov	bp,sp
	push	ds
	lds	dx,[bp+@@nam]
	mov	ax,word ptr [bp+@@buf]
	add	ax,15
	shr	ax,4
	add	ax,word ptr [bp+@@buf+2]
	mov	es,ax
	cld
	mov	si,dx
	xor	dx,dx
	mov	di,dx
	lodsb
	xor	ch,ch
	mov	cl,al
	rep	movsb
	xor	al,al
	stosb
	push	es
	pop	ds
	mov	si,[bp+@@bufsiz]
	mov	ax,word ptr [bp+@@buf]
	and	ax,15
	sub	si,ax
	mov	bx,[bp+@@x]
	mov	cx,[bp+@@y]
	mov	di,[bp+@@ton]
	mov	ax,[bp+@@opt]
	call	piload0
	pop	ds
	pop	bp
	ret	16
PiLoad	endp

ToneSet	proc	near
	mov	bx,sp
	push	ds
	mov	ax,dsseg
	mov	ds,ax
	mov	es,ax
	mov	al,ss:[bx+2]
	mov	ds:piloadc_tone,al
	call	palset
	pop	ds
	ret	2
ToneSet	endp

	public	_PiLoad,_ToneSet
_PiLoad	proc	near
	arg		@@nam:word,@@buf,@@bufsiz,@@x,@@y,@@ton,@@opt:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,ds
	mov	es,bx
	mov	dx,@@nam
	mov	ax,@@buf
	add	ax,15
	shr	ax,4
	add	ax,bx
	mov	ds,ax
	mov	si,@@bufsiz
	mov	ax,@@buf
	and	ax,15
	sub	si,ax
	mov	bx,@@x
	mov	cx,@@y
	mov	di,@@ton
	mov	ax,@@opt
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
	mov	ds:piloadc_tone,al
	call	palset
	pop	di
	pop	si
	pop	ds
	ret
_ToneSet	endp

	public	_PiLoadL,_ToneSetL
_PiLoadL	proc	far
	arg		@@nam:dword,@@buf:dword,@@bufsiz,@@x,@@y,@@ton,@@opt:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	les	dx,@@nam
	mov	ax,word ptr @@buf
	add	ax,15
	shr	ax,4
	add	ax,word ptr @@buf+2
	mov	ds,ax
	mov	si,@@bufsiz
	mov	ax,word ptr @@buf
	and	ax,15
	sub	si,ax
	mov	bx,@@x
	mov	cx,@@y
	mov	di,@@ton
	mov	ax,@@opt
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
	mov	ds:piloadc_tone,al
	call	palset
	pop	di
	pop	si
	pop	ds
	retf
_ToneSetL	endp

	public	_PiLoadC
_PiLoadC	proc	near
	arg		@@nam:dword,@@buf:dword,@@bufsiz,@@x,@@y,@@ton,@@opt:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	les	dx,@@nam
	mov	ax,word ptr @@buf
	add	ax,15
	shr	ax,4
	add	ax,word ptr @@buf+2
	mov	ds,ax
	mov	si,@@bufsiz
	mov	ax,word ptr @@buf
	and	ax,15
	sub	si,ax
	mov	bx,@@x
	mov	cx,@@y
	mov	di,@@ton
	mov	ax,@@opt
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
	mov	ds:piloadc_x_pos,bx
	mov	ds:piloadc_y_pos,cx
	mov	word ptr ds:piloadc_option,ax
	mov	ax,di
	mov	ds:piloadc_tone,al

	xor	ax,ax
	mov	ds:piloadc_flg800,al

	mov	ax,-8
	cmp	si,piloadc_parasize+18+48
	jb	error0
	mov	ax,si
	sub	ax,piloadc_parasize
	mov	ds:piloadc_bufsize,ax
	add	ax,piloadc_buffer
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
	mov	ds:piloadc_fhandle,ax
	call	fread
	mov	si,bx
	lodsw
	cmp	ax,'NZ'	;ID check
	mov	ax,-31
	jz	pilop
error:	ret
pilop:
	test	ds:piloadc_option,4
	jz	pilop_lop2
pilop_lop:
	lodsb
	cmp	al,1ah
	jz	pilop_lop2
	mov	dl,al
	mov	ah,2
	int	21h
	jmp	short	pilop_lop
pilop_lop2:
	lodsb
	or	al,al
	jnz	pilop_lop2
	lodsb
	mov	bl,al	;palet flag
	lodsw		;ドット比率
	mov	cx,ax
	lodsb
	cmp	al,4	;plane check
	mov	ax,-32
	jnz	error
	test	ds:piloadc_option,8
	jz	pilop_skip
	mov	ax,cx
	call	gmode
pilop_skip:
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
	test	ds:piloadc_option,40h
	jnz	ccode
	cmp	ds:piloadc_tcol,0ffh
	jz	ccode
	mov	ds:piloadc_tcol,al
	or	ds:piloadc_option,40h
	jmp	short	ccode

codee:
	mov	si,di
	cmp	ds:piloadc_x_pos,0
	jge	codee_jmp@
	mov	ds:piloadc_x_pos,cx
codee_jmp@:
	cmp	ds:piloadc_y_pos,0
	jge	codee_jmp
	mov	ds:piloadc_y_pos,dx
codee_jmp:

	mov	cx,ds:piloadc_x_pos
	mov	ax,ds:piloadc_y_pos
	shr	cx,3
	shl	ax,4
	add	cx,ax
	shl	ax,2
	add	cx,ax
	mov	ds:piloadc_vadr,cx

	lodsw
	xchg	ah,al
	mov	ds:piloadc_x_wid,ax

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
	add	ax,piloadc_gbuff
	mov	ds:piloadc_bufbgn,ax
	shl1	cx
	mov	ds:piloadc_line4,cx
	add	ax,cx
	mov	ds:piloadc_bufend,ax
	mov	bufend2,ax
	mov	bufend3,ax
	mov	bufend4,ax

	mov	ax,ds:piloadc_x_pos
	and	ax,7
	add	ax,ds:piloadc_x_wid
	mov	ds:piloadc_x_wid2,ax
	mov	cx,ax
	lodsw
	xchg	ah,al
	mov	ds:piloadc_y_wid,ax
	mov	ds:piloadc_y_wid2,ax

	test	bl,080h	;palet	check
	jnz	nopalet
	mov	cx,48
	mov	di,piloadc_PaletteBuff
codee_lop1:
	lodsb
	shr	al,4
	stosb
	loop	codee_lop1
	mov	bx,si
	jmp	short	palend
nopalet:
	mov	bx,si
	mov	si,offset dftpal
	mov	di,piloadc_PaletteBuff
	mov	cx,12
	rep	movs word ptr es:[di], word ptr cs:[si]
palend:
	test	ds:piloadc_option,1
	jz	palend_skip
	call	palset
palend_skip:
	call	maketbl
	mov	dh,1
	mov	di,piloadc_gbuff
	xor	al,al
	call	color	;ax=col
	mov	cx,ds:piloadc_x_wid
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
	sub	si,ds:piloadc_line4
	jmp	short jmp1

jmp0:
	xor	cx,cx
lop0:
	movsw
	cmp	di,ds:piloadc_bufend
	loopnz	lop0
	jnz	jmp1
	call	gtrans
	sub	si,ds:piloadc_line4
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
	jc	bit01_jmp
	lodsb
	jmp	short color2
bit01_jmp:
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
;	add	si,piloadc_coltbl

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
;	add	si,piloadc_coltbl

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
	jc	@bit01_jmp
	mov	ah,[si]
	mov	di,bp
	cld
	ret
@bit01_jmp:
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
;	mov	di,piloadc_coltbl
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
comment	;
	push	si
	push	dx
	mov	si,dx
flop:	lodsb
	mov	dl,al
	mov	ah,2
	int	21h
	or	dl,dl
	jnz	flop
	pop	dx
	pop	si
;
	mov	ax,3d00h
	int	21h
	ret

fread:
	push	ax
	push	cx
	push	dx
	mov	bx,ds:piloadc_fhandle
	mov	dx,piloadc_buffer
	push	dx
	mov	cx,ds:piloadc_bufsize
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
	mov	bx,ds:piloadc_fhandle
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
	jz	gmode_next
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
gmode_next:
	mov	ch,080h
	mov	ah,42h
	int	18h
	mov	al,8
	out	68h,al
	mov	ah,40h
	int	18h
	mov	al,1
	out	6ah,al
	or	ds:piloadc_flg800,4
	ret


;	gbuffからlinライン分表示(gbuff->VRAM)
gtrans:
	pusha
	push	es
	cmp	ds:piloadc_vadr,32000
	jl	gtrans_skip
	sub	ds:piloadc_vadr,32000
	or	ds:piloadc_flg800,1
	mov	al,1
	out	0a6h,al
;	out	0a4h,al
gtrans_skip:

disp:
	mov	si,ds:piloadc_bufend
	mov	di,piloadc_gbuff
	mov	cx,ds:piloadc_x_wid
	sub	si,cx
	sub	si,cx
	rep	movsw
	mov	si,di
	mov	cx,lin
ylop:
	push	cx
	mov	di,ds:piloadc_vadr
	mov	ax,ds:piloadc_x_pos
	and	ax,7
	jz	ylop_skip
	mov	cx,8
	sub	cx,ax
	push	cx
	mov	ah,0ffh
	shl	ah,cl
	not	al
	xor	bx,bx
	mov	dx,bx
ylop_lop:
	lodsb
	shl1	al
	rcl1	bl
	shl1	al
	rcl1	bh
	shl1	al
	rcl1	dl
	shl1	al
	rcl1	dh
	loop	ylop_lop
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
	test	ds:piloadc_option,40h
	jz	ylop_skip0
	mov	ah,ds:piloadc_tcol
	shr	ah,1
	jnc	ylop_jmp1
	not	dh
ylop_jmp1:
	shr	ah,1
	jnc	ylop_jmp2
	not	dl
ylop_jmp2:
	shr	ah,1
	jnc	ylop_jmp3
	not	bh
ylop_jmp3:
	shr	ah,1
	jnc	ylop_jmp4
	not	bl
ylop_jmp4:
	or	bx,dx
	or	bl,bh
	or	al,bl
ylop_skip0:
	stosb
	xor	al,al
	out	7ch,al

	pop	ax
	mov	cx,ds:piloadc_x_wid
	sub	cx,ax
	shr	cx,3
	jmp	short	xlop
ylop_skip:
	mov	cx,ds:piloadc_x_wid
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

	test	ds:piloadc_option,40h
	jnz	xlop_jmp0
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
xlop_jmp0:
	mov	ah,ds:piloadc_tcol
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
	jnc	xlop_jmp1
	not	dh
xlop_jmp1:
	shr	ah,1
	jnc	xlop_jmp2
	not	dl
xlop_jmp2:
	shr	ah,1
	jnc	xlop_jmp3
	not	bh
xlop_jmp3:
	shr	ah,1
	jnc	xlop_jmp4
	not	bl
xlop_jmp4:
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
	mov	cx,ds:piloadc_x_wid2
	and	cx,7
	jz	ext
	mov	ah,8
	sub	ah,cl
	xor	bx,bx
	mov	dx,bx
xend_lop:
	lodsb
	shl1	al
	rcl1	bl
	shl1	al
	rcl1	bh
	shl1	al
	rcl1	dl
	shl1	al
	rcl1	dh
	loop	xend_lop
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
	test	ds:piloadc_option,40h
	jz	xend_skip0
	mov	ah,ds:piloadc_tcol
	shr	ah,1
	jnc	xend_jmp1
	not	dh
xend_jmp1:
	shr	ah,1
	jnc	xend_jmp2
	not	dl
xend_jmp2:
	shr	ah,1
	jnc	xend_jmp3
	not	bh
xend_jmp3:
	shr	ah,1
	jnc	xend_jmp4
	not	bl
xend_jmp4:
	or	bx,dx
	or	bl,bh
	or	al,bl
xend_skip0:
	stosb
	xor	al,al
	out	7ch,al

ext:
	pop	cx
	add	ds:piloadc_vadr,80
	dec	ds:piloadc_y_wid2
	jz	piloadc_fin
	dec	cx
	jz	ext2
	jmp	ylop
ext2:
	pop	es
	popa
	mov	di,ds:piloadc_bufbgn
	ret
piloadc_fin:
	test	ds:piloadc_flg800,1
	jle	fin_jmp
	mov	al,0
;	out	0a4h,al
	out	0a6h,al
	and	ds:piloadc_flg800,not 2
fin_jmp:
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
	mov	bl,ds:piloadc_tone
	mov	bh,100
	mov	di,piloadc_tonetbl
	xor	cx,cx
palset_plop:
	mov	al,cl
	mul	bl
	div	bh
	stosb
	inc	cl
	cmp	cl,16
	jnz	palset_plop

	mov	si,piloadc_PaletteBuff
	mov	bx,piloadc_tonetbl
	mov	cx,16
	xor	ah,ah
	test	ds:piloadc_option,16
	jnz	palset_lop2
palset_lop:				;通常
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
	loop	palset_lop
	pop	bx
	ret
palset_lop2:				;NOTE用
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
	loop	palset_lop2
	pop	bx
	ret

	db	0	; word alignment
