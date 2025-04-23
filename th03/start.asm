public START_DEMO
start_demo	proc near
	push	bp
	mov	bp, sp
	push	si
	les	bx, _resident
	mov	es:[bx+resident_t.RESIDENT_is_cpu][0], 1
	mov	es:[bx+resident_t.RESIDENT_is_cpu][1], 1
	inc	es:[bx+resident_t.demo_num]
	cmp	es:[bx+resident_t.demo_num], DEMO_COUNT
	jbe	short @@next_demo
	mov	es:[bx+resident_t.demo_num], 1

@@next_demo:
	les	bx, _resident
	mov	es:[bx+resident_t.pid_winner], 0
	mov	es:[bx+resident_t.story_stage], 0
	mov	es:[bx+resident_t.game_mode], GM_DEMO
	mov	es:[bx+resident_t.show_score_menu], 0
	mov	al, es:[bx+resident_t.demo_num]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	mov	al, (_demo_chars - (PLAYER_COUNT * byte))[bx]
	mov	bx, word ptr _resident
	mov	es:[bx+resident_t.RESIDENT_playchar_paletted][0], al
	mov	al, es:[bx+resident_t.demo_num]
	mov	ah, 0
	add	ax, ax
	mov	dx, offset (_demo_chars - (PLAYER_COUNT * byte))
	inc	dx
	add	ax, dx
	mov	bx, ax
	mov	al, [bx]
	mov	bx, word ptr _resident
	mov	es:[bx+resident_t.RESIDENT_playchar_paletted][1], al
	mov	al, es:[bx+resident_t.demo_num]
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	mov	eax, (_demo_rand - dword)[bx]
	mov	bx, word ptr _resident
	mov	es:[bx+resident_t.rand], eax
	xor	si, si
	jmp	short @@score_more?
; ---------------------------------------------------------------------------

@@score_loop:
	les	bx, _resident
	add	bx, si
	mov	es:[bx+resident_t.score_last], 0
	inc	si

@@score_more?:
	cmp	si, (PLAYER_COUNT * SCORE_DIGITS)
	jl	short @@score_loop
	call	palette_black_out pascal, 1
	call	@cfg_save$qv
	call	gaiji_restore
	kajacall	KAJA_SONG_STOP
	call	@game_exit$qv
	call	_execl c, offset _BINARY_MAINL, ds, offset _BINARY_MAINL, ds, large 0
	pop	si
	pop	bp
	retn
start_demo	endp
