public CDG_PUT_8
cdg_put_8 proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@slot:word, @@top:word, @@left:word
	@@vram_dword_w	equ <bp>
	@@vram_offset_at_bottom_left	equ <bx>
	@@stride	equ <dx>

	push	bp
	mov	bp, sp
	push	si
	push	di
	push	ds
	cli

	; grcg_setcolor(GC_RMW, 0);
	GRCG_SETMODE_VIA_MOV	al, GC_RMW
	mov	dx, 7Eh
	xor	al, al
	out	dx, al
	out	dx, al
	out	dx, al
	out	dx, al

	sti
	mov	si, @@slot
	shl	si, 4	; *= size cdg_t
	add	si, offset _cdg_slots
if GAME eq 4
	mov	ax, [si+cdg_t.seg_colors]
	mov	word ptr cs:@@seg_colors, ax
	jmp	short $+2
	mov	ax, @@top
	mov	bx, ax
	shl	ax, 2
	add	ax, bx
else
	mov	ax, @@top
	shl	ax, 2
	add	ax, @@top
endif
	add	ax, SEG_PLANE_B
	mov	es, ax
	push	0	; (sentinel)
	add	ax, (SEG_PLANE_E - SEG_PLANE_B)	; AX == SEG_PLANE_E
	push	ax
	sub	ax, SEG_PLANE_DIST_E	; AX == SEG_PLANE_G
	push	ax
	sub	ax, SEG_PLANE_DIST_BRG	; AX == SEG_PLANE_R
	push	ax
	mov	ax, @@left
	shr	ax, 3
	add	ax, [si+cdg_t.offset_at_bottom_left]
	mov	di, ax
	mov	@@vram_offset_at_bottom_left, ax
	mov	ax, [si+cdg_t.vram_dword_w]
	mov	@@vram_dword_w, ax
	shl	ax, 2
	add	ax, ROW_SIZE
	mov	@@stride, ax
if GAME eq 4
	mov	ax, [si+cdg_t.seg_alpha]
	mov	ds, ax
else
	mov	ax, [si+cdg_t.seg_colors]
	mov	cx, [si+cdg_t.seg_alpha]
	mov	ds, cx
endif
	xor	si, si
	cld
	even

@@alpha:
	mov	cx, @@vram_dword_w
	rep movsd
	sub	di, @@stride
	jns	short @@alpha
if GAME eq 5
	mov	ds, ax
endif
	GRCG_OFF_VIA_XOR	al

	xor	si, si
if GAME eq 5
	even
endif

if GAME eq 4
	@@seg_colors equ $+1
	mov	ax, 1234h
	mov	ds, ax
endif

@@next_plane:
	mov	di, @@vram_offset_at_bottom_left

@@next_row:
	mov	cx, @@vram_dword_w

@@blit_dword:
	lodsd
	or	es:[di], eax
	add	di, dword
	loop	@@blit_dword
	sub	di, @@stride
	jns	short @@next_row
	pop	ax
	mov	es, ax
	or	ax, ax
	jnz	short @@next_plane
	pop	ds
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_put_8 endp
	even
