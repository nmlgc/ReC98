public _scoredat_load_for_cur
_scoredat_load_for_cur proc near
	mov	ax, 3D00h
	mov	dx, offset aGENSOU_SCR
	int	21h		; DOS - 2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX -> ASCIZ filename
				; AL = access mode
				; 0 - read
	jnb	short @@read
	retn
; ---------------------------------------------------------------------------

@@read:
	mov	bx, ax
	xor	ah, ah
	mov	al, _playchar
	imul	ax, RANK_COUNT
	add	al, _rank
	imul	ax, size scoredat_section_t
	mov	dx, ax
	xor	cx, cx
	mov	ax, 4200h
	int	21h		; DOS - 2+ - MOVE FILE READ/WRITE POINTER (LSEEK)
				; AL = method: offset from beginning of file
	mov	ah, 3Fh
	mov	dx, offset _hi
	mov	cx, size scoredat_section_t
	int	21h		; DOS - 2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number of bytes to read
				; DS:DX -> buffer
	mov	ah, 3Eh
	int	21h		; DOS - 2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	call	scoredat_decode
	retn
_scoredat_load_for_cur endp
