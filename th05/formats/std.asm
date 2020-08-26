; TH05 adds stage and BGM titles to the format, and assumes that the tile
; section IDs come pre-multiplied by the element size of the section offset
; lookup array – see tiles_fill_initial() for details. The rest of the format
; is identical to TH04.

; void pascal near std_load(void);
public STD_LOAD
std_load	proc near
	push	si
	push	di
	push	ds
	call	std_free
	mov	al, _stage_id
	add	al, '0'
	mov	byte ptr _std_fn+3, al
	mov	dx, offset _std_fn
	mov	ax, 3D00h
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	mov	dx, offset _std_size
	mov	ah, 3Fh
	mov	cx, 2
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	push	bx
	mov	si, _std_size
	call	hmem_allocbyte pascal, si
	mov	_std_seg, ax
	mov	ds, ax
	mov	es, ax
	assume es:nothing
	xor	di, di
	pop	bx
	mov	dx, di
	mov	ah, 3Fh
	mov	cx, si
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	pop	ds
	mov	word ptr _stage_title+2, es
	mov	word ptr _stage_title, di
	xor	ax, ax
	mov	cx, 0FFFFh
	repne scasb
	mov	word ptr _stage_bgm_title+2, es
	mov	word ptr _stage_bgm_title, di
	repne scasb
	mov	word ptr _boss_bgm_title+2, es
	mov	word ptr _boss_bgm_title, di
	repne scasb
	lea	ax, [di+5]
	mov	_tile_section_ptr, ax
	mov	_tile_row_in_section, 0
	movzx	ax, byte ptr es:[di]
	inc	ax
	add	di, ax
	lea	ax, [di+5]
	mov	_tile_scrollspeed_ptr, ax
	movzx	ax, byte ptr es:[di]
	mov	_scroll_speed, al
	inc	ax
	add	di, ax
	mov	dl, es:[di]
	inc	di
	mov	bx, offset _enemy_script_ptrs

@@enemy_script_loop:
	movzx	ax, byte ptr es:[di]
	inc	di
	mov	[bx], di
	add	bx, 2
	add	di, ax
	dec	dl
	jnz	short @@enemy_script_loop
	inc	di
	mov	word ptr _std_ip+2, es
	mov	word ptr _std_ip, di
	setfarfp	_stage_vm, std_run
	pop	di
	pop	si
	retn
std_load	endp


; void pascal near std_free(void);
public STD_FREE
std_free	proc near
	cmp	_std_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _std_seg
	mov	_std_seg, 0

@@ret:
	retn
std_free	endp
	even
