; master library - graphic - packedpixel - put - hline - 8dot - PC98V
;
; Description:
;	パックト4bitピクセル形式の水平グラフィックパターン表示
;
; Function/Procedures:
;	void graph_pack_put_8( int x, int y, void far * linepat, int len ) ;
;
; Parameters:
;	x	描画開始 x 座標( 0〜639, ただし8ドット単位に切り捨て )
;	y	描画 y 座標( 0 〜 399(※400ライン表示のとき)
;	linepat	パターンデータの先頭アドレス
;	len	パターンデータの横ドット数
;		ただし実際には8dot単位に切り詰めます。
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
;
; Notes:
;	クリッピングは縦方向だけ gc_poly 相当の処理を行っています。
;	横は画面幅でクリッピングできます。
;
; Assembly Language Note:
;	
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	恋塚昭彦
;
; Revision History:
;	93/ 6/23 Initial: grppput8.asm/master.lib 0.19
;	93/ 7/ 3 [M0.20] large modelでのbugfix
;	93/ 7/ 3 [M0.20] クリップ枠最下行を外と判定していた(^^; fix
;	93/ 7/28 [M0.20] ちょっと加速
;	93/11/22 [M0.21] linepatをfar固定化
;	93/12/ 8 [M0.22] RotTblを rottbl.asmに分離

	SCREEN_XBYTE equ 80

USE_GRCG = 0	; 1にするとGRCGを使うが少し遅くなる(RA21+VMM386)
USE_TABLE = 1

ROTATE	macro	wreg,lh,ll
	rept	2
	rol	wreg,1
	RCL	DH,1
	rol	wreg,1
	RCL	DL,1
	rol	wreg,1
	RCL	lh,1
	rol	wreg,1
	RCL	ll,1
	endm
endm
GC_MODEREG equ 7ch
GC_TILEREG equ 7eh


MRETURN macro
	pop	DI
	pop	SI
	pop	BP
	ret	5*2
	EVEN
endm

retfunc GRPPPUT8_CLIPOUT
	MRETURN
endfunc

func GRAPH_PACK_PUT_8	; graph_pack_put_8() {
	push	BP
	mov	BP,SP
	push	SI
	push	DI

	; 引数
	@@x	= (RETSIZE+5)*2
	@@y	= (RETSIZE+4)*2
	@@linepat	= (RETSIZE+2)*2
	@@len	= (RETSIZE+1)*2

	mov	AX,[BP+@@y]
	sub	AX,ClipYT
	cmp	AX,ClipYH
	ja	short GRPPPUT8_CLIPOUT

	mov	CX,[BP+@@len]
	sar	CX,3		; 8dot単位に切り捨てる
	jle	short GRPPPUT8_CLIPOUT

	mov	SI,[BP+@@linepat]

	mov	DI,[BP+@@x]
	sar	DI,3		; xを8ドット単位に補正
	jns	short @@XNORMAL
	add	CX,DI
	jle	short GRPPPUT8_CLIPOUT
	shl	DI,2
	add	SI,DI
	xor	DI,DI
@@XNORMAL:
	cmp	DI,SCREEN_XBYTE
	jge	short GRPPPUT8_CLIPOUT

	add	CX,DI
	cmp	CX,SCREEN_XBYTE
	jl	short @@RIGHTCLIPPED
	mov	CX,SCREEN_XBYTE
@@RIGHTCLIPPED:
	sub	CX,DI
	imul	AX,AX,SCREEN_XBYTE
	add	DI,AX		; DI = draw address

IF USE_GRCG
	pushf
	CLI
	mov	AL,80h		; GC_TDW
	out	GC_MODEREG,AL
	popf
ENDIF

	; 描画開始
	push	DS
	mov	ES,ClipYT_seg
	mov	DS,[BP+@@linepat+2]

	mov	BP,CX
	CLD
	EVEN
@@XLOOP:

IF USE_TABLE
	mov	CL,2

	mov	BL,[SI]
	mov	BH,0
	shl	BX,CL
	mov	AX,word ptr CS:RotTbl[BX]
	mov	DX,word ptr CS:RotTbl[BX+2]
	inc	SI
	REPT 3
	shl	AX,CL
	shl	DX,CL
	mov	BL,[SI]
	mov	BH,0
	shl	BX,CL
	or	AX,word ptr CS:RotTbl[BX]
	or	DX,word ptr CS:RotTbl[BX+2]
	inc	SI
	ENDM
ELSE
	mov	CX,2
@@LOOP8:
	lodsw
	ROTATE	AL,BH,BL
	ROTATE	AH,BH,BL
	loop	short @@LOOP8
	mov	AX,BX
ENDIF

IF USE_GRCG
	out	GC_TILEREG,AL
	mov	AL,AH
	out	GC_TILEREG,AL
	mov	AX,DX
	out	GC_TILEREG,AL
	mov	AL,AH
	out	GC_TILEREG,AL
	stosb
ELSE
	mov	ES:[DI],AL		; 0a800h
	mov	BX,ES
	mov	ES:[DI+8000h],AH	; 0b000h
	add	BH,10h
	mov	ES,BX
	mov	ES:[DI],DL		; 0b800h
	add	BH,28h
	mov	ES,BX
	mov	ES:[DI],DH		; 0e000h
	sub	BH,38h
	mov	ES,BX
	inc	DI
ENDIF

	dec	BP
	jnz	short @@XLOOP

	pop	DS

IF USE_GRCG
	mov	AL,0
	out	GC_MODEREG,AL
ENDIF
	MRETURN
endfunc		; }
