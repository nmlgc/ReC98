; Returns the parameter for the current player character. The ASM always
; passes the 4 parameters with two 32-bit pushes, whose visual layout matches
; the parameter list:
;
; 	push	([for_reimu] shl 16) or [for_marisa]
; 	push	( [for_mima] shl 16) or  [for_yuuka]

; int pascal far select_for_playchar(
; 	int for_reimu, int for_marisa,
; 	int for_mima, int for_yuuka
; );
public SELECT_FOR_PLAYCHAR
select_for_playchar	proc far
	mov	al, playchar
	jmp	short select_for
select_for_playchar	endp
	nop
