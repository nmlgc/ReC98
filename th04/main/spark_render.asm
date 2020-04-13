; Draws the hardcoded spark sprite with the given ID, with ([x], [vram_y])
; pointing to the top-left point. Assumptions:
; • ES is already be set to the beginning of a VRAM segment
; • The GRCG is active, and set to the intended color

; void near fastcall spark_render(int x, int vram_y, int sprite_id);
public @spark_render
@spark_render	proc near
	push	si
	push	di
	mov	si, ax	; SI = [x]
	mov	bx, dx	; BX = [vram_y]
	sar	ax, 3	; x / 8
	shl	dx, 6	; [vram_y] * 64
	add	ax, dx
	shr	dx, 2	; (([vram_y] * 64) / 4) = [vram_y] * 16
	add	ax, dx
	mov	di, ax	; ([vram_y] * 64) + ([vram_y] * 16) = [vram_y * ROW_SIZE]
	and	si, 7	; [x] & 7
	mov	ax, si
	shl	si, 7	; *= SPARK_SIZE * SPARK_SPRITES (offset of X-shifted sprite)
	add	si, offset _sSPARKS
	and	cx, 7	; & (SPARK_SPRITES - 1)
	shl	cx, 4	; * SPARK_SIZE
	add	si, cx

	blit_dots16_empty2opt_emptyopt_roll	<bx>, SPARK_H

@@ret:
	pop	di
	pop	si
	retn
@spark_render	endp
	even
