public _graph_r_hline
_graph_r_hline	proc far

@@vram_row		= dword	ptr -0Ah
@@right_pixels		= byte ptr -6
@@left_pixels		= byte ptr -5
@@order_tmp		= word ptr -4
@@full_bytes_to_put		= word ptr -2
@@left		= word ptr  6
@@right		= word ptr  8
@@y		= word ptr  0Ah
@@col		= word ptr  0Ch

	enter	0Ah, 0
	push	si
	push	di
	mov	di, [bp+@@y]
	mov	ax, [bp+@@left]
	cmp	ax, [bp+@@right]
	jle	short @@clip_left?
	mov	[bp+@@order_tmp], ax
	mov	ax, [bp+@@right]
	mov	[bp+@@left], ax
	mov	ax, [bp+@@order_tmp]
	mov	[bp+@@right], ax

@@clip_left?:
	cmp	[bp+@@left], 0
	jge	short @@clip_right?
	cmp	[bp+@@right], 0
	jl	@@ret
	mov	[bp+@@left], 0

@@clip_right?:
	cmp	[bp+@@right], (RES_X - 1)
	jle	short @@setup_vram_pointer_and_edges
	cmp	[bp+@@left], (RES_X - 1)
	jg	@@ret
	mov	[bp+@@right], (RES_X - 1)

@@setup_vram_pointer_and_edges:
	mov	ax, [bp+@@right]
	mov	_graph_r_last_line_end.x, ax
	mov	_graph_r_last_line_end.y, di
	mov	ax, di
	imul	ax, ROW_SIZE
	push	ax
	mov	ax, [bp+@@left]
	mov	bx, 8
	cwd
	idiv	bx
	pop	dx
	add	dx, ax
	mov	word ptr [bp+@@vram_row+2], 0A800h
	mov	word ptr [bp+@@vram_row], dx
	mov	ax, [bp+@@right]
	cwd
	idiv	bx
	push	ax
	mov	ax, [bp+@@left]
	cwd
	idiv	bx
	pop	dx
	sub	dx, ax
	mov	[bp+@@full_bytes_to_put], dx
	mov	cl, byte ptr [bp+@@left]
	and	cl, 7
	mov	ax, 0FFh
	sar	ax, cl
	mov	[bp+@@left_pixels], al
	mov	al, byte ptr [bp+@@right]
	and	al, 7
	mov	cl, 7
	sub	cl, al
	mov	al, 0FFh
	shl	al, cl
	mov	[bp+@@right_pixels], al
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@restore?
	push	[bp+@@col]
	call	_grcg_setcolor_rmw
	pop	cx

@@restore?:
	cmp	_graph_r_restore_from_1, 0
	jz	short @@put
	push	1
	mov	ax, RES_X
	sub	ax, [bp+@@left]
	push	ax
	push	di
	push	[bp+@@left]
	call	_egc_copy_rect_1_to_0
	add	sp, 8
	jmp	short @@grcg_off?
; ---------------------------------------------------------------------------

@@put:
	cmp	[bp+@@full_bytes_to_put], 0
	jnz	short @@at_least_one_full_byte
	mov	al, [bp+@@left_pixels]
	and	al, [bp+@@right_pixels]
	les	bx, [bp+@@vram_row]
	assume es:nothing
	jmp	short @@put_edge
; ---------------------------------------------------------------------------

@@at_least_one_full_byte:
	les	bx, [bp+@@vram_row]
	mov	al, [bp+@@left_pixels]
	mov	es:[bx], al
	mov	si, 1
	jmp	short @@xloop_more?
; ---------------------------------------------------------------------------

@@xloop:
	les	bx, [bp+@@vram_row]
	add	bx, si
	mov	byte ptr es:[bx], 0FFh
	inc	si

@@xloop_more?:
	cmp	si, [bp+@@full_bytes_to_put]
	jl	short @@xloop
	les	bx, [bp+@@vram_row]
	add	bx, [bp+@@full_bytes_to_put]
	mov	al, [bp+@@right_pixels]

@@put_edge:
	mov	es:[bx], al

@@grcg_off?:
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@ret
	call	_grcg_off_func

@@ret:
	pop	di
	pop	si
	leave
	retf
_graph_r_hline	endp


public _graph_r_vline
_graph_r_vline	proc far

@@vram_row_offset		= word ptr -8
@@pattern		= word ptr -6
@@order_tmp		= word ptr -4
@@y		= word ptr -2
@@x		= word ptr  6
@@top		= word ptr  8
@@bottom		= word ptr  0Ah
@@col		= word ptr  0Ch

	enter	8, 0
	push	si
	push	di
	mov	si, [bp+@@top]
	mov	di, [bp+@@bottom]
	cmp	si, di
	jle	short @@clip_top?
	mov	[bp+@@order_tmp], si
	mov	si, di
	mov	di, [bp+@@order_tmp]

@@clip_top?:
	or	si, si
	jge	short @@clip_bottom?
	or	di, di
	jl	@@ret
	xor	si, si

@@clip_bottom?:
	cmp	di, (RES_Y - 1)
	jle	short @@restore?
	cmp	si, (RES_Y - 1)
	jg	@@ret
	mov	di, (RES_Y - 1)

@@restore?:
	mov	ax, [bp+@@x]
	mov	_graph_r_last_line_end.x, ax
	mov	_graph_r_last_line_end.y, di
	cmp	_graph_r_restore_from_1, 0
	jz	short @@setup_vram_offset_and_pattern
	mov	ax, di
	sub	ax, si
	push	ax
	push	16
	push	si
	push	[bp+@@x]
	call	_egc_copy_rect_1_to_0
	add	sp, 8
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@setup_vram_offset_and_pattern:
	mov	ax, [bp+@@x]
	sar	ax, 3
	mov	dx, si
	shl	dx, 6
	add	ax, dx
	mov	dx, si
	shl	dx, 4
	add	ax, dx
	mov	[bp+@@vram_row_offset], ax
	mov	cl, byte ptr [bp+@@x]
	and	cl, 7
	mov	ax, _graph_r_pattern
	shr	ax, cl
	mov	[bp+@@pattern], ax
	mov	al, byte ptr [bp+@@x]
	and	al, 7
	mov	cl, 16
	sub	cl, al
	mov	ax, _graph_r_pattern
	shl	ax, cl
	or	[bp+@@pattern], ax
	push	[bp+@@col]
	call	_grcg_setcolor_rmw
	pop	cx
	mov	[bp+@@y], si
	jmp	short @@yloop_more?
; ---------------------------------------------------------------------------

@@yloop:
	les	bx, _VRAM_PLANE_B
	add	bx, [bp+@@vram_row_offset]
	mov	ax, [bp+@@pattern]
	mov	es:[bx], ax
	add	[bp+@@vram_row_offset], ROW_SIZE
	inc	[bp+@@y]

@@yloop_more?:
	cmp	[bp+@@y], di
	jle	short @@yloop
	call	_grcg_off_func

@@ret:
	pop	di
	pop	si
	leave
	retf
_graph_r_vline	endp


public _graph_r_line_from_1
_graph_r_line_from_1	proc far

@@left		= word ptr  6
@@top		= word ptr  8
@@right		= word ptr  0Ah
@@bottom		= word ptr  0Ch

	push	bp
	mov	bp, sp
	mov	_graph_r_restore_from_1, 1
	push	7
	push	[bp+@@bottom]
	push	[bp+@@right]
	push	[bp+@@top]
	push	[bp+@@left]
	nopcall	_graph_r_line
	add	sp, 0Ah
	mov	_graph_r_restore_from_1, 0
	pop	bp
	retf
_graph_r_line_from_1	endp


public _graph_r_line_patterned
_graph_r_line_patterned	proc far

@@left		= word ptr  6
@@top		= word ptr  8
@@right		= word ptr  0Ah
@@bottom		= word ptr  0Ch
@@col		= word ptr  0Eh
@@pattern		= word ptr  10h

	push	bp
	mov	bp, sp
	mov	ax, [bp+@@pattern]
	mov	_graph_r_pattern, ax
	push	[bp+@@col]
	push	[bp+@@bottom]
	push	[bp+@@right]
	push	[bp+@@top]
	push	[bp+@@left]
	nopcall	_graph_r_line
	add	sp, 0Ah
	mov	_graph_r_pattern, 80h
	pop	bp
	retf
_graph_r_line_patterned	endp


public _graph_r_line
_graph_r_line	proc far

@@page1_B		= dword	ptr -28h
@@page1_R		= dword	ptr -24h
@@page1_G		= dword	ptr -20h
@@page1_E		= dword	ptr -1Ch
@@x87_tmp		= word ptr -18h
@@pixels		= word ptr -16h
@@y_vram		= word ptr -14h
@@x_vram		= word ptr -12h
@@tmp		= word ptr -10h
@@y_direction		= word ptr -0Eh
@@error		= word ptr -0Ch
@@h		= word ptr -0Ah
@@w		= word ptr -8
@@y_cur		= word ptr -6
@@x_cur		= word ptr -4
@@i		= word ptr -2
@@left		= word ptr  6
@@top		= word ptr  8
@@right		= word ptr  0Ah
@@bottom		= word ptr  0Ch
@@col		= word ptr  0Eh

	enter	28h, 0
	push	si
	push	di
	mov	di, [bp+@@top]
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@horizontal_only?
	mov	ax, [bp+@@left]
	cmp	ax, [bp+@@right]
	jnz	short @@horizontal_only?
	call	_graph_r_vline stdcall, ax, di, [bp+@@bottom], [bp+@@col]
	jmp	short @@add_sp_and_ret
; ---------------------------------------------------------------------------

@@horizontal_only?:
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@not_aligned
	cmp	di, [bp+@@bottom]
	jnz	short @@not_aligned
	call	_graph_r_hline stdcall, [bp+@@left], [bp+@@right], di, [bp+@@col]

@@add_sp_and_ret:
	add	sp, 8
	jmp	@@ret
; ---------------------------------------------------------------------------

@@not_aligned:
	mov	ax, [bp+@@left]
	cmp	ax, [bp+@@right]
	jle	short @@clip_left?
	mov	[bp+@@tmp], ax
	mov	ax, [bp+@@right]
	mov	[bp+@@left], ax
	mov	ax, [bp+@@tmp]
	mov	[bp+@@right], ax
	mov	[bp+@@tmp], di
	mov	di, [bp+@@bottom]
	mov	ax, [bp+@@tmp]
	mov	[bp+@@bottom], ax

@@clip_left?:
	cmp	[bp+@@left], 0
	jge	short @@clip_right?
	cmp	[bp+@@right], 0
	jl	@@ret
	mov	ax, [bp+@@bottom]
	sub	ax, di
	mov	bx, [bp+@@right]
	sub	bx, [bp+@@left]
	cwd
	idiv	bx
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	xor	ax, ax
	sub	ax, [bp+@@left]
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	fmulp	st(1), st
	call	ftol@
	add	di, ax
	mov	[bp+@@left], 0

@@clip_right?:
	cmp	[bp+@@right], (RES_X - 1)
	jle	short @@clip_top?
	cmp	[bp+@@left], (RES_X - 1)
	jg	@@ret
	mov	ax, [bp+@@bottom]
	sub	ax, di
	mov	bx, [bp+@@right]
	sub	bx, [bp+@@left]
	cwd
	idiv	bx
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	mov	ax, [bp+@@right]
	add	ax, -(RES_X - 1)
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	fmulp	st(1), st
	call	ftol@
	sub	[bp+@@bottom], ax
	mov	[bp+@@right], (RES_X - 1)

@@clip_top?:
	or	di, di
	jge	short @@clip_bottom?
	cmp	[bp+@@bottom], 0
	jl	@@ret
	mov	ax, [bp+@@right]
	sub	ax, [bp+@@left]
	mov	bx, [bp+@@bottom]
	sub	bx, di
	cwd
	idiv	bx
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	xor	ax, ax
	sub	ax, di
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	fmulp	st(1), st
	call	ftol@
	add	[bp+@@left], ax
	xor	di, di

@@clip_bottom?:
	cmp	[bp+@@bottom], (RES_Y - 1)
	jle	short @@clip_bottom_at_top?
	cmp	di, (RES_Y - 1)
	jg	@@ret
	mov	ax, [bp+@@right]
	sub	ax, [bp+@@left]
	mov	bx, [bp+@@bottom]
	sub	bx, di
	cwd
	idiv	bx
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	mov	ax, [bp+@@bottom]
	add	ax, -(RES_Y - 1)
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	fmulp	st(1), st
	call	ftol@
	sub	[bp+@@right], ax
	mov	[bp+@@bottom], (RES_Y - 1)

@@clip_bottom_at_top?:
	cmp	[bp+@@bottom], 0
	jge	short @@clip_top_at_bottom?
	mov	ax, [bp+@@right]
	sub	ax, [bp+@@left]
	mov	bx, [bp+@@bottom]
	sub	bx, di
	cwd
	idiv	bx
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	xor	ax, ax
	sub	ax, [bp+@@bottom]
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	fmulp	st(1), st
	call	ftol@
	add	[bp+@@right], ax
	mov	[bp+@@bottom], 0

@@clip_top_at_bottom?:
	cmp	di, (RES_Y - 1)
	jle	short @@setup_coords
	mov	ax, [bp+@@right]
	sub	ax, [bp+@@left]
	mov	bx, [bp+@@bottom]
	sub	bx, di
	cwd
	idiv	bx
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	lea	ax, [di-(RES_Y - 1)]
	mov	[bp+@@x87_tmp], ax
	fild	[bp+@@x87_tmp]
	fmulp	st(1), st
	call	ftol@
	sub	[bp+@@left], ax
	mov	di, (RES_Y - 1)

@@setup_coords:
	mov	ax, [bp+@@right]
	mov	_graph_r_last_line_end.x, ax
	mov	ax, [bp+@@bottom]
	mov	_graph_r_last_line_end.y, ax
	mov	ax, [bp+@@left]
	mov	[bp+@@x_cur], ax
	mov	[bp+@@y_cur], di
	cmp	di, [bp+@@bottom]
	jge	short @@y_up
	mov	ax, 1
	jmp	short @@y_direction_set
; ---------------------------------------------------------------------------

@@y_up:
	mov	ax, -1

@@y_direction_set:
	mov	[bp+@@y_direction], ax
	mov	ax, [bp+@@right]
	sub	ax, [bp+@@left]
	mov	[bp+@@w], ax
	mov	ax, [bp+@@bottom]
	sub	ax, di
	imul	[bp+@@y_direction]
	mov	[bp+@@h], ax
	mov	[bp+@@pixels], 0
	mov	ax, [bp+@@x_cur]
	sar	ax, 3
	mov	[bp+@@x_vram], ax
	mov	ax, [bp+@@y_cur]
	mov	[bp+@@y_vram], ax
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@select_loop
	push	[bp+@@col]
	call	_grcg_setcolor_rmw
	pop	cx

@@select_loop:
	mov	ax, [bp+@@w]
	cmp	ax, [bp+@@h]
	jle	@@yloop_setup
	sar	ax, 1
	mov	[bp+@@error], ax
	mov	[bp+@@i], 0
	jmp	@@xloop_more?
; ---------------------------------------------------------------------------

@@xloop:
	mov	ax, [bp+@@x_cur]
	sar	ax, 3
	cmp	ax, [bp+@@x_vram]
	jnz	short @@xloop_put
	mov	ax, [bp+@@y_vram]
	cmp	ax, [bp+@@y_cur]
	jz	@@xloop_advance_cur

@@xloop_put:
	mov	ax, [bp+@@y_vram]
	imul	ax, ROW_SIZE
	add	ax, [bp+@@x_vram]
	mov	si, ax
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@xloop_restore
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	ax, [bp+@@pixels]
	mov	es:[bx], ax
	mov	[bp+@@pixels], 0
	jmp	@@xloop_advance_vram
; ---------------------------------------------------------------------------

@@xloop_restore:
	dec	si
	push	1
	call	_graph_accesspage_func
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_B], eax
	les	bx, _VRAM_PLANE_R
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_R], eax
	les	bx, _VRAM_PLANE_G
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_G], eax
	les	bx, _VRAM_PLANE_E
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_E], eax
	push	0
	call	_graph_accesspage_func
	add	sp, 4
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, [bp+@@page1_B]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_R
	add	bx, si
	mov	eax, [bp+@@page1_R]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_G
	add	bx, si
	mov	eax, [bp+@@page1_G]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_E
	add	bx, si
	mov	eax, [bp+@@page1_E]
	mov	es:[bx], eax

@@xloop_advance_vram:
	mov	ax, [bp+@@y_cur]
	mov	[bp+@@y_vram], ax
	mov	ax, [bp+@@x_cur]
	sar	ax, 3
	mov	[bp+@@x_vram], ax

@@xloop_advance_cur:
	mov	cl, byte ptr [bp+@@x_cur]
	and	cl, 7
	mov	ax, _graph_r_pattern
	shr	ax, cl
	or	[bp+@@pixels], ax
	mov	al, byte ptr [bp+@@x_cur]
	and	al, 7
	mov	cl, 16
	sub	cl, al
	mov	ax, _graph_r_pattern
	shl	ax, cl
	or	[bp+@@pixels], ax
	mov	ax, [bp+@@h]
	sub	[bp+@@error], ax
	inc	[bp+@@x_cur]
	cmp	[bp+@@error], 0
	jge	short @@xloop_next
	mov	ax, [bp+@@w]
	add	[bp+@@error], ax
	mov	ax, [bp+@@y_direction]
	add	[bp+@@y_cur], ax

@@xloop_next:
	inc	[bp+@@i]

@@xloop_more?:
	mov	ax, [bp+@@i]
	cmp	ax, [bp+@@w]
	jle	@@xloop
	cmp	_graph_r_restore_from_1, 0
	jz	@@grcg_off?
	jmp	@@restore_last
; ---------------------------------------------------------------------------

@@yloop_setup:
	mov	ax, [bp+@@h]
	sar	ax, 1
	mov	[bp+@@error], ax
	mov	[bp+@@i], 0
	jmp	@@yloop_more?
; ---------------------------------------------------------------------------

@@yloop:
	mov	ax, [bp+@@x_cur]
	sar	ax, 3
	cmp	ax, [bp+@@x_vram]
	jnz	short @@yloop_put
	mov	ax, [bp+@@y_vram]
	cmp	ax, [bp+@@y_cur]
	jz	@@yloop_advance_cur

@@yloop_put:
	mov	ax, [bp+@@y_vram]
	imul	ax, ROW_SIZE
	add	ax, [bp+@@x_vram]
	mov	si, ax
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@yloop_restore
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	ax, [bp+@@pixels]
	mov	es:[bx], ax
	mov	[bp+@@pixels], 0
	jmp	@@yloop_advance_vram
; ---------------------------------------------------------------------------

@@yloop_restore:
	dec	si
	push	1
	call	_graph_accesspage_func
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_B], eax
	les	bx, _VRAM_PLANE_R
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_R], eax
	les	bx, _VRAM_PLANE_G
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_G], eax
	les	bx, _VRAM_PLANE_E
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_E], eax
	push	0
	call	_graph_accesspage_func
	add	sp, 4
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, [bp+@@page1_B]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_R
	add	bx, si
	mov	eax, [bp+@@page1_R]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_G
	add	bx, si
	mov	eax, [bp+@@page1_G]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_E
	add	bx, si
	mov	eax, [bp+@@page1_E]
	mov	es:[bx], eax

@@yloop_advance_vram:
	mov	ax, [bp+@@y_cur]
	mov	[bp+@@y_vram], ax
	mov	ax, [bp+@@x_cur]
	sar	ax, 3
	mov	[bp+@@x_vram], ax

@@yloop_advance_cur:
	mov	cl, byte ptr [bp+@@x_cur]
	and	cl, 7
	mov	ax, _graph_r_pattern
	shr	ax, cl
	or	[bp+@@pixels], ax
	mov	al, byte ptr [bp+@@x_cur]
	and	al, 7
	mov	cl, 16
	sub	cl, al
	mov	ax, _graph_r_pattern
	shl	ax, cl
	or	[bp+@@pixels], ax
	mov	ax, [bp+@@w]
	sub	[bp+@@error], ax
	mov	ax, [bp+@@y_direction]
	add	[bp+@@y_cur], ax
	cmp	[bp+@@error], 0
	jge	short @@yloop_next
	mov	ax, [bp+@@h]
	add	[bp+@@error], ax
	inc	[bp+@@x_cur]

@@yloop_next:
	inc	[bp+@@i]

@@yloop_more?:
	mov	ax, [bp+@@i]
	cmp	ax, [bp+@@h]
	jle	@@yloop
	cmp	_graph_r_restore_from_1, 0
	jz	@@grcg_off?

@@restore_last:
	mov	ax, [bp+@@x_cur]
	sar	ax, 3
	mov	dx, [bp+@@y_cur]
	shl	dx, 6
	add	ax, dx
	mov	dx, [bp+@@y_cur]
	shl	dx, 4
	add	ax, dx
	dec	ax
	mov	si, ax
	push	1
	call	_graph_accesspage_func
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_B], eax
	les	bx, _VRAM_PLANE_R
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_R], eax
	les	bx, _VRAM_PLANE_G
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_G], eax
	les	bx, _VRAM_PLANE_E
	add	bx, si
	mov	eax, es:[bx]
	mov	[bp+@@page1_E], eax
	push	0
	call	_graph_accesspage_func
	add	sp, 4
	les	bx, _VRAM_PLANE_B
	add	bx, si
	mov	eax, [bp+@@page1_B]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_R
	add	bx, si
	mov	eax, [bp+@@page1_R]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_G
	add	bx, si
	mov	eax, [bp+@@page1_G]
	mov	es:[bx], eax
	les	bx, _VRAM_PLANE_E
	add	bx, si
	mov	eax, [bp+@@page1_E]
	mov	es:[bx], eax

@@grcg_off?:
	cmp	_graph_r_restore_from_1, 0
	jnz	short @@ret
	call	_grcg_off_func

@@ret:
	pop	di
	pop	si
	leave
	retf
_graph_r_line	endp
