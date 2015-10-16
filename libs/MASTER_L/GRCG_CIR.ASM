; master library - gc_poly - grcg - circle
;
; Description:
;	円描画
;
; Function/Procedures:
;	void grcg_circle( int x, int y, unsigned r ) ;
;
; Parameters:
;	x,y	中心座標
;	r	半径 ( 1 以上 )
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
;	半径が 0 ならば描画しません。
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
;	93/ 5/12 Initial:gc_circl.asm/master.lib 0.16
;	93/ 5/14 [M0.16] 加速
;	95/ 2/20 縦倍モード対応
;	95/ 3/25 [M0.22k] ゴミがでるバグ修正

MRETURN macro
	pop	DI
	pop	SI
	pop	BP
	ret	6
	EVEN
	endm

retfunc GC_CIRCL_ALLIN
	pop	SI
	pop	BP
	jmp	GRCG_CIRCLE_X
GC_CIRCL_CLIPOUT:
	pop	SI
	pop	BP
	ret	6
	EVEN
endfunc

func GRCG_CIRCLE	; grcg_circle() {
	push	BP
	mov	BP,SP
	push	SI
	; DIは下の方でpushしてる

	; 引数
	@@x	= (RETSIZE+3)*2
	@@y	= (RETSIZE+2)*2
	@@r	= (RETSIZE+1)*2

	mov	SI,[BP+@@r]	; SI = 半径
	xor	CX,CX		; どこかクリップ枠にひっかかったら 0以外にー

	; 大まかなクリッピング
	mov	AX,[BP+@@y]
	sub	AX,ClipYT
	mov	DX,AX		; DX = y
	sub	AX,SI
	cmp	AX,ClipYH
	jg	short GC_CIRCL_CLIPOUT
	shl	AX,1
	rcl	CX,1
	mov	AX,DX
	add	AX,SI
	js	short GC_CIRCL_CLIPOUT
	cmp	ClipYH,AX
	rcl	CX,1

	mov	AX,[BP+@@x]
	mov	BX,AX		; BX = x
	sub	AX,SI
	cmp	AX,ClipXR
	jg	short GC_CIRCL_CLIPOUT
	sub	AX,ClipXL
	shl	AX,1
	rcl	CX,1
	mov	AX,BX
	add	AX,SI
	cmp	AX,ClipXL
	jl	short GC_CIRCL_CLIPOUT
	cmp	ClipXR,AX
	rcl	CX,1
	jcxz	short GC_CIRCL_ALLIN

	; 半径が 0 なら描画しない
	or	SI,SI
	jz	short GC_CIRCL_CLIPOUT

	push	DI

	mov	AL,byte ptr graph_VramZoom
	mov	CS:GC_CIRCL_VRAMZOOM1,AL
	mov	CS:GC_CIRCL_VRAMZOOM2,AL

	mov	ES,ClipYT_seg
	mov	AX,BX		; AX = x

	mov	gc_circl_cx_,AX
	mov	gc_circl_cy_,DX
	xor	DI,DI
	mov	BP,SI
	EVEN
@@LOOPTOP:
	call	GC_CIRCL_PSET4
	cmp	SI,DI
	je	short @@SKIP
	xchg	SI,DI
	call	GC_CIRCL_PSET4
	xchg	SI,DI
@@SKIP:
	stc		; BP -= DI*2+1;
	sbb	BP,DI	;
	sub	BP,DI	;
	jns	short @@LOOPCHECK
	dec	SI	; --SI;
	add	BP,SI	; BP += SI*2;
	add	BP,SI	;
@@LOOPCHECK:
	inc	DI	; ++DI;
	cmp	SI,DI
	jge	short @@LOOPTOP
	MRETURN
endfunc			; }

; in:
;	SI = dx
;	DI = dy
; break:
;	AX,BX,CX,DX
;
	EVEN
GC_CIRCL_PSET4Q proc near
	retn
	EVEN
GC_CIRCL_PSET4Q endp

GC_CIRCL_PSET4 proc	near
	mov	AX,gc_circl_cy_
	mov	BX,DI
	shr	BX,9	; dummy
	org	$-1
GC_CIRCL_VRAMZOOM1	db	?
	or	BX,BX
	jz	short @@PS4
	sub	AX,BX
	js	short @@PS3
	cmp	AX,ClipYH
	jg	short GC_CIRCL_PSET4Q	; →描けるわけがない場合

	; AX = (cy_ - DI)
	; (cx_ + SI, AX)と (cx_ - SI, AX)に点を打つ
	mov	DX,AX
	shl	DX,2
	add	DX,AX
	shl	DX,4

	mov	AX,gc_circl_cx_

	or	SI,SI		; dxが 0 ならば 1 点のみ
	je	short @@PS2

	sub	AX,SI
	cmp	AX,ClipXL
	jl	short @@PS1
	cmp	AX,ClipXR
	jg	short GC_CIRCL_PSET4Q	; 左側の点が右端を越えているなら
				; 右側の点は描けるわけがない

	mov	BX,AX
	mov	CX,AX
	shr	BX,3
	add	BX,DX
	and	CL,7
	mov	CH,80h
	shr	CH,CL
	mov	ES:[BX],CH
@@PS1:
	mov	AX,gc_circl_cx_
	add	AX,SI

@@PS2:
	cmp	AX,ClipXL
	jl	short @@PS3
	cmp	AX,ClipXR
	jg	short @@PS3

	mov	BX,AX
	mov	CX,BX
	shr	BX,3
	add	BX,DX
	and	CL,7
	mov	CH,80h
	shr	CH,CL
	mov	ES:[BX],CH

@@PS3:
	mov	AX,gc_circl_cy_
	mov	BX,DI
	shr	BX,9	; dummy
	org	$-1
GC_CIRCL_VRAMZOOM2	db	?
	add	AX,BX
@@PS4:
	cmp	AX,ClipYH
	jae	short @@PSQ

	; (cx_ + SI, AX)と (cx_ - SI, AX)に点を打つ
	mov	DX,AX
	shl	DX,2
	add	DX,AX
	shl	DX,4

	mov	AX,gc_circl_cx_

	or	SI,SI		; dxが 0 ならば 1 点のみ
	je	short @@PS6

	sub	AX,SI
	cmp	AX,ClipXL
	jl	short @@PS5
	cmp	AX,ClipXR
	jg	short @@PSQ	; 左側の点が右端を越えているなら
				; 右側の点は描けるわけがない

	mov	BX,AX
	mov	CX,AX
	shr	BX,3
	add	BX,DX
	and	CL,7
	mov	CH,80h
	shr	CH,CL
	mov	ES:[BX],CH
@@PS5:
	mov	AX,gc_circl_cx_
	add	AX,SI

@@PS6:
	cmp	AX,ClipXL
	jl	short @@PSQ
	cmp	AX,ClipXR
	jg	short @@PSQ

	mov	BX,AX
	mov	CX,BX
	shr	BX,3
	add	BX,DX
	and	CL,7
	mov	CH,80h
	shr	CH,CL
	mov	ES:[BX],CH

@@PSQ:
	ret
GC_CIRCL_PSET4 endp
