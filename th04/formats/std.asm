; void std_load();
public std_load
std_load	proc near
@@enemy_script_count	= byte ptr -4
@@chunk_size	= byte ptr -3
@@std_size 	= word ptr -2

	enter	4, 0
	push	si
	push	di
	call	std_free
	les	bx, _humaconfig
	mov	al, es:[bx+13h]
	les	bx, _std_fn
	mov	es:[bx+3], al
	call	file_ropen pascal, word ptr _std_fn+2, bx
	push	ss
	lea	ax, [bp+@@std_size]
	call	file_read pascal, ax, 2
	push	ss
	lea	ax, [bp+@@chunk_size]
	call	file_read pascal, ax, 1
	dec	[bp+@@std_size]
	call	hmem_allocbyte pascal, [bp+@@std_size]
	mov	_std_seg, ax
	mov	es, _std_seg
	xor	si, si
	call	file_read pascal, es, si, [bp+@@std_size]
	call	file_close
	mov	es, _std_seg
	mov	_tile_section, 4
	mov	_tile_row_in_section, 0
	mov	al, [bp+@@chunk_size]
	mov	ah, 0
	add	si, ax
	mov	al, es:[si]
	mov	[bp+@@chunk_size], al
	lea	ax, [si+5]
	mov	_tile_scrollspeed_ptr, ax
	mov	al, es:[si]
	mov	_scroll_speed, al
	mov	al, [bp+@@chunk_size]
	mov	ah, 0
	inc	ax
	add	si, ax
	xor	di, di
	mov	al, es:[si]
	mov	[bp+@@enemy_script_count], al
	inc	si

@@enemy_script_loop:
	mov	al, es:[si]
	mov	[bp+@@chunk_size], al
	inc	si
	mov	bx, di
	add	bx, bx
	mov	_enemy_script_ptrs[bx], si
	inc	di
	mov	ah, 0
	add	si, ax
	dec	[bp+@@enemy_script_count]
	cmp	[bp+@@enemy_script_count], 0
	ja	short @@enemy_script_loop
	inc	si
	mov	word ptr _std_ip+2,	es
	mov	word ptr _std_ip, si
	setfarfp	_stage_vm, std_run
	pop	di
	pop	si
	leave
	ret
std_load	endp


; void std_free();
public std_free
std_free	proc near
	push	bp
	mov	bp, sp
	cmp	_std_seg, 0
	jz	short @@ret
	call	hmem_free pascal, _std_seg
	mov	_std_seg, 0

@@ret:
	pop	bp
	retn
std_free	endp
