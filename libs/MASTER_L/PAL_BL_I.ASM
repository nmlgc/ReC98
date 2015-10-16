; superimpose & master library module
;
; Description:
;	画面を黒からじわじわと正常にする
;
; Functions/Procedures:
;	void palette_black_in( int speed ) ;
;
; Parameters:
;	speed	遅延時間(vsync単位) 0=遅延なし
;
; Returns:
;	
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801V
;
; Requiring Resources:
;	CPU: 8086
;
; Notes:
;	実行後, PaletteTone は 100になります。
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
;$Id: blackin.asm 0.01 93/02/19 20:16:20 Kazumi Rel $
;
;	93/ 3/10 Initial: master.lib <- super.lib 0.22b
;	93/ 9/13 [M0.21] palette_show使用(忘れてた(^^;)
;

func PALETTE_BLACK_IN	; palette_black_in() {
	mov	BX,SP
	push	SI
	push	DI
	; 引数
	speed	= (RETSIZE+0)*2
	mov	SI,SS:[BX+speed]

	mov	PaletteTone,0
	nopcall	VSYNC_WAIT	; 表示タイミングあわせ
@@MLOOP:
	nopcall	PALETTE_SHOW
	mov	DI,SI
	cmp	DI,0
	jle	short @@SKIP
@@VWAIT:
	nopcall	VSYNC_WAIT
	dec	DI
	jnz	short @@VWAIT
@@SKIP:

	add	PaletteTone,6
	cmp	PaletteTone,100
	jl	short @@MLOOP

	mov	PaletteTone,100
	nopcall	PALETTE_SHOW
	pop	DI
	pop	SI
	ret	2
endfunc		; }
