; superimpose & master library module
;
; Description:
;	パターンの表示(16x16限定, 4色以内, 画面上下連続)
;
; Functions/Procedures:
;	void z_super_roll_put_tiny( int x<ax>, int y<dx>, int num ) ;
;
; Parameters:
;	x,y	描画する座標
;	num	パターン番号
;	Further assumes that the caller…
;	• …has set ES to the beginning of VRAM (0A800h)
;	• …and has set the GRCG to RMW mode. (Consequently, it also isn't turned
;	  off before returning from this function.)
;
; Returns:
;	none
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801
;
; Requiring Resources:
;	CPU: V30
;	GRCG
;
; Notes:
;	Micro-optimized version of the original master.lib function, used for
;	drawing all sorts of 16×16 sprites in TH04 and TH05. Changes compared to
;	the original, in addition to the assumptions mentioned above:
;	• Procedure distance is NEAR rather than FAR.
;	• X and Y coordinates are passed in AX and DX, respectively, rather than
;	  on the stack.
;	• Therefore, I removed the WIDE_RANGE branch, as it wouldn't have worked
;	  with the changed register contents anyway.
;	• A small attempt to optimize the EVEN_COLOR_LOOP by jumping over the
;	  blitting write of the third byte if it is blank.
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	恋塚(恋塚昭彦)
;	ZUN
;
; Revision History:
;	93/ 9/19 Initial: superrpt.asm / master.lib 0.21
;

PATTERN_HEIGHT	equ 16
SCREEN_HEIGHT	equ 400
SCREEN_XBYTES	equ 80
GC_MODEREG	equ 07ch
GC_TILEREG	equ 07eh
GC_RMW		equ 0c0h ; 書き込みﾋﾞｯﾄが立っているﾄﾞｯﾄにﾀｲﾙﾚｼﾞｽﾀから書く

MRETURN macro
	pop	DI
	pop	SI
	pop	DS
	ret	2		; ZUN change, since only one parameter is passed via the stack
	EVEN
	endm

public Z_SUPER_ROLL_PUT_TINY
Z_SUPER_ROLL_PUT_TINY proc near	; super_roll_put_tiny() {
	even
	mov	BX,SP
	push	DS
	push	SI
	push	DI

	@@num	= 2

	mov	BX,SS:[BX+@@num]
	shl	BX,1
	mov	DS,super_patdata[BX]

	; SCREEN_XBYTES = 80 を想定
	mov	BX,DX		; ZUN change, DI → DX
	shl	BX,2
	add	BX,DX		; ZUN change, DI → DX
	shl	BX,4
	mov	CX,AX		; ZUN change
	and	CX,7		; CL = x & 7
	shr	AX,3
	add	BX,AX		; BX = draw start offset

	xor	SI,SI

	lodsw
	cmp	AL,80h
	jnz	short @@RETURN	; １色もないとき(おいおい)

	mov	DL,0ffh		; DL = ワード境界マスク
	shr	DL,CL

	test	BL,1	; ZUN change, BX → BL
	jnz	short @@ODD_COLOR_LOOP
	EVEN
	; 偶数アドレス
@@EVEN_COLOR_LOOP:
	; 色の指定あるね
	REPT 4
	shr	AH,1
	sbb	AL,AL
	out	GC_TILEREG,AL
	ENDM

	mov	CH,PATTERN_HEIGHT
	mov	DI,BX
	cmp	DI,(SCREEN_HEIGHT-PATTERN_HEIGHT+1)*SCREEN_XBYTES
	jb	short @@EVEN_YLOOP2

	EVEN
@@EVEN_YLOOP1:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,DL
	mov	ES:[DI],AX
	xor	AL,DH
	jz	@@EVEN_YLOOP1_SKIP_BLANK_3RD
	mov	ES:[DI+2],AL

@@EVEN_YLOOP1_SKIP_BLANK_3RD:
	add	DI,SCREEN_XBYTES
	dec	CH
	cmp	DI,SCREEN_HEIGHT*SCREEN_XBYTES
	jb	short @@EVEN_YLOOP1

	sub	DI,SCREEN_HEIGHT*SCREEN_XBYTES

	EVEN
@@EVEN_YLOOP2:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,DL
	mov	ES:[DI],AX
	xor	AL,DH
	jz	@@EVEN_YLOOP2_SKIP_BLANK_3RD
	mov	ES:[DI+2],AL

@@EVEN_YLOOP2_SKIP_BLANK_3RD:
	add	DI,SCREEN_XBYTES

	dec	CH
	jnz	short @@EVEN_YLOOP2

@@EVEN_YLOOP_END:
	lodsw
	cmp	AL,80h
	je	short @@EVEN_COLOR_LOOP

@@RETURN:
	MRETURN


	EVEN
	; 奇数アドレス
@@ODD_COLOR_LOOP:
	; 色の指定あるね
	REPT 4
	shr	AH,1
	sbb	AL,AL
	out	GC_TILEREG,AL
	ENDM

	mov	CH,PATTERN_HEIGHT
	mov	DI,BX
	cmp	DI,(SCREEN_HEIGHT-PATTERN_HEIGHT+1)*SCREEN_XBYTES
	jb	short @@ODD_YLOOP2

	EVEN
@@ODD_YLOOP1:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,DL
	mov	ES:[DI],AL
	xor	AL,DH
	xchg	AH,AL
	mov	ES:[DI+1],AX
	add	DI,SCREEN_XBYTES

	dec	CH
	cmp	DI,SCREEN_HEIGHT*SCREEN_XBYTES
	jb	short @@ODD_YLOOP1

	sub	DI,SCREEN_HEIGHT*SCREEN_XBYTES

	EVEN
@@ODD_YLOOP2:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,DL
	mov	ES:[DI],AL
	xor	AL,DH
	xchg	AH,AL
	mov	ES:[DI+1],AX
	add	DI,SCREEN_XBYTES

	dec	CH
	jnz	short @@ODD_YLOOP2

@@ODD_YLOOP_END:
	lodsw
	cmp	AL,80h
	je	short @@ODD_COLOR_LOOP

	MRETURN
Z_SUPER_ROLL_PUT_TINY	endp			; }
