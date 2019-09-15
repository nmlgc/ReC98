; void pascal near bb_curvebullet_load(void);
public BB_CURVEBULLET_LOAD
bb_curvebullet_load	proc near
	mov	ax, 3D00h
	mov	dx, offset aLs00_bb
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	mov	ah, 3Fh
	mov	dx, offset _bb_curvebullet
	mov	cx, BB_SIZE
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	retn
bb_curvebullet_load	endp
	nop
