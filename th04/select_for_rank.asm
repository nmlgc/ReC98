; Returns the parameter for the current difficulty. The ASM always passes the
; 4 parameters with two 32-bit pushes, whose visual layout matches the
; parameter list:
;
; 	push	([for_easy] shl 16) or  [for_normal]
; 	push	([for_hard] shl 16) or [for_lunatic]

; int pascal far select_for_rank(
; 	int for_easy, int for_normal,
; 	int for_hard, int for_lunatic
; );
public select_for_rank
select_for_rank	proc far
	mov	al, _rank

select_for:
	xor	ah, ah
	add	ax, ax
	mov	bx, 0Ah
	sub	bx, ax
	add	bx, sp
	mov	ax, ss:[bx]
	retf	8
select_for_rank	endp
