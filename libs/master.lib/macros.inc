; ReC98
; ASM equivalents of relevant #defines from master.h

Point struc
	x dw ?
	y dw ?
Point	ends

; テキスト画面関係 --------------------------------------------------------

TX_BLACK	equ 001h ; テキスト属性
TX_BLUE	equ 021h
TX_RED	equ 041h
TX_MAGENTA	equ 061h
TX_GREEN	equ 081h
TX_CYAN	equ 0a1h
TX_YELLOW	equ 0c1h
TX_WHITE	equ 0e1h
TX_BLINK	equ 2
TX_REVERSE	equ 4
TX_UNDERLINE	equ 8

; グラフィック画面への多角形描画処理 --------------------------------------
; 出典: gc_poly.h 0.16

; grcg_setcolor()や vgc_setcolor()に指定するアクセスプレーン指定
GC_B	equ 00eh	; 青プレーンをアクセスする
GC_R	equ 00dh
GC_BR	equ 00ch	;	:
GC_G	equ 00bh	;	:
GC_BG	equ 00ah	;	:
GC_RG	equ 009h
GC_BRG	equ 008h	;	:
GC_I	equ 007h
GC_BI	equ 006h
GC_RI	equ 005h
GC_BRI	equ 004h
GC_GI	equ 003h
GC_BGI	equ 002h
GC_RGI	equ 001h	;	:
GC_BRGI	equ 000h	;

; grcg_setcolor()の modeに設定する値
GC_OFF	equ 0
GC_TDW	equ 080h	; 書き込みﾃﾞｰﾀは無視して、ﾀｲﾙﾚｼﾞｽﾀの内容を書く
GC_TCR	equ 080h	; ﾀｲﾙﾚｼﾞｽﾀと同じ色のﾋﾞｯﾄが立って読み込まれる
GC_RMW	equ 0c0h	; 書き込みﾋﾞｯﾄが立っているﾄﾞｯﾄにﾀｲﾙﾚｼﾞｽﾀから書く

; GRCG mode setting macros
; ------------------------
GRCG_SETMODE_CLOBBERING macro port_reg:req, mode:req
	mov	port_reg, 7Ch
	mov	al, mode
	out	port_reg, al
endm

GRCG_SETMODE_VIA_MOV macro value_reg:req, mode:req
	mov	value_reg, mode
	out	7Ch, value_reg
endm

GRCG_NOINT_SETMODE_VIA_MOV macro value_reg:req, mode:req
	mov	value_reg, mode
	pushf
	cli
	out	7Ch, al
	popf
endm

GRCG_OFF_CLOBBERING macro port_reg:req
	GRCG_SETMODE_CLOBBERING dx, GC_OFF
endm

GRCG_OFF_VIA_MOV macro value_reg:req
	GRCG_SETMODE_VIA_MOV value_reg, GC_OFF
endm

GRCG_OFF_VIA_XOR macro value_reg:req
	xor	value_reg, value_reg
	out	7Ch, value_reg
endm
; ------------------------
