; int __pascal __near music_cmt_load(int track)
music_cmt_load	proc pascal near
@@track	= word ptr [bp+4]

	push	bp
	mov	bp, sp
	push	si
	call	file_ropen pascal, ds, offset _aMUSIC_TXT
	mov	ax, @@track
	imul	ax, MUSIC_CMT_LEN
if GAME ge 3
	cwde
	call	file_seek pascal, eax, 0
else
	cwd
	call	file_seek pascal, dx, ax, 0
endif
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
	pop	bp
	ret	2
music_cmt_load	endp
