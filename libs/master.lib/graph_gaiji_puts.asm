; master library - GRPHICS - GRCG - GAIJI - Cstring - PC98V
;
; Description:
;	グラフィック画面へ外字文字列を描画する
;
; Function/Procedures:
;	void graph_gaiji_puts( int x, int y, int step, char * ank, int color )
;
; Parameters:
;	x,y	開始左上座標
;	step	文字ごとに進めるドット数
;	ank	半角文字列(対応する外字コードに変換して描画します)
;	color	色( 0〜15 )
;
; Returns:
;	none
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801V
;
; Requiring Resources:
;	CPU: V30
;	GRCG
;
; Notes:
;	クリッピングは行っていません。
;	外字があらかじめ定義されている必要があります。
;
; Assembly Language Note:
;	
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	Kazumi
;
; Revision History:
;	93/ 7/16 Initial: grpgputs.asm/master.lib 0.20

func GRAPH_GAIJI_PUTS	; graph_gaiji_puts() {
	push	BP
	mov	BP,SP
	push	SI
	push	DI
	_push	DS

	; 引数
	@@x	= (RETSIZE+4+DATASIZE)*2
	@@y	= (RETSIZE+3+DATASIZE)*2
	@@step	= (RETSIZE+2+DATASIZE)*2
	@@ank	= (RETSIZE+2)*2
	@@color	= (RETSIZE+1)*2

	mov	ES,graph_VramSeg

	mov	CX,[BP+@@x]
	mov	DI,[BP+@@y]
	mov	BX,[BP+@@step]
	_lds	SI,[BP+@@ank]
	mov	DX,[BP+@@color]
	mov	BP,BX

	mov	AX,DI		;-+
	shl	AX,2		; |
	add	DI,AX		; |DI=y*80
	shl	DI,4		;-+

	; GRCG setting..
	mov	AL,0c0h		;RMW mode
	pushf
	cli
	out	7ch,AL
	popf
	shr	DX,1
	sbb	AL,AL
	out	7eh,AL
	shr	DX,1
	sbb	AL,AL
	out	7eh,AL
	shr	DX,1
	sbb	AL,AL
	out	7eh,AL
	shr	DX,1
	sbb	AL,AL
	out	7eh,AL

	; CG dot access
	mov	AL,0bh
	out	68h,AL

@@START:
	lodsb
	or	AL,AL
	jz	short @@RETURN
	mov	AH,0

	; master.lib bug: This calculation should not add the carry flag – if it's
	; set, the resulting JIS code point will correspond to ([@@ank] + 1). ADD
	; is the correct instruction here.
if GAME ge 4
	add	AX,5680h	;from gjwrite.asm
else
	adc	AX,5680h	;from gjwrite.asm
endif

	and	AX,0ff7fh

	mov	BX,CX
	and	CX,7h		;CL=x%8(shift dot counter)
	shr	BX,3		;AX=x/8
	add	DI,BX		;GVRAM offset address

	out	0a1h,AL
	mov	AL,AH
	out	0a3h,AL
	mov	DX,16
	xor	CH,CH
	EVEN
@@PUT_LOOP:
	mov	AL,CH
	or	AL,00100000b	;L/R
	out	0a5h,AL
	in	AL,0a9h
	mov	AH,AL
	mov	AL,CH
	out	0a5h,AL
	in	AL,0a9h
	mov	BH,AL
	mov	BL,0
	shr	AX,CL
	shr	BX,CL
	xchg	AL,AH
	stosw
	mov	ES:[DI],BL
	add	DI,78		;next line
	inc	CH
	dec	DX
	jnz	short @@PUT_LOOP
	sub	DI,80 * 16
	xor	CH,CH
	add	CX,BP

	jmp	short @@START

@@RETURN:
	; CG code access
	mov	AL,0ah
	out	68h,AL
	; GRCG off
	xor	AL,AL
	out	7ch,AL		;grcg stop

	_pop	DS
	pop	DI
	pop	SI
	pop	BP
	ret	(4+DATASIZE)*2
endfunc			; }
