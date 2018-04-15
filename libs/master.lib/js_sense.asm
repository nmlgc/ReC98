; master library - PC-9801
;
; Description:
;	ジョイスティック(キーボード)リアルタイム入力(js_sense)
;;
; Function/Procedures:
;	int js_sense( void ) ;
;
; Parameters:
;	none
;
; Returns:
;	Current state of joystick 1 if it's connected, garbage otherwise
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
;	先に js_start()によってジョイスティックを使用するように初期設定されて
;	いないと、ジョイスティックを無視します。
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
;	93/ 5/ 2 Initial:jssense.asm/master.lib 0.16
;	93/ 5/10 SAJ-98に対応したのかなあ?
;	94/ 2/28 [M0.23] js_2player, js_shift, js_keyassign対応…
;	94/ 7/ 3 [M0.23] ESCキー状態を1P4の上(1P5?)に乗せた
;	TH03     ZUN removes:
;	         • SENSE_KEY (internal keyboard → joystick mapping, would have
;	           allowed the caller to support both by just using the js_* API)
;	         • SAJ-98 support
;	         • the reliablility of js_sense()'s return value (AX remains
;	           unchanged if no joystick is connected)
;	         • Support for two joysticks in general
;	         • js_sense2() (fills js_stat[] with just the keyboard input)
;	TH04     ZUN further reduces js_sense() to the bare minimum of
;	         instructions, even moving the joystick existence check to the
;	         call site.

SOUND_JOY proc near
	mov	BH,0fh
	call	SOUND_O

	mov	DX,188h
	mov	AL,0eh
	out	DX,AL

	inc	DX
	inc	DX
	in	AL,DX
	not	AL
	ret
SOUND_JOY endp

func JS_SENSE	; {
if GAME eq 3
	push	BP
	push	SI	; joy stick 1
	push	DI	; joy stick 2
	xor	BP,BP

	cmp	js_bexist,0
	je	short NO_STICK
endif
	pushf
	CLI
	; ジョイスティックからの読み取り

	mov	BL,080h		; JOYSTICK1
	call	SOUND_JOY
	and	AX,003fh	; b,a,right,left,forward,back
if GAME eq 3
	mov	SI,AX
	popf

NO_STICK:
	or	js_stat,SI

	pop	DI
	pop	SI
	pop	BP
else
	popf
endif
	ret
endfunc		; }


SAJOUT	proc near
	xchg	DX,BX
	out	DX,AL
	xchg	DX,BX
	in	AL,DX
	not	AL
	ret
SAJOUT	endp
