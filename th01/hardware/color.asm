public _z_palette_show_single
_z_palette_show_single	proc far

@@col	= byte ptr  6
@@r  	= byte ptr  8
@@g  	= byte ptr  0Ah
@@b  	= byte ptr  0Ch

	push	bp
	mov	bp, sp
	mov	dx, 0A8h
	mov	al, [bp+@@col]
	out	dx, al
	mov	dx, 0AAh
	mov	al, [bp+@@g]
	out	dx, al
	mov	dx, 0ACh
	mov	al, [bp+@@r]
	out	dx, al
	mov	dx, 0AEh
	mov	al, [bp+@@b]
	out	dx, al
	pop	bp
	retf
_z_palette_show_single	endp


public _grcg_setcolor_rmw
_grcg_setcolor_rmw	proc far

@@color	= word ptr  6

	push	bp
	mov	bp, sp
	mov	bx, [bp+@@color]
	GRCG_SETMODE_CLOBBERING dx, GC_RMW
	test	bl, 1
	jz	short @@bit0_0
	mov	al, 0FFh
	jmp	short @@bit0_set
; ---------------------------------------------------------------------------

@@bit0_0:
	mov	al, 0

@@bit0_set:
	mov	dx, 7Eh
	out	dx, al
	test	bl, 2
	jz	short @@bit1_0
	mov	al, 0FFh
	jmp	short @@bit1_set
; ---------------------------------------------------------------------------

@@bit1_0:
	mov	al, 0

@@bit1_set:
	mov	dx, 7Eh
	out	dx, al
	test	bl, 4
	jz	short @@bit2_0
	mov	al, 0FFh
	jmp	short @@bit2_set
; ---------------------------------------------------------------------------

@@bit2_0:
	mov	al, 0

@@bit2_set:
	mov	dx, 7Eh
	out	dx, al
	test	bl, 8
	jz	short @@bit3_0
	mov	al, 0FFh
	jmp	short @@bit3_set
; ---------------------------------------------------------------------------

@@bit3_0:
	mov	al, 0

@@bit3_set:
	mov	dx, 7Eh
	out	dx, al
	pop	bp
	retf
_grcg_setcolor_rmw	endp


public _grcg_setcolor_tdw
_grcg_setcolor_tdw	proc far

@@color	= word ptr  6

	push	bp
	mov	bp, sp
	mov	bx, [bp+@@color]
	GRCG_SETMODE_CLOBBERING dx, GC_TDW
	test	bl, 1
	jz	short @@bit0_0
	mov	al, 0FFh
	jmp	short @@bit0_set
; ---------------------------------------------------------------------------

@@bit0_0:
	mov	al, 0

@@bit0_set:
	mov	dx, 7Eh
	out	dx, al
	test	bl, 2
	jz	short @@bit1_0
	mov	al, 0FFh
	jmp	short @@bit1_set
; ---------------------------------------------------------------------------

@@bit1_0:
	mov	al, 0

@@bit1_set:
	mov	dx, 7Eh
	out	dx, al
	test	bl, 4
	jz	short @@bit2_0
	mov	al, 0FFh
	jmp	short @@bit2_set
; ---------------------------------------------------------------------------

@@bit2_0:
	mov	al, 0

@@bit2_set:
	mov	dx, 7Eh
	out	dx, al
	test	bl, 8
	jz	short @@bit3_0
	mov	al, 0FFh
	jmp	short @@bit3_set
; ---------------------------------------------------------------------------

@@bit3_0:
	mov	al, 0

@@bit3_set:
	mov	dx, 7Eh
	out	dx, al
	pop	bp
	retf
_grcg_setcolor_tdw	endp


public _grcg_off_func
_grcg_off_func	proc far
	push	bp
	mov	bp, sp
	GRCG_OFF_CLOBBERING dx
	pop	bp
	retf
_grcg_off_func	endp
