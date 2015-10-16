; superimpose & master library module
;
; Description:
;	パターンの表示
;
; Functions/Procedures:
;	void super_put( int x, int y, int num ) ;
;
; Parameters:
;	x,y	描画する座標
;	num	パターン番号
;
; Returns:
;	
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
;	
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	Kazumi(奥田  仁)
;	恋塚(恋塚昭彦)
;
; Revision History:
;
;$Id: superput.asm 0.17 92/05/29 20:38:10 Kazumi Rel $
;
;	93/ 3/20 Initial: master.lib <- super.lib 0.22b
;	93/ 5/ 4 [M0.16]
;	93/ 9/20 [M0.21] すこし(32byteぐらい)縮小
;	93/ 9/20 [M0.21] WORD_MASK廃止
;

func SUPER_PUT
	push	BP
	mov	BP,SP
	push	DS
	push	SI
	push	DI

	@@x	= (RETSIZE+3)*2
	@@y	= (RETSIZE+2)*2
	@@num	= (RETSIZE+1)*2

	mov	BX,[BP+@@num]
	shl	BX,1		;integer size & near pointer
	mov	DX,super_patsize[BX]	;pattern size (1-8)

	mov	CX,[BP+@@x]
	mov	BP,[BP+@@y]
	mov	AX,BP		;-+
	shl	AX,2		; |
	add	BP,AX		; |BP=y*80
	shl	BP,4		;-+
	mov	AX,CX
	and	CX,7h		;CL=x%8(shift dot counter)
	shr	AX,3		;AX=x/8
	add	BP,AX		;GVRAM offset address
	mov	SI,CX
	mov	CH,DH		;DL -> DH
	shr	CH,1

	mov	AL,DL
	mov	AH,BYTE_MASK[SI]
	mov	CS:_BX_,AX
	test	BP,1
	jnz	short @@ODD_ADDRESS

	; 開始アドレスが偶数
@@EVEN_ADDRESS:
	test	DH,1		;DX -> DH
	jnz	short @@ODD_SIZE1

	; 開始アドレスが偶数で長さも偶数
	mov	BYTE PTR CS:[COUNT1],CH
	mov	AL,80
	sub	AL,DH		;DL -> DH
	mov	BYTE PTR CS:[ADD_DI1],AL
	mov	CS:SUPERPUT_DISP_ADDRESS,offset SUPERPUT_DISP1 - offset JUMP_ORIGIN
	jmp	short @@START

	; 開始アドレスが偶数で長さは奇数
	EVEN
@@ODD_SIZE1:
	mov	BYTE PTR CS:[COUNT2],CH
	mov	AL,80
	sub	AL,DH		;DL -> DH
	mov	BYTE PTR CS:[ADD_DI2],AL
	mov	CS:SUPERPUT_DISP_ADDRESS,offset SUPERPUT_DISP2 - offset JUMP_ORIGIN
	jmp	short @@START

	; 開始アドレスが奇数
	EVEN
@@ODD_ADDRESS:
	dec	BP
	test	DH,1		;DX -> DH
	jnz	short @@ODD_SIZE2

	; 開始アドレスが奇数で長さは偶数
	dec	CH		;!!!!!!!!!!!!!!!!!!!!!
	mov	BYTE PTR CS:[COUNT3],CH
	mov	AL,78		;word
	sub	AL,DH		;DL -> DH
	mov	BYTE PTR CS:[ADD_DI3],AL
	mov	CS:SUPERPUT_DISP_ADDRESS,offset SUPERPUT_DISP3 - offset JUMP_ORIGIN
	jmp	short @@START

	; 開始アドレスが奇数で長さも奇数
	EVEN
@@ODD_SIZE2:
	mov	BYTE PTR CS:[COUNT4],CH
	mov	AL,79		;word
	sub	AL,DH		;DL -> DH
	mov	BYTE PTR CS:[ADD_DI4],AL
	mov	CS:SUPERPUT_DISP_ADDRESS,offset SUPERPUT_DISP4 - offset JUMP_ORIGIN
	EVEN

	; ごーごー
@@START:
	mov	DS,super_patdata[BX]
	xor	SI,SI

	mov	AL,0c0h		;RMW mode
	out	7ch,AL
	mov	AX,SI
	out	7eh,AL
	out	7eh,AL
	out	7eh,AL
	out	7eh,AL
	mov	AX,0a800h
	mov	ES,AX

	call	SUPERPUT_DISP		;originally cls_loop

	mov	AX,0ff00h + 11001110b
	out	7ch,AL		;RMW mode
	mov	AL,AH		;AL==0ffh
	out	7eh,AL
	out	7eh,AL
	out	7eh,AL
	out	7eh,AL

	call	SUPERPUT_DISP
	mov	AL,11001101b
	out	7ch,AL		;RMW mode
	call	SUPERPUT_DISP
	mov	AL,11001011b
	out	7ch,AL		;RMW mode
	call	SUPERPUT_DISP
	mov	AL,11000111b
	out	7ch,AL		;RMW mode
	call	SUPERPUT_DISP

	xor	AL,AL
	out	7ch,AL		;grcg off

	pop	DI
	pop	SI
	pop	DS
	pop	BP
	ret	6
endfunc

; 開始偶数長さ偶数
;
;
SUPERPUT_DISP1	proc	near
	xor	DL,DL
	EVEN
@@PUT_LOOP1:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,BH
	xor	DH,AL
	or	AL,DL
	stosw	;mov 	ES:[DI],AX	;;;or
	mov	DL,DH
	dec	CH
	jnz	short @@PUT_LOOP1
	mov	ES:[DI],DL
	mov	DL,CH	;DL=0
	add	DI,80	;dummy
ADD_DI1		EQU	$-1
	mov	CH,11h	;dummy
COUNT1		EQU	$-1
	dec	BL
	jnz	short @@PUT_LOOP1
	ret
SUPERPUT_DISP1	endp

; 開始偶数長さ奇数
;
;
	EVEN
SUPERPUT_DISP2	proc	near
	xor	DL,DL
	EVEN
@@SINGLE_CHECK2:
	or	CH,CH
	jz	short @@SKIP2

	EVEN
@@PUT_LOOP2:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,BH
	xor	DH,AL
	or	AL,DL
	stosw	;mov 	ES:[DI],AX	;;;or
	mov	DL,DH
	dec	CH
	jnz	short @@PUT_LOOP2

@@SKIP2:
	lodsb
	xor	AH,AH
	ror	AX,CL
	or	AL,DL
	stosw
	dec	DI
	mov	DL,CH	;DL=0
	add	DI,80	;dummy
ADD_DI2		EQU	$-1
	mov	CH,11h	;dummy
COUNT2		EQU	$-1
	dec	BL
	jnz	short @@SINGLE_CHECK2
	ret
SUPERPUT_DISP2	endp

; 開始奇数長さ偶数
;
;
	EVEN
SUPERPUT_DISP3	proc	near
@@PUT_LOOP3_1:
	lodsb
	xor	AH,AH
	ror	AX,CL
	mov	DL,AH
	xchg	AH,AL
	xor	AL,AL
	stosw
	or	CH,CH
	jz	short @@NO_WORD1

	EVEN
@@PUT_LOOP3_2:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,BH
	xor	DH,AL
	or	AL,DL
	stosw	;mov 	ES:[DI],AX	;;;or
	mov	DL,DH
	dec	CH
	jnz	short @@PUT_LOOP3_2

	EVEN
@@NO_WORD1:
	lodsb
	xor	AH,AH
	ror	AX,CL
	or	AL,DL
	stosw
	mov	DL,CH	;DL=0
	add	DI,80	;dummy
ADD_DI3		EQU	$-1
	mov	CH,11h	;dummy
COUNT3		EQU	$-1
	dec	BL
	jnz	short @@PUT_LOOP3_1
	ret
SUPERPUT_DISP3	endp

; 開始奇数長さ奇数
;
;
	EVEN
SUPERPUT_DISP4	proc	near
@@PUT_LOOP4_1:
	lodsb
	xor	AH,AH
	ror	AX,CL
	mov	DL,AH
	xchg	AH,AL
	xor	AL,AL
	stosw
	or	CH,CH
	jz	short @@NO_WORD2

	EVEN
@@PUT_LOOP4_2:
	lodsw
	ror	AX,CL
	mov	DH,AL
	and	AL,BH
	xor	DH,AL
	or	AL,DL
	stosw	;mov 	ES:[DI],AX	;;;or
	mov	DL,DH
	dec	CH
	jnz	short @@PUT_LOOP4_2

	EVEN
@@NO_WORD2:
	mov	ES:[DI],DL
	mov	DL,CH	;DL=0
	add	DI,80	;dummy
ADD_DI4		EQU	$-1
	mov	CH,11h	;dummy
COUNT4		EQU	$-1
	dec	BL
	jnz	short @@PUT_LOOP4_1
	ret
SUPERPUT_DISP4	endp

;
; 表示サブルーチンエントリ
;
;
	EVEN
SUPERPUT_DISP	proc	near
	mov	DI,BP
	JMOV	BX,_BX_	; BH=MIDMASK  BL=YLEN
	jmp	near ptr SUPERPUT_DISP1	; ダミーで遠いところを
	org	$-2
SUPERPUT_DISP_ADDRESS	dw	?
JUMP_ORIGIN	label	word
	EVEN
SUPERPUT_DISP	endp
