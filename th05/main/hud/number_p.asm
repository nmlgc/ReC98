	.386
	.model use16 large

include libs/master.lib/master.inc
include th02/score.inc
include th04/gaiji/gaiji.inc

extrn _hud_gaiji_row:byte:SCORE_DIGITS
extern _SEVEN_DIGIT_POWERS_OF_10:dword:7

	.code

@@divisor = bx

public @HUD_5_DIGIT_PUT$QUIUIUIUI
@hud_5_digit_put$quiuiuiui proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@atrb:word, @@val:word, @@y:word, @@left:word

	push	bp
	mov 	bp, sp
	push	di
; ZUN bloat: Avoid LEA being turned into MOV for immediate addresses
pushstate
nosmart
	lea  	di, (_hud_gaiji_row + (SCORE_DIGITS - 5))
	movzx	edx, @@val
	lea  	@@divisor, (_SEVEN_DIGIT_POWERS_OF_10 + (2 * dword)) ; 10,000
popstate
	mov	ax, @@atrb
	mov	cx, 4	; CH = 0 (omit leading zeroes), CL = 4 ((5 - 1) iterations)
	jmp	short digits_put
@hud_5_digit_put$quiuiuiui endp
	even


public @HUD_POINTS_PUT$QUIUIUL
@hud_points_put$quiuiul proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@points:dword, @@y:word, @@left:word

	push	bp
	mov 	bp, sp
	push	di
	mov 	edx, @@points
	mov 	di, offset _hud_gaiji_row
	mov 	ax, TX_WHITE

	; Set the "continues used" digit to zero to make all point values appear as
	; a multiple of 10.
	mov	_hud_gaiji_row[SCORE_DIGITS - 1], gb_0_

	mov	@@divisor, offset _SEVEN_DIGIT_POWERS_OF_10 ; 1,000,000

	; CH = 0 (omit leading zeroes), CL = 6 ((7 - 1) iterations)
	mov	cx, (SCORE_DIGITS - 2)

digits_put:
	push	@@left	; x
	push	@@y	; y
	push	ds	; str (segment)
	push	di	; str (offset)
	push	ax	; atrb
	mov 	ax, ds
	mov 	es, ax

@@digit_loop:
	mov	eax, edx ; Previous remainder = new dividend
	xor	edx, edx
	div	dword ptr [@@divisor] ; EAX = quotient, EDX = remainder
	or 	ch, al
	jz 	short @@omit_leading_zeroes
	add	al, gb_0_
	jmp	short @@digit_next

@@omit_leading_zeroes:
	mov	al, g_EMPTY

@@digit_next:
	stosb
	add	@@divisor, dword
	dec	cl
	jnz	short @@digit_loop

	; Reuse the remainder from the final division and unconditionally display
	; it as a number to ensure that we display at least "0".
	add	dl, gb_0_
	mov	[di], dl

	call	gaiji_putsa
	pop 	di
	pop 	bp
	retf	8
@hud_points_put$quiuiul endp

	end
