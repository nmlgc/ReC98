if GAME eq 4
; Yes, specific to the bonus popup, due to the hardcoded position.
public POPUP_PUT_POINTS_TH04
popup_put_points_th04 proc pascal near
	arg  	@@points:dword
	local	@@digit:dword, @@divisor:dword, @@buf:byte:SCORE_DIGITS + 2 ; padding...

	push	si
	push	di
	mov	@@divisor, 1000000
	xor	si, si
	xor	di, di
	jmp	short @@more_digits?
; ---------------------------------------------------------------------------

@@digit_loop:
	mov	eax, @@points
	xor	edx, edx
	div	@@divisor
	mov	@@digit, eax
	mov	eax, @@points
	xor	edx, edx
	div	@@divisor
	mov	@@points, edx
	or	di, word ptr @@digit
	or	di, di
	jz	short @@omit_leading_zeroes
	mov	al, byte ptr @@digit
	add	al, GB_DIGITS
	mov	@@buf[si], al
	jmp	short @@divisor_next
; ---------------------------------------------------------------------------

@@omit_leading_zeroes:
	mov	@@buf[si], g_EMPTY

@@divisor_next:
	mov	ebx, 10
	mov	eax, @@divisor
	xor	edx, edx
	div	ebx
	mov	@@divisor, eax
	inc	si

@@more_digits?:
	cmp	@@divisor, 1
	ja	short @@digit_loop
	mov	al, byte ptr @@points
	add	al, gb_0_
	mov	@@buf[SCORE_DIGITS - 2], al   	; (ones)
	mov	@@buf[SCORE_DIGITS - 1], gb_0_	; ("continues used" digit)
	mov	@@buf[SCORE_DIGITS - 0], 0     	; (null terminator)
	push	((PLAYFIELD_TRAM_LEFT + (PLAYFIELD_TRAM_W / 2)) shl 16) + POPUP_TRAM_Y
	push	ss
	lea	ax, @@buf
	push	ax
	push	TX_WHITE
	call	gaiji_putsa
	pop	di
	pop	si
	ret
popup_put_points_th04 endp
endif
