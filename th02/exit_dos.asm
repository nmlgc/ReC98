public GAME_EXIT_TO_DOS
game_exit_to_dos	proc far
	push	bp
	mov	bp, sp
	nopcall	game_exit
	call	key_beep_on
	call	text_systemline_show
	call	text_cursor_show
	pop	bp
	retf
game_exit_to_dos	endp
