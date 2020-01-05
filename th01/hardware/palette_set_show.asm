public _z_palette_set_show
_z_palette_set_show	proc far

@@col	= word ptr  6
@@r  	= word ptr  8
@@g  	= word ptr  0Ah
@@b  	= word ptr  0Ch

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@col]
	cmp	[bp+@@r], 0Fh
	jge	short @@r_above
	mov	ax, [bp+@@r]
	jmp	short @@r_below?
; ---------------------------------------------------------------------------

@@r_above:
	mov	ax, 0Fh

@@r_below?:
	or	ax, ax
	jle	short @@r_below
	cmp	[bp+@@r], 0Fh
	jge	short @@r_REALLY_above
	mov	ax, [bp+@@r]
	jmp	short @@r_in_range
; ---------------------------------------------------------------------------

@@r_REALLY_above:
	mov	ax, 0Fh

@@r_in_range:
	jmp	short @@r_set
; ---------------------------------------------------------------------------

@@r_below:
	xor	ax, ax

@@r_set:
	mov	[bp+@@r], ax
	cmp	[bp+@@g], 0Fh
	jge	short @@g_above_4bit
	mov	ax, [bp+@@g]
	jmp	short @@g_below?
; ---------------------------------------------------------------------------

@@g_above_4bit:
	mov	ax, 0Fh

@@g_below?:
	or	ax, ax
	jle	short @@g_below
	cmp	[bp+@@g], 0Fh
	jge	short @@g_REALLY_above
	mov	ax, [bp+@@g]
	jmp	short @@g_in_range
; ---------------------------------------------------------------------------

@@g_REALLY_above:
	mov	ax, 0Fh

@@g_in_range:
	jmp	short @@g_set
; ---------------------------------------------------------------------------

@@g_below:
	xor	ax, ax

@@g_set:
	mov	[bp+@@g], ax
	cmp	[bp+@@b], 0Fh
	jge	short @@b_above
	mov	ax, [bp+@@b]
	jmp	short @@b_below?
; ---------------------------------------------------------------------------

@@b_above:
	mov	ax, 0Fh

@@b_below?:
	or	ax, ax
	jle	short @@b_below
	cmp	[bp+@@b], 0Fh
	jge	short @@b_REALLY_above
	mov	ax, [bp+@@b]
	jmp	short @@b_in_range
; ---------------------------------------------------------------------------

@@b_REALLY_above:
	mov	ax, 0Fh

@@b_in_range:
	jmp	short @@b_set
; ---------------------------------------------------------------------------

@@b_below:
	xor	ax, ax

@@b_set:
	mov	[bp+@@b], ax
	mov	bx, si
	imul	bx, 3
	mov	al, byte ptr [bp+@@r]
	mov	_z_Palettes[bx].r, al
	mov	bx, si
	imul	bx, 3
	mov	al, byte ptr [bp+@@g]
	mov	_z_Palettes[bx].g, al
	mov	bx, si
	imul	bx, 3
	mov	al, byte ptr [bp+@@b]
	mov	_z_Palettes[bx].b, al
	call	_z_palette_show_single c, si, [bp+@@r], [bp+@@g], [bp+@@b]
	pop	si
	pop	bp
	retf
_z_palette_set_show	endp
