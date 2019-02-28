; void near bb_txt_load(void);
public bb_txt_load
bb_txt_load	proc near
	call	hmem_allocbyte pascal, BB_SIZE + (BB_SIZE / 2)
	mov	_bb_txt_seg, ax
	mov	ax, 3D00h
	mov	dx, offset aTxt1_bb
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	push	ds
	mov	ds, _bb_txt_seg
	mov	cx, BB_SIZE
	xor	dx, dx
	mov	ah, 3Fh
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	pop	ds
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	mov	byte ptr aTxt1_bb+3, '2'
	mov	ax, 3D00h
	mov	dx, offset aTxt1_bb
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	push	ds
	mov	ds, _bb_txt_seg
	mov	cx, (BB_SIZE / 2)
	mov	dx, BB_SIZE
	mov	ah, 3Fh
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	pop	ds
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	retn
bb_txt_load	endp


; void near bb_txt_free(void);
public bb_txt_free
bb_txt_free	proc near
	cmp	_bb_txt_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _bb_txt_seg
	mov	_bb_txt_seg, 0

@@ret:
	retn
bb_txt_free	endp
	nop
