public SND_DETERMINE_MODES
snd_determine_modes	proc
@@req_se_mode	= word ptr (cPtrSize + 2)
@@req_bgm_mode	= word ptr (cPtrSize + 4)

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@req_bgm_mode]
	mov	di, [bp+@@req_se_mode]
	nopcall	snd_pmd_resident
	cmp	si, SND_BGM_MIDI
	jne	short @@check_PMD
	nopcall	snd_mmd_resident

@@check_PMD:
	mov	ah, PMD_GET_DRIVER_VERSION
	int	60h
	cmp	al, -1
	jne	short @@got_PMD
	mov	_snd_bgm_mode, SND_BGM_OFF
	jmp	short @@FM_SE_requested?

@@got_PMD:
	or	al, al	; 1 == running a 26 board, 2 == running a 86 board
	jne	short @@got_PMD86
	mov	_snd_bgm_mode, SND_BGM_FM26
	jmp	short @@FM_SE_requested?

@@got_PMD86:
	mov	_snd_bgm_mode, SND_BGM_FM86

@@FM_SE_requested?:
	cmp	di, SND_SE_FM
	jne	short @@Beep_SE_requested?
	cmp	_snd_bgm_mode, SND_BGM_OFF
	je	short @@FM_SE_requested_but_got_no_board
	mov	ax, SND_SE_FM
	jmp	short @@decide_SE_if_FM_requested

@@FM_SE_requested_but_got_no_board:
	xor	ax, ax

@@decide_SE_if_FM_requested:
	mov	_snd_se_mode, al
	jmp	short @@do_we_even_want_BGM?

@@Beep_SE_requested?:
	cmp	di, SND_SE_BEEP
	jne	short @@no_SE_requested
	mov	_snd_se_mode, SND_SE_BEEP
	jmp	short @@do_we_even_want_BGM?

@@no_SE_requested:
	mov	_snd_se_mode, SND_SE_OFF

; Since we tentatively set snd_bgm_mode when checking the driver above...
@@do_we_even_want_BGM?:
	or	si, si
	jne	short @@MIDI_requested?
	mov	_snd_bgm_mode, SND_BGM_OFF
	jmp	short @@ret

@@MIDI_requested?:
	cmp	si, SND_BGM_MIDI
	jnz	short @@FM26_requested?
	cmp	_snd_midi_possible, 0
	jz	short @@FM26_requested?
	mov	_snd_bgm_mode, SND_BGM_MIDI
	jmp	short @@ret

@@FM26_requested?:
	cmp	si, SND_BGM_FM26
	jnz	short @@ret
	cmp	_snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret
	mov	_snd_bgm_mode, SND_BGM_FM26

@@ret:
	mov	al, _snd_bgm_mode
	mov	ah, 0
	pop	di
	pop	si
	pop	bp
	ret	4
snd_determine_modes	endp
