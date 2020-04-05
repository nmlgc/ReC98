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
	cmp	bx, RES_Y - SPARK_H
	ja	short @@ywrap_needed
	mov	cx, SPARK_H	; CX = # of rows copied *before* Y wrap
	xor	bx, bx     	; BX = # of rows copied *after* Y wrap
	jmp	short @@blit_loop

@@ywrap_needed:
	mov	cx, RES_Y
	sub	cx, bx
	mov	bx, SPARK_H
	sub	bx, cx

@@blit_loop:
	lodsw
	or	ah, ah
	jz	short @@8px
	mov	es:[di], ax
	jmp	short @@next_row

@@8px:
	or	al, al
	jz	short @@next_row
	mov	es:[di], al

@@next_row:
	add	di, ROW_SIZE
	loop	@@blit_loop
	or	bx, bx
	jz	short @@ret
	sub	di, PLANE_SIZE
	xchg	cx, bx
	jmp	short @@blit_loop

@@ret:
	pop	di
	pop	si
	retn
@spark_render	endp
	even
