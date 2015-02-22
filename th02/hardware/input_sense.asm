; void DEFCONV input_sense(void);
proc_defconv input_sense
	mov	_input, 0
	mov	al, 7
	mov	ah, 4
	int	18h
	mov	bh, ah
	mov	al, 8
	mov	ah, 4
	int	18h
	test	bh, 4
	jnz	short @@up
	test	ah, 8
	jz	short @@left?

@@up:
	or	_input, INPUT_UP

@@left?:
	test	bh, 8
	jnz	short @@left
	test	ah, 40h
	jz	short @@num7?

@@left:
	or	_input, INPUT_LEFT

@@num7?:
	test	ah, 4
	jz	short @@num9?
	or	_input, INPUT_UP_LEFT

@@num9?:
	test	ah, 10h
	jz	short @@down?
	or	_input, INPUT_UP_RIGHT

@@down?:
	mov	al, 9
	mov	ah, 4
	int	18h
	test	bh, 20h
	jnz	short @@down
	test	ah, 8
	jz	short @@right?

@@down:
	or	_input, INPUT_DOWN

@@right?:
	test	bh, 10h
	jnz	short @@right
	test	ah, 1
	jz	short @@num1?

@@right:
	or	_input, INPUT_RIGHT

@@num1?:
	test	ah, 4
	jz	short @@num3?
	or	_input, INPUT_DOWN_LEFT

@@num3?:
	test	ah, 10h
	jz	short @@z?
	or	_input, INPUT_DOWN_RIGHT

@@z?:
	mov	al, 5
	mov	ah, 4
	int	18h
	test	ah, 2
	jz	short @@x?
	or	_input, INPUT_SHOT

@@x?:
	test	ah, 4
	jz	short @@esc?
	or	_input, INPUT_BOMB

@@esc?:
	mov	al, 0
	mov	ah, 4
	int	18h
	test	ah, 1
	jz	short @@return?
	or	_input, INPUT_CANCEL

@@return?:
	mov	al, 3
	mov	ah, 4
	int	18h
	test	ah, 10h
	jz	short @@q?
	or	_input, INPUT_OK

@@q?:
	mov	al, 2
	mov	ah, 4
	int	18h
	test	ah, 1
	jz	short @@space?
	or	_input, INPUT_Q

@@space?:
	mov	al, 6
	mov	ah, 4
	int	18h
	test	ah, 10h
	jz	short @@ret
	or	_input, INPUT_SHOT

@@ret:
	retf
endp_defconv
	even
