PAGE 98,120
; gc_poly library - graphics - grcg - trapezoid - noclip - PC98V
;
; Subroutines:
;	draw_trapezoidx
;
; Variables:
;	trapez_a, trapez_b	台形描画作業変数
;
; Description:
;	台形塗りつぶし(ES:〜が対象)
;
; Binding Target:
;	asm routine
;
; Running Target:
;	NEC PC-9801 Normal mode
;
; Requiring Resources:
;	CPU: V30
;	GRAPHICS ACCELARATOR: GRAPHIC CHARGER
;
; Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Notes:
;	・グラフィック画面の青プレーンにのみ描画します。
;	・色をつけるには、グラフィックチャージャーを利用してください。
;	・クリッピングは一切しません。
;	・側辺同士が交差していると、交差した描画をします。
;
; Author:
;	恋塚昭彦
;
; 関連関数:
;
; Revision History:
;	92/3/21 Initial
;	92/3/29 bug fix, 台形に側辺の交差を認めるようにした
;	92/4/2 少々加速
;	92/4/18 三角形ﾙｰﾁﾝから分離。ｸﾘｯﾋﾟﾝｸﾞ付加。
;	92/4/19 少々加速
;	92/5/7 自己書き換えにより加速
;	92/5/20 任意ｸﾘｯﾋﾟﾝｸﾞの横にだけ対応。:-)
;	92/5/22 ↑これも自己書き換え〜
;	92/6/4	grcg_trapezoid()関数をgc_zoid.asmに分割。
;	92/6/5	bugfix(make_lineworkのCXが0の時のdiv 0回避)
;	92/6/5	下端クリップ対応
;	92/6/12 加速〜
;	92/6/16 TASMに対応
;	92/7/10 クリッピング無し＆側辺交差無し版(koizoidx.asm)
;	92/7/14 加速
;	92/7/17 最初の点が同じxだと変になってたbugをfix...減速(;_;)
;		今度は、横幅 1dotの並行な図形はすごく遅いぞ
;	93/3/2 あう(>_<)<-意味なし
;	93/ 5/29 [M0.18] .CONST->.DATA
;	94/ 2/23 [M0.23] make_lineworkのEXTRNを削除(それだけ(^^;)

; LINEWORK構造体の各メンバの定義
; 名称  - ｵﾌｾｯﾄ - 説明
koizoidx_x	= 0	; 現在のx座標
koizoidx_dlx	= 2	; 誤差変数への加算値
koizoidx_s	= 4	; 誤差変数
koizoidx_d	= 6	; 最小横移動量(符号付き)

;-------------------------------------------------------------------------
; draw_trapezoidx - 台形の描画 高速（機能削減）版
; IN:
;	SI : unsigned yadr	; 描画する三角形の上のラインの左端のVRAMｵﾌｾｯﾄ
;	DX : unsigned ylen	; 描画する三角形の上下のライン差(y2-y1)
;	ES : unsigned gseg	; 描画するVRAMのセグメント(ClipYT_seg)
;	trapez_a		; 側辺aのxの初期値と傾き
;	trapez_b		; 側辺bのxの初期値と傾き
; BREAKS:
;	AX,BX,CX,DX,SI,DI,flags
;
	public draw_trapezoidx
draw_trapezoidx	PROC NEAR
	mov	AX,[trapez_a+koizoidx_d]
	mov	CS:[koizoidx_trapez_a_d],AX
	mov	AX,[trapez_b+koizoidx_d]
	mov	CS:[koizoidx_trapez_b_d],AX

	mov	AX,[trapez_a+koizoidx_dlx]
	mov	CS:[koizoidx_trapez_a_dlx],AX
	mov	AX,[trapez_b+koizoidx_dlx]
	mov	CS:[koizoidx_trapez_b_dlx],AX

	out	64h,AL		; 'out anywhere' for CPU cache clear
				; 64h: PC-9801の CRTV割り込みﾘｾｯﾄ

	push	BP

	mov	BP,[trapez_a+koizoidx_x]
	mov	CX,[trapez_b+koizoidx_x]

	EVEN
@@YLOOP:
	; 水平線 (without clipping) start ===================================
	; IN: SI... x=0の時のVRAM ADDR(y*80)	BP,CX... 二つのx座標
	mov	BX,BP

	sub	CX,BX		; CX := bitlen
				; BX := left-x
	sbb	AX,AX
	xor	CX,AX
	sub	CX,AX
	and	AX,CX
	sub	BX,AX

	mov	DI,BX		; addr := yaddr + xl div $10 * 2
	shr	DI,4
	shl	DI,1
	add	DI,SI

	and	BX,0Fh		; BX := xl and $0F
	add	CX,BX
	shl	BX,1
	mov	AX,[EDGES+BX]	; 左エッジ
	not	AX

	mov	BX,CX		;
	and	BX,0Fh
	shl	BX,1

	shr	CX,4
	jz	short @@LASTW
	dec	CX
	stosw
	mov	AX,0FFFFh
	rep stosw
@@LASTW:	and	AX,[EDGES+2+BX]	; 右エッジ
	stosw
	; 水平線 (without clipping) end ===================================

	add	[trapez_b+koizoidx_s],1234h
	org $-2
koizoidx_trapez_b_dlx	dw ?
	mov	CX,[trapez_b+koizoidx_x]
	adc	CX,1234h
	org $-2
koizoidx_trapez_b_d	dw ?
	mov	[trapez_b+koizoidx_x],CX

	add	[trapez_a+koizoidx_s],1234h
	org $-2
koizoidx_trapez_a_dlx	dw ?
	adc	BP,1234h
	org $-2
koizoidx_trapez_a_d	dw ?

	add	SI,80			; yadr
	dec	DX			; ylen
	jns	short @@YLOOP

	mov	[trapez_a+koizoidx_x],BP
	pop	BP
	ret
	EVEN
draw_trapezoidx	ENDP
