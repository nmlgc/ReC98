; void pascal far hud_bar_put(
; 	utram_y_t y, unsigned char value, tram_atrb2 atrb
; );
public HUD_BAR_PUT
hud_bar_put	proc far

@@bar_notfull	= byte ptr -16h
@@bar_max    	= word ptr -0Ch
@@value_rem  	= word ptr -2
@@atrb       	= word ptr  6
@@value      	= word ptr  8
@@y          	= word ptr  0Ah

	push	bp
	mov	bp, sp
	sub	sp, 16h
	push	si
	push	di
	mov	di, [bp+@@value]
	mov	ax, word ptr _hud_bar_max + 0
	mov	word ptr [bp+@@bar_max + 0], ax
	mov	ax, word ptr _hud_bar_max + 2
	mov	word ptr [bp+@@bar_max + 2], ax
	mov	ax, word ptr _hud_bar_max + 4
	mov	word ptr [bp+@@bar_max + 4], ax
	mov	ax, word ptr _hud_bar_max + 6
	mov	word ptr [bp+@@bar_max + 6], ax
	mov	al, byte ptr _hud_bar_max + 8
	mov	byte ptr [bp+@@bar_max + 8], al
	cmp	di, BAR_MAX
	jl	short @@below_max
	push	HUD_LEFT
	push	[bp+@@y]
	push	ss
	lea	ax, [bp+@@bar_max]
	jmp	short @@put
; ---------------------------------------------------------------------------

@@below_max:
	mov	[bp+@@value_rem], di
	sub	[bp+@@value_rem], BAR_GAIJI_MAX
	xor	si, si
	jmp	short @@cell_still_fully_filled?
; ---------------------------------------------------------------------------

@@cell_is_fully_filled:
	mov	[bp+si+@@bar_notfull], g_BAR_16W
	sub	[bp+@@value_rem], BAR_GAIJI_MAX
	inc	si

@@cell_still_fully_filled?:
	cmp	[bp+@@value_rem], 0
	jg	short @@cell_is_fully_filled
	lea	ax, [di-1]
	and	ax, BAR_GAIJI_MAX - 1
	mov	[bp+@@value_rem], ax
	mov	al, byte ptr [bp+@@value_rem]
	add	al, G_BAR
	mov	[bp+si+@@bar_notfull], al
	jmp	short @@empty_cells_left?
; ---------------------------------------------------------------------------

@@still_empty_cells_left:
	mov	[bp+si+@@bar_notfull], g_EMPTY

@@empty_cells_left?:
	inc	si
	cmp	si, 7
	jle	short @@still_empty_cells_left
	mov	[bp+@@bar_notfull+8], 0
	push	HUD_LEFT
	push	[bp+@@y]
	push	ss
	lea	ax, [bp+@@bar_notfull]

@@put:
	push	ax
	push	[bp+@@atrb]
	call	gaiji_putsa
	pop	di
	pop	si
	leave
	retf	6
hud_bar_put	endp
