; ReC98
; ASM equivalents of relevant #defines from master.h

; These directly translate to the C OUTB, OUTW and OUTW2 macros.
outb macro port:req, value:rest
	mov	dx, port
ifdifi <value>, <al>
	mov	al, value
endif
	out	dx, al
endm
outw macro port:req, value:rest
	mov	dx, port
	mov	ax, value
	out	dx, ax
endm
outw2 macro port:req, value:rest
	mov	ax, value
	mov	dx, port
	out	dx, ax
endm

Point struc
	x dw ?
	y dw ?
Point	ends

GRAM_400 = 0A800h

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

; グラフィック画面関係 ----------------------------------------------------

graph_showpage	macro	page:rest
	outb	0A4h, page
endm

graph_accesspage	macro	page:rest
	outb	0A6h, page
endm

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

; GRCG color setting macros
; -------------------------
; In contrast to master.lib's own grcg_setcolor(), these keep the current
; GRCG mode.
GRCG_SETCOLOR_DIRECT_CLOBBERING macro port_reg:req, col_reg:req
	mov	port_reg, 7Eh
	rept 4
		shr	ah, 1
		sbb	al, al
		out	dx, al
	endm
endm

GRCG_SETCOLOR_DIRECT macro col_reg:req
	rept 4
		shr	col_reg, 1
		sbb	al, al
		out	7Eh, al
	endm
endm
; -------------------------

; EGC
; ---

EGC_ACTIVEPLANEREG	equ 04a0h
EGC_READPLANEREG  	equ 04a2h
EGC_MODE_ROP_REG  	equ 04a4h
EGC_FGCOLORREG    	equ 04a6h
EGC_MASKREG       	equ 04a8h
EGC_BGCOLORREG    	equ 04aah
EGC_ADDRRESSREG   	equ 04ach
EGC_BITLENGTHREG  	equ 04aeh

EGC_COMPAREREAD	equ 02000h
EGC_WS_PATREG  	equ 01000h	; WS = write source
EGC_WS_ROP     	equ 00800h	; parren reg, ans of rop, cpu data
EGC_WS_CPU     	equ 00000h
EGC_SHIFT_CPU  	equ 00400h	; input to shifter
EGC_SHIFT_VRAM 	equ 00000h	; cpu write, vram read
EGC_RL_MEMWRITE	equ 00200h	; RL = pattern Register Load
EGC_RL_MEMREAD 	equ 00100h	; ^at mem write, <-at mem read
EGC_RL_NONE    	equ 00000h	; no touch

egc_selectpat	macro
	outw2	EGC_READPLANEREG, 000FFh
endm

egc_setrop	macro mode_rop:rest
	outw2	EGC_MODE_ROP_REG, mode_rop
endm
; ---
