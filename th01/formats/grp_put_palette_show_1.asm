public GRP_PUT_PALETTE_SHOW_1
grp_put_palette_show_1	proc far

@@fn		= dword ptr  6

	push	bp
	mov	bp, sp
	call	_graph_accesspage_func stdcall, 1
	pop	cx
	call	_grp_put_palette_show c, word ptr [bp+@@fn], word ptr [bp+@@fn+2]
	pop	bp
	retf	4
grp_put_palette_show_1	endp
