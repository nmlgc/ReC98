VERDICT_BITMAP_W = 320
VERDICT_SCREEN_H = 352
VERDICT_BITMAP_VRAM_W = (VERDICT_BITMAP_W / 8)
VERDICT_SCREEN_SIZE = (VERDICT_SCREEN_H * VERDICT_BITMAP_VRAM_W)

public VERDICT_BITMAP_SNAP
verdict_bitmap_snap	proc near

@@bitmap_offset	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	push	di
	push	ds
	push	ds
	pop	es
	assume es:_DATA
	mov	ax, SEG_PLANE_E
	mov	ds, ax
	assume ds:nothing
	xor	si, si
	mov	di, [bp+@@bitmap_offset]
	add	di, offset _verdict_bitmap
	mov	ax, VERDICT_SCREEN_H

@@snap_loop:
	mov	cx, (VERDICT_BITMAP_VRAM_W / 2)
	rep movsw
	add	si, (ROW_SIZE - VERDICT_BITMAP_VRAM_W)
	dec	ax
	jnz	short @@snap_loop
	pop	ds
	assume ds:_DATA
	pop	di
	pop	si
	pop	bp
	retn	2
verdict_bitmap_snap endp


public VERDICT_BITMAP_PUT
verdict_bitmap_put proc near

@@bitmap_offset		= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	grcg_setcolor pascal, (GC_TDW shl 16) + 1
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	xor	di, di
	mov	dx, VERDICT_SCREEN_H

@@clear_loop:
	mov	cx, (VERDICT_BITMAP_VRAM_W / 2)
	rep stosw
	add	di, (ROW_SIZE - VERDICT_BITMAP_VRAM_W)
	dec	dx
	jnz	short @@clear_loop
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 13
	xor	di, di
	mov	si, [bp+@@bitmap_offset]
	add	si, offset _verdict_bitmap
	mov	dx, VERDICT_SCREEN_H

@@put_loop:
	mov	cx, (VERDICT_BITMAP_VRAM_W / 2)
	rep movsw
	add	di, (ROW_SIZE - VERDICT_BITMAP_VRAM_W)
	dec	dx
	jnz	short @@put_loop
	GRCG_OFF_CLOBBERING dx
	pop	di
	pop	si
	pop	bp
	retn	2
verdict_bitmap_put endp
