; void* pascal near bb_load(const char far *fn);
public bb_load
bb_load	proc near
	push	si
	call	hmem_allocbyte pascal, BB_SIZE
	mov	_bb_load_seg, ax
	mov	bx, sp
	mov	si, ds
	mov	ax, 3D00h
	lds	dx, ss:[bx+4]
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	mov	ds, si
	mov	ds, _bb_load_seg
	mov	cx, BB_SIZE
	xor	dx, dx
	mov	ah, 3Fh
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	mov	ds, si
	pop	si
	mov	ax, _bb_load_seg
	retn	4
bb_load	endp
	nop
