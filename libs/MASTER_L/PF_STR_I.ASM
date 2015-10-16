; Moved out from pfopen.asm to a separate file and kept in libs/master_l/,
; since it's the only unmodified original procedure shared between all games
; that use pfopen().

;-----------------------------------------------------------------------------
;	int str_ieq(const char far *s1,const char MASTER_PTR *s2);
;		文字列s1とs2を大文字小文字を同一視して比較し、
;		equalとき0以外(zf=0)、not equalのとき0(zf=1)を返す
;-----------------------------------------------------------------------------
STR_IEQ	proc near	; {
	push	BP
	mov	BP,SP
	push	SI
	_push	DS

	;arg	s1:dataptr,s2:dataptr
	s1	= (1+1+DATASIZE)*2
	s2	= (1+1)*2

	CLD
	les	BX,[BP+s1]
	_lds	SI,[BP+s2]

	EVEN
STR_IEQ_loop:
	mov	AH,ES:[BX]
	inc	BX
	lodsb

	sub	AL,'a'
	cmp	AL,'z' - 'a'
	ja	short STR_IEQ_1
	sub	AL,'a' - 'A'	; toupper
STR_IEQ_1:
	sub	AH,'a'
	cmp	AH,'z' - 'a'
	ja	short STR_IEQ_2
	sub	AH,'a' - 'A'	; toupper
STR_IEQ_2:
	cmp	AH,AL
	jne	short STR_IEQ_noteq

	add	AL,'a'
	jnz	short STR_IEQ_loop
	jmp	short STR_IEQ_ret

STR_IEQ_noteq:
	xor	AX,AX
STR_IEQ_ret:
	test	AX,AX
	_pop	DS
	pop	SI
	pop	BP
	ret	(DATASIZE+2)*2
STR_IEQ	endp		; }
