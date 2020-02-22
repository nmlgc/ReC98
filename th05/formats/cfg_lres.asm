public CFG_LOAD_RESIDENT
cfg_load_resident	proc near
	mov	ax, 3D00h
	mov	dx, offset _CFG_FN
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	mov	ah, 3Fh
	mov	dx, offset _cfg
	mov	cx, size cfg_t
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	mov	ax, _cfg.resident_sgm
	mov	word ptr _resident+2, ax
	mov	word ptr _resident, 0
	retn
cfg_load_resident	endp
	nop
