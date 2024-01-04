; int __pascal __near music_cmt_load(int track)
music_cmt_load	proc pascal near
	arg @@track:word
	local @@fn:dword

	push	si
	mov	word ptr @@fn+2, ds
	mov	word ptr @@fn, offset _a_Music0_txt
	les	bx, @@fn
	mov	al, byte ptr _game_sel
	add	al, '0'
	mov	es:[bx+6], al
	call	file_ropen pascal, word ptr @@fn+2, bx
	mov	ax, @@track
	imul	ax, MUSIC_CMT_LEN
	cwde
	call	file_seek pascal, eax, 0
	call	file_read pascal, ds, offset _music_cmt, MUSIC_CMT_LEN
	call	file_close
	xor	si, si
	jmp	short @@check

@@terminate_line:
	mov	bx, si
	imul	bx, MUSIC_CMT_LINE_LEN
	mov	(_music_cmt + MUSIC_CMT_LINE_LEN - 2)[bx], 0
	inc	si

@@check:
	cmp	si, MUSIC_CMT_LINE_COUNT
	jl	short @@terminate_line
	pop	si
	ret
music_cmt_load	endp
