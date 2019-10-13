public SHOT_CYCLE_INIT
shot_cycle_init	proc near

@@cycle_flag	= byte ptr [bp-1]

	enter	2, 0
	mov	@@cycle_flag, 0
	mov	al, _shot_time
	mov	ah, 0
	sub	ax, 3
	mov	bx, ax
	cmp	bx, 15
	ja	short @@cycle____
	add	bx, bx
	jmp	word ptr cs:@@time_to_cycle[bx]

@@cycle6321:
	mov	@@cycle_flag, SC_6X or SC_3X or SC_2X or SC_1X
	jmp	short @@snd

@@cycle6_2_:
	mov	@@cycle_flag, SC_6X or SC_2X
	jmp	short @@in_a_cycle

@@cycle63__:
	mov	@@cycle_flag, SC_6X or SC_3X

@@snd:
	call	snd_se_play pascal, 1
	jmp	short @@in_a_cycle

@@cycle6___:
	mov	@@cycle_flag, SC_6X
	jmp	short @@in_a_cycle

@@cycle____:
	mov	al, 0
	leave
	retn

@@in_a_cycle:
	mov	_shot_ptr, offset _shots
	mov	_shot_last_id, 0
	mov	al, @@cycle_flag
	leave
	retn

	db 0
@@time_to_cycle	label word
	dw @@cycle6___, @@cycle____, @@cycle____
	dw @@cycle63__, @@cycle____, @@cycle____
	dw @@cycle6_2_, @@cycle____, @@cycle____
	dw @@cycle63__, @@cycle____, @@cycle____
	dw @@cycle6___, @@cycle____, @@cycle____
	dw @@cycle6321
shot_cycle_init	endp
