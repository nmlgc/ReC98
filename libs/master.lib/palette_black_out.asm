; superimpose & master library module
;
; Description:
;	画面をじわじわと真っ黒にする
;
; Functions/Procedures:
;	void palette_black_out( int speed ) ;
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
;$Id: blackout.asm 0.01 93/02/19 20:15:27 Kazumi Rel $
;	93/ 3/20 Initial: master.lib <- super.lib 0.22b
;	93/ 6/25 [M0.19] palette_show使用

func PALETTE_BLACK_OUT	; palette_black_out() {
	mov	BX,SP
	push	SI
	push	DI
	; 引数
	@@speed	= (RETSIZE+0)*2
	mov	SI,SS:[BX+@@speed]

	mov	PaletteTone,100
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

	sub	PaletteTone,6
	jg	short @@MLOOP

	mov	PaletteTone,0
	nopcall	PALETTE_SHOW
	pop	DI
	pop	SI
	ret	2
endfunc		; }
