; Draws the hardcoded spark sprite with the given ID, with ([x], [vram_y])
; pointing to the top-left point. Assumptions:
; • The GRCG is active, and set to the intended color
; • [sprite_id] ≤ SPARK_SPRITES

; void pascal near spark_render(int x, int vram_y, int sprite_id);
spark_render	proc near
@@sprite_id	= word ptr  4
@@vram_y   	= word ptr  6
@@x        	= word ptr  8

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	mov	bx, [bp+@@x]
	mov	ax, bx
	sar	ax, 3	; x /= 8
	mov	dx, [bp+@@vram_y]
	shl	dx, 6	; [vram_y] * 64
	add	ax, dx
	shr	dx, 2	; (([vram_y] * 64) / 4) = [vram_y] * 16
	add	ax, dx
	mov	di, ax	; ([vram_y] * 64) + ([vram_y] * 16) = [vram_y * ROW_SIZE]
	mov	ax, bx
	and	ax, 7	; [x] & 7
	shl	ax, 7	; *= SPARK_SIZE * SPARK_SPRITES (offset of X-shifted sprite)
	mov	dx, [bp+@@sprite_id]
	shl	dx, 4	; sprite_ptr = [sprite_id] * SPARK_SIZE
	add	ax, dx
	add	ax, offset sSPARKS
	mov	si, ax
	mov	cx, SPARK_H

@@blit_loop:
	movsw
	add	di, (ROW_SIZE - SPARK_VRAM_W)
	cmp	di, PLANE_SIZE
	jl	short @@next_row
	sub	di, PLANE_SIZE

@@next_row:
	loop	@@blit_loop
	pop	di
	pop	si
	pop	bp
	retn	6
spark_render	endp
	even
