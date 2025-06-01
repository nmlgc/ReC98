; ReC98 fork of PiLoad. The full list of changes:
; • Renamed the original direct-to-VRAM loading entry point to `PiBlit`
; • Added a new `PiLoad` entry point that loads to a newly allocated 4-plane
;   buffer
; • Input data is now provided through a read callback
; • Added support for ZUN's .GRP files with a 'NZ' signature (lol)
; • [PaletteBuff] now receives the original 8-bit palette from the file's
;   header instead of getting shifted down to 4 bits
; • Removed blitting at non-byte-aligned X positions
; • Removed all palette and tone setting code
; • Removed all mode setting code
; • Removed comment display
; • Removed the Pascal entry points (might restore them if other PC-98 homebrew
;   developers actually need them)
; • Slightly optimized VRAM transfer by jumping over the GRCG shutdown when
;   blitting without a transparent color
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
tone	=	byte ptr ds:[138h] ; unused
option	=	byte ptr ds:[139h]
tcol	=	byte ptr ds:[13ah]
flg800	=	byte ptr ds:[13bh] ; unused
line4	=	word ptr ds:[13ch]
vadr	=	word ptr ds:[13eh]
fhandle	=	word ptr ds:[140h] ; unused
bufbgn	=	word ptr ds:[142h]
bufend	=	word ptr ds:[144h]
bufsize	=	word ptr ds:[146h]
y_wid2	=	word ptr ds:[148h]
x_wid2	=	word ptr ds:[14ah]
out_p	=	word ptr ds:[14ch] ; segment of first output bitplane
psize	=	word ptr ds:[14eh] ; plane size in paragraphs
gbuff	=	150h
buffer	=	150h+line*(lin+2)
parasize =	buffer
	.code
	locals
spreg	dw	?
dsseg	dw	?
trans_func	dw	?
read_func	label dword
read_func_off	dw	?
read_func_seg	dw	?

; Segment-aligns the data buffer address (BX:CX) and size (SI) received from
; the entry point. Thrashes AX.
buf_align proc near
	mov	ax,cx
	add	ax,15
	shr	ax,4
	add	ax,bx
	mov	ds,ax
	mov	ax,cx
	and	ax,15
	sub	si,ax
	ret
buf_align endp

	public	_PiBlit
_PiBlit	proc	near
	arg		buf,bufsiz,x,y,opt:word,reader:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,ds
	mov	cx,buf
	mov	si,bufsiz
	call	buf_align
	xor	bx,bx
	mov	es,bx
	mov	dx,reader
	mov	bx,x
	mov	cx,y
	mov	ax,opt
	call	piblit0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiBlit	endp

	public	_PiBlitL
_PiBlitL	proc	far
	arg		buf:dword,bufsiz,x,y,opt:word,reader:dword
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,word ptr buf+2
	mov	cx,word ptr buf
	mov	si,bufsiz
	call	buf_align
	les	dx,reader
	mov	bx,x
	mov	cx,y
	mov	ax,opt
	call	piblit0
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf
_PiBlitL	endp

	public	_PiBlitC
_PiBlitC	proc	near
	arg		buf:dword,bufsiz,x,y,opt:word,reader:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,word ptr buf+2
	mov	cx,word ptr buf
	mov	si,bufsiz
	call	buf_align
	xor	bx,bx
	mov	es,bx
	mov	dx,reader
	mov	bx,x
	mov	cx,y
	mov	ax,opt
	call	piblit0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiBlitC	endp

	public _PiLoadHeader
_PiLoadHeader proc near
	arg	buf,bufsiz:word,reader:word,opt:byte
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,ds
	mov	cx,buf
	mov	si,bufsiz
	call	buf_align
	xor	bx,bx
	mov	es,bx
	mov	dx,reader
	mov	al,opt
	call	piloadheader0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiLoadHeader endp

	public _PiLoadHeaderL
_PiLoadHeaderL proc far
	arg	buf:dword,bufsiz:word,reader:dword,opt:byte
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,word ptr buf+2
	mov	cx,word ptr buf
	mov	si,bufsiz
	call	buf_align
	les	dx,reader
	mov	al,opt
	call	piloadheader0
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf
_PiLoadHeaderL endp

	public _PiLoadHeaderC
_PiLoadHeaderC proc near
	arg	buf:dword,bufsiz:word,reader:word,opt:byte
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,word ptr buf+2
	mov	cx,word ptr buf
	mov	si,bufsiz
	call	buf_align
	xor	bx,bx
	mov	es,bx
	mov	dx,reader
	mov	al,opt
	call	piloadheader0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiLoadHeaderC endp

	public _PiLoadPlanes
_PiLoadPlanes proc near
	arg	plane_B:word,buf,bufsiz:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,ds
	mov	cx,buf
	mov	si,bufsiz
	call	buf_align
	mov	ax,plane_B
	call	piloadplanes0
	pop	ds
	pop	di
	pop	si
	pop	bp
	ret
_PiLoadPlanes endp

	public _PiLoadPlanesL
_PiLoadPlanesL proc far
	arg	plane_B:word,buf:dword,bufsiz:word
	push	bp
	mov	bp,sp
	push	si
	push	di
	push	ds
	mov	bx,word ptr buf+2
	mov	cx,word ptr buf
	mov	si,bufsiz
	call	buf_align
	mov	ax,plane_B
	call	piloadplanes0
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf
_PiLoadPlanesL endp


;	in	es:dx	= read_func
;		ds:0	= buff
;		si	= size(paragraph)
;		bx	= x
;		cx	= y
;		al	= option
;		ah	= tcol
	public	piblit0
error0:
	ret
piblit0:
	mov	x_pos,bx
	mov	y_pos,cx
	mov	word ptr option,ax
	mov	ax,offset gtrans
	mov	trans_func,ax
	jmp	start

;	in	es:dx	= read_func
;		ds:0	= buff
;		si	= size(paragraph)
;		al	= option
	public	piloadheader0
piloadheader0:
	mov	x_pos,0
	mov	y_pos,0
	mov	option,al
	mov	ax,offset mtrans
	mov	trans_func,ax

start:
	cld
	mov	spreg,sp
	mov	dsseg,ds
	mov	read_func_off,dx
	mov	read_func_seg,es
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

	mov	es,dsseg
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
	; Skip comment
	lodsb
	or	al,al
	jnz	pilop

	lodsb
	mov	bl,al	;palet flag
	lodsw		;ドット比率
	mov	cx,ax
	lodsb
	cmp	al,4	;plane check
	mov	ax,-32
	jnz	error
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
	mov	cx,((16 * 3) / 2)
	mov	di,PaletteBuff
	rep	movsw
nopalet:
	cmp	trans_func,offset gtrans
	je	skip_alloc

@@check_width:
	; Width has to be a multiple of 8.
	mov	ax,x_wid
	test	ax,7
	jz	@@valid_width
	mov	ax,-32
	jmp	error

@@valid_width:
	; 1bpp width × height has to fit within a segment minus 16 bytes…
	shr	ax,3
	mov	bx,y_wid
	mul	bx
	jnc	@@alloc
	mov	ax,-32
	jmp	error

@@alloc:
	; …because we paragraph-align the bitplanes for easier handling.
	add	ax,0fh
	shr	ax,4
	mov	psize,ax
	mov	cx,4
	mul	cx
	mov	si_resume,si
	ret

;	in	ax	= plane_B
;		ds:0	= buff
	public	piloadplanes0
piloadplanes0:
	cld
	mov	spreg,sp
	mov	dsseg,ds
	mov	out_p,ax
	mov	bx,ds
	mov	es,bx
	db	0BEh	;mov si,nn
si_resume	dw	?

skip_alloc:
	mov	bx,si
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
	call	trans
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
cjmp01:	call	trans
	jmp	cjmp02

jmp2:
	sub	cx,ax
	xchg	cx,ax
	rep	movsw
	call	trans
	sub	si,line4
	jmp	short jmp1

jmp0:
	xor	cx,cx
lop0:
	movsw
	cmp	di,bufend
	loopnz	lop0
	jnz	jmp1
	call	trans
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

	; Returns the buffer offset in BX.
fread:
	push	ax
	push	cx
	push	dx
	push	ds
	push	buffer
	push	bufsize
	mov	ax,seg DGROUP
	mov	ds,ax
	cmp	read_func_seg,0
	jz	@@read_func_near
@@read_func_far:
	call	read_func
	jmp	@@read_func_return
@@read_func_near:
	call	read_func_off
@@read_func_return:
	mov	ds,dsseg
	cmp	ax,0
	je	@err
	mov	bx,buffer
	pop	dx
	pop	cx
	pop	ax
	ret

@err:
	mov	sp,spreg
	ret

trans proc near
	pusha
	push	es
	mov	si,bufend
	mov	di,gbuff
	mov	cx,x_wid
	sub	si,cx
	sub	si,cx
	rep	movsw
	mov	si,di
	mov	cx,lin
	call	trans_func
	pop	es
	popa
	mov	di,bufbgn
	retn
trans endp

;	gbuffからlinライン分表示(gbuff->VRAM)
gtrans:
ylop:
	push	cx
	mov	di,vadr
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
	jz	xend_grcg
	jmp	xlop

xend_grcg:
	xor	al,al
	out	7ch,al
xend:
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
	jz	gtrans_ret
	jmp	ylop
fin:
	mov	sp,spreg
	xor	ax,ax
gtrans_ret:
	ret

;	Transfer [CX] lines from [gbuff] to the allocated buffer
mtrans proc near
	mov	bp,psize
	mov	di,vadr
@@ylop:
	push	cx
	mov	cx,x_wid
	shr	cx,3
@@xlop:
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
	mov	ax,out_p
	mov	es,ax
	mov	es:[di],dh
	add	ax,bp
	mov	es,ax
	mov	es:[di],dl
	add	ax,bp
	mov	es,ax
	mov	es:[di],bh
	add	ax,bp
	mov	es,ax
	mov	al,bl
	stosb
	dec	cx
	jz	@@xend
	jmp	@@xlop

@@xend:
	pop	cx
	dec	y_wid2
	jz	@@fin
	dec	cx
	jz	@@ext2
	jmp	@@ylop

@@ext2:
	mov	vadr,di
	ret
@@fin:
	mov	sp,spreg
	xor	ax,ax
	ret
mtrans endp

	end

