; master library - PC-9801
;
; Description:
;	ジョイスティック関連の初期設定 (TH03 version)
;
; Function/Procedures:
;	int js_start( void ) ;
;
; Parameters:
;
; Returns:
;	0 = ジョイスティックは全く使用しない
;	1 = サウンドボードを認識した
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801
;
; Requiring Resources:
;	CPU: 8086
;
; Notes:
;	TH03 removes the support for the SAJ-98 board by SYSTEM SACOM.
;	I have no idea why, but according to the Google translation of
;
;		http://avionics.game.coocan.jp/mypc/saj-98.html
;
;	it was made obsolete as soon as the PC-9801-86 board came out?
;	Or maybe Amusement Makers just didn't have one lying around?
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
;	ZUN
;
; Revision History:
;	93/ 5/ 2 Initial:jsstart.asm/master.lib 0.16
;	93/ 5/10 SAJ-98対応できたかなあ?
;	93/ 6/22 [M0.19] SAJ-98優先に変更
;	TH03     ZUN removes SAJ-98 support again

func JS_START	; {
	; サウンドボード検査

	mov	CX,256

	mov	DX,188h
LO1:
	in	AL,DX
	inc	AL
	jnz	short ARU
	loop	short LO1
NAI:
	xor	AX,AX	; ない
	jmp	short OWARI
ARU:
	pushf
	CLI
	mov	BH,07h
	call	SOUND_I
	and	AL,3fh
	or	AL,80h	; reg 7 の上位2bitを 10 にする
	mov	BL,AL
	call	SOUND_O
	popf

	mov	AX,1

OWARI:
	mov	js_bexist,AX
	ret
endfunc		; }
