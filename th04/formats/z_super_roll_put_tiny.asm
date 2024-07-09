; superimpose & master library module
;
; Description:
;	パターンの表示(16x16/32x32限定, 4色以内, 画面上下連続)
;
; Functions/Procedures:
;	void z_super_roll_put_tiny_32x32(
;		screen_x_t left<ax>, vram_y_t top<dx>, int num
;	);
;	void z_super_roll_put_tiny_16x16(
;		screen_x_t left<ax>, vram_y_t top<dx>, int num
;	);
;
; Parameters:
;	x,y	描画する座標
;	num	パターン番号
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
;	z_super_roll_put_tiny_16x16() is a micro-optimized version of master.lib's
;	original super_roll_put_tiny(), used for drawing all sorts of 16×16
;	sprites in TH04 and TH05. Changes compared to the original:
;	• Procedure distance is NEAR rather than FAR.
;	• X and Y coordinates are passed in AX and DX, respectively, rather than
;	  on the stack.
;	• Therefore, I removed the WIDE_RANGE branch, as it wouldn't have worked
;	  with the changed register contents anyway.
;	• A small attempt to optimize the EVEN_COLOR_LOOP by jumping over the
;	  blitting write of the third byte if it is blank.
;	ZUN then adapted this modified function for 32×32 pixel sprites.
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

SCREEN_HEIGHT	equ 400
SCREEN_XBYTES	equ 80
GC_MODEREG	equ 07ch
GC_TILEREG	equ 07eh
GC_RMW		equ 0c0h ; 書き込みﾋﾞｯﾄが立っているﾄﾞｯﾄにﾀｲﾙﾚｼﾞｽﾀから書く

MRETURN macro
	pop	DI
	pop	SI
	pop	DS
	ret_bx	; ZUN change
	EVEN
	endm

srpt32x32_vram_topleft	dw 0

public Z_SUPER_ROLL_PUT_TINY_32X32_RAW
z_super_roll_put_tiny_32x32_raw	proc near

; Parameters
arg_bx near, @patnum:word
@@left equ ax
@@top equ dx

; Locals
@@PATTERN_HEIGHT = 32
@@first_mask equ dl
@@rows_left equ ch

	push	ds
	push	si
	push	di
	mov	bx, @patnum
	shl	bx, 1
	mov	ds, super_patdata[bx]
	mov	bx, @@top
	shl	bx, 2
	add	bx, @@top
	shl	bx, 4
	mov	cx, @@left
	and	cx, 7	; CL = x & 7
	shr	@@left, 3
	add	bx, @@left
	mov	cs:srpt32x32_vram_topleft, bx
	xor	si, si

	lodsw
	cmp	al, 80h	; is this tiny sprite data?
	jnz	short @@RETURN

	mov	@@first_mask, 0FFh
	shr	@@first_mask, cl
	test	bl, 1
	jnz	short @@ODD_COLOR_LOOP

@@EVEN_COLOR_LOOP:
	call	@@grcg_setcolor
	mov	@@rows_left, @@PATTERN_HEIGHT
	mov	di, cs:srpt32x32_vram_topleft
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@EVEN_YLOOP2

@@EVEN_YLOOP1:
	call	put32_even
	cmp	di, PLANE_SIZE
	jb	short @@EVEN_YLOOP1
	sub	di, PLANE_SIZE

	even
@@EVEN_YLOOP2:
	call	put32_even
	jnz	short @@EVEN_YLOOP2
	lodsw
	cmp	al, 80h
	jz	short @@EVEN_COLOR_LOOP

@@RETURN:
	MRETURN
; ---------------------------------------------------------------------------

@@ODD_COLOR_LOOP:
	call	@@grcg_setcolor
	mov	@@rows_left, @@PATTERN_HEIGHT
	mov	di, cs:srpt32x32_vram_topleft
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@ODD_YLOOP2

@@ODD_YLOOP1:
	call	put32_odd
	cmp	di, PLANE_SIZE
	jb	short @@ODD_YLOOP1
	sub	di, PLANE_SIZE
	nop

@@ODD_YLOOP2:
	call	put32_odd
	jnz	short @@ODD_YLOOP2
	lodsw
	cmp	al, 80h
	jz	short @@ODD_COLOR_LOOP
	MRETURN
; ---------------------------------------------------------------------------

; void __usercall near @@grcg_setcolor(vc_t col<ah>);
@@grcg_setcolor:
	GRCG_SETCOLOR_DIRECT ah
	ret
	even

; ---------------------------------------------------------------------------

; These put functions take:
; • const dots32_t* row_color_pixels<ds:si>
; • dots32_t* vram_offset<es:di>
; • uint3_t first_bit<cl>
; • uint8_t& rows_left<ch>
; • dots8_t first_mask<dl>
; [rows_left] is decremented at the end. ZF then indicates whether this was
; the last row.
@@first_bit equ cl

@@words equ bh
@@carry_pixels equ bl

put32_even:	; if X is even
	xor	@@carry_pixels, @@carry_pixels
	mov	@@words, 2
	lodsd

@@EVEN_WORD_LOOP:
	ror	ax, @@first_bit
	mov	dh, al
	and	al, @@first_mask
	xor	dh, al
	or	al, @@carry_pixels
	mov	@@carry_pixels, dh
	or	ax, ax
	jz	short @@EVEN_SKIP_BLANK_WORD
	mov	es:[di], ax

@@EVEN_SKIP_BLANK_WORD:
	add	di, word
	shr	eax, (8 * word)
	dec	@@words
	jnz	short @@EVEN_WORD_LOOP
	or	@@carry_pixels, @@carry_pixels
	jz	short @@EVEN_SKIP_BLANK_5TH
	mov	es:[di], @@carry_pixels

@@EVEN_SKIP_BLANK_5TH:
	add	di, (ROW_SIZE - dword)
	dec	@@rows_left
	retn
	even


put32_odd:	; if X is odd
	mov	@@words, 2
	lodsd	; EAX = the 32 pixels of this row
	ror	al, @@first_bit
	mov	@@carry_pixels, al
	and	al, @@first_mask
	jz	short @@ODD_SKIP_BLANK_1ST
	mov	es:[di], al

@@ODD_SKIP_BLANK_1ST:
	xor	@@carry_pixels, al
	inc	di
	shr	eax, (8 * byte)

@@ODD_WORD_LOOP:
	ror	ax, @@first_bit
	mov	dh, al
	and	al, @@first_mask
	xor	dh, al
	or	al, @@carry_pixels
	mov	@@carry_pixels, dh
	or	ax, ax
	jz	short @@ODD_SKIP_BLANK_WORD
	mov	es:[di], ax

@@ODD_SKIP_BLANK_WORD:
	add	di, word
	shr	eax, (8 * word)
	dec	@@words
	jnz	short @@ODD_WORD_LOOP
	add	di, (ROW_SIZE - (dword + 1))
	dec	@@rows_left
	retn
Z_SUPER_ROLL_PUT_TINY_32X32_RAW	endp


public Z_SUPER_ROLL_PUT_TINY_16X16_RAW
Z_SUPER_ROLL_PUT_TINY_16x16_RAW proc near	; z_super_roll_put_tiny_16x16_raw() {
	even
	mov	BX,SP
	push	DS
	push	SI
	push	DI

	@@num	= 2
	@@PATTERN_HEIGHT = 16

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

	mov	CH,@@PATTERN_HEIGHT
	mov	DI,BX
	cmp	DI,(SCREEN_HEIGHT-@@PATTERN_HEIGHT+1)*SCREEN_XBYTES
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

	mov	CH,@@PATTERN_HEIGHT
	mov	DI,BX
	cmp	DI,(SCREEN_HEIGHT-@@PATTERN_HEIGHT+1)*SCREEN_XBYTES
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
Z_SUPER_ROLL_PUT_TINY_16x16_RAW	endp			; }
