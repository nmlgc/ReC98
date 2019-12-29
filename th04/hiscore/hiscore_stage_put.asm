public HISCORE_STAGE_PUT
hiscore_stage_put	proc near

@@g_stage	= word ptr  4
@@y		= word ptr  6
@@x		= word ptr  8

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, [bp+@@x]
	mov	di, [bp+@@y]
	cmp	[bp+@@g_stage], g_NONE
	jz	short @@put_empty
	lea	ax, [si+2]
	push	ax
	lea	ax, [di+2]
	push	ax
	push	[bp+@@g_stage]
	push	14
	call	graph_gaiji_putc
	push	si
	push	di
	push	[bp+@@g_stage]
	jmp	short @@put_main
; ---------------------------------------------------------------------------

@@put_empty:
	lea	ax, [si+2]
	push	ax
	lea	ax, [di+2]
	push	ax
	push	(g_HISCORE_STAGE_EMPTY shl 16) or 14
	call	graph_gaiji_putc
	push	si
	push	di
	push	g_HISCORE_STAGE_EMPTY

@@put_main:
	push	7
	call	graph_gaiji_putc
	pop	di
	pop	si
	pop	bp
	retn	6
hiscore_stage_put	endp
