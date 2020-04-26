public _piano_setup
_piano_setup	proc far
	push	si
	push	di
	GRCG_SETMODE_VIA_MOV al, GC_RMW
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	di, (PIANO_Y + (0 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	mov	di, (PIANO_Y + (1 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	mov	di, (PIANO_Y + (2 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	mov	di, (PIANO_Y + (3 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	mov	di, (PIANO_Y + (4 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	mov	di, (PIANO_Y + (5 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	mov	ah, GC_RI
	call	_grcg_setcolor_direct_seg1_raw
	piano_label_puts	0, pl_F, pl_M, pl_1
	piano_label_puts	1, pl_F, pl_M, pl_2
	piano_label_puts	2, pl_F, pl_M, pl_3
	piano_label_puts	3, pl_F, pl_M, pl_4
	piano_label_puts	4, pl_F, pl_M, pl_5
	piano_label_puts	5, pl_S, pl_S, pl_G
	GRCG_OFF_VIA_XOR al
	push	ds
	mov	ah, PMD_GET_WORKAREA_ADDRESS
	int	PMD
	mov	ax, ds
	pop	ds
	mov	word ptr _pmd_workadr, dx
	mov	word ptr _pmd_workadr+2, ax
	pop	di
	pop	si
	retf
_piano_setup	endp


public _piano_render
_piano_render	proc far
	push	si
	push	di
	push	ds
	push	ds
	pop	fs
	GRCG_SETMODE_VIA_MOV al, GC_RMW
	mov	ax, GRAM_400
	mov	es, ax
	mov	di, (PIANO_Y + (5 * PIANO_H_PADDED)) * ROW_SIZE
	call	piano_draw_part_keys
	lds	bx, _pmd_workadr	; FMPart[0]
	mov	di, (PIANO_Y + (0 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[0]
	call	piano_part_render
	add	bx, 2	; FMPart[1]
	mov	di, (PIANO_Y + (1 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[1]
	call	piano_part_render
	add	bx, 2	; FMPart[2]
	mov	di, (PIANO_Y + (2 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[2]
	call	piano_part_render
	add	bx, 2	; FMPart[3]
	mov	di, (PIANO_Y + (3 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[3]
	call	piano_part_render
	add	bx, 2	; FMPart[4]
	mov	di, (PIANO_Y + (4 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[4]
	call	piano_part_render
	mov	ah, GC_RI
	call	_grcg_setcolor_direct_seg1_raw
	mov	di, (PIANO_Y + (5 * PIANO_H_PADDED)) * ROW_SIZE
	add	bx, 4	; SSGPart[0]
	call	piano_get_note
	call	piano_draw_pressed_key
	add	bx, 2	; SSGPart[1]
	call	piano_get_note
	call	piano_draw_pressed_key
	GRCG_OFF_VIA_XOR al
	pop	ds
	pop	di
	pop	si
	retf
_piano_render	endp


; void __usercall near piano_part_render(
; 	void far *vram_at_x0_and_top_of_part<es:di>,
; 	int fm_part_num<si>,
; 	QQ **pmd_part<ds:bx>,
; 	void __seg own_ds<fs>
; );
piano_part_render	proc near
	call	piano_get_note
	push	ds
	push	fs
	pop	ds
	cmp	al, _piano_notes_cur.fm[si]
	jnz	short @@note_changed
	cmp	al, _piano_notes_prev.fm[si]
	jz	short @@ret

@@note_changed:
	mov	ah, _piano_notes_cur.fm[si]
	mov	_piano_notes_prev.fm[si], ah
	mov	_piano_notes_cur.fm[si], al
	call	piano_draw_part_keys
	mov	ah, GC_RI
	call	_grcg_setcolor_direct_seg1_raw
	mov	al, _piano_notes_cur.fm[si]
	call	piano_draw_pressed_key

@@ret:
	pop	ds
	retn
piano_part_render	endp


; char __usercall near piano_get_note(QQ **pmd_part<ds:bx>);
piano_get_note	proc near
	push	bx
	mov	bx, [bx]
	mov	ax, word ptr [bx+qq.leng]
	cmp	ah, 4
	jbe	short @@above_gatetime?
	mov	ah, 4

@@above_gatetime?:
	cmp	al, ah
	jbe	short @@resting
	cmp	al, 1
	jbe	short @@resting
	mov	al, [bx+qq.onkai]
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@resting:
	mov	al, ONKAI_REST

@@ret:
	pop	bx
	retn
piano_get_note	endp


; void __usercall near piano_draw_part_keys(
; 	void far *vram_at_x0_and_top_of_part<es:di>
; )
piano_draw_part_keys	proc near
	push	di
	push	si
	mov	ah, GC_GI
	call	_grcg_setcolor_direct_seg1_raw
	add	di, PIANO_VRAM_X
	mov	ax, PIANO_KEYS_WHITE
	mov	dl, PIANO_H

@@white_key_loop:
	mov	cx, PIANO_VRAM_W / 2
	rep stosw
	add	di, ROW_SIZE - PIANO_VRAM_W
	dec	dl
	jnz	short @@white_key_loop
	mov	ah, GC_RGI
	call	_grcg_setcolor_direct_seg1_raw
	mov	si, offset _PIANO_KEYS_BLACK
	sub	di, ROW_SIZE * PIANO_H
	mov	dl, PIANO_BLACK_H

@@black_key_loop:
	mov	cx, PIANO_VRAM_W / 2
	rep movsw
	sub	si, PIANO_VRAM_W
	add	di, ROW_SIZE - PIANO_VRAM_W
	dec	dl
	jnz	short @@black_key_loop
	pop	si
	pop	di
	retn
piano_draw_part_keys	endp


; void __usercall near piano_draw_pressed_key(
; 	void far *vram_at_x0_and_top_of_part<es:di>, char onkai<al>
; )
piano_draw_pressed_key	proc near
	cmp	al, ONKAI_REST
	jnz	short @@note_is_active
	retn
; ---------------------------------------------------------------------------

@@note_is_active:
	push	bx
	push	di
	mov	ah, al
	and	ah, ONKAI_NOTE_MASK
	xor	bh, bh
	mov	bl, ah
	shr	al, 4
	mov	dl, PIANO_OCTAVE_W
	mul	dl
	mov	dl, cs:PIANO_KEY_PRESSED_TOP[bx]
	add	bx, bx
	add	ax, cs:PIANO_NOTE_X[bx]
	mov	cx, ax
	shr	ax, 3
	add	di, ax
	and	cl, 7
	jmp	cs:BLACK_OR_WHITE[bx]

white_key:
	shr	dl, cl
	mov	al, cl
	mov	cx, PIANO_BLACK_H

@@white_key_top_loop:
	mov	es:[di], dl
	add	di, ROW_SIZE
	loop	@@white_key_top_loop
	mov	cl, al
	mov	al, (111b shl 5)	; bottom part of any pressed key
	shr	al, cl
	mov	cx, PIANO_H - PIANO_BLACK_H

@@white_key_bottom_loop:
	mov	es:[di], al
	add	di, ROW_SIZE
	loop	@@white_key_bottom_loop
	jmp	short @@ret
; ---------------------------------------------------------------------------

black_key:
	xor	dh, dh
	ror	dx, cl
	mov	cx, PIANO_BLACK_PRESSED_H

@@black_key_loop:
	mov	es:[di], dx
	add	di, ROW_SIZE
	loop	@@black_key_loop

@@ret:
	pop	di
	pop	bx
	retn
piano_draw_pressed_key	endp

; ---------------------------------------------------------------------------
BLACK_OR_WHITE	label word
	dw offset white_key	; C
	dw offset black_key	; C#
	dw offset white_key	; D
	dw offset black_key	; D#
	dw offset white_key	; E
	dw offset white_key	; F
	dw offset black_key	; F#
	dw offset white_key	; G
	dw offset black_key	; G#
	dw offset white_key	; A
	dw offset black_key	; A#
	dw offset white_key	; B

PIANO_NOTE_X	label word
	dw PIANO_X + 0	; C
	dw PIANO_X + 2	; C#
	dw PIANO_X + 4	; D
	dw PIANO_X + 6	; D#
	dw PIANO_X + 8	; E
	dw PIANO_X + 12	; F
	dw PIANO_X + 14	; F#
	dw PIANO_X + 16	; G
	dw PIANO_X + 18	; G#
	dw PIANO_X + 20	; A
	dw PIANO_X + 22	; A#
	dw PIANO_X + 24	; B

; 1bpp sprite data for the top part of a pressed key, in the black key row.
PIANO_KEY_PRESSED_TOP	label byte
	db (110b shl 5)	; C
	db (110b shl 5)	; C#
	db (010b shl 5)	; D
	db (110b shl 5)	; D#
	db (011b shl 5)	; E
	db (110b shl 5)	; F
	db (110b shl 5)	; F#
	db (010b shl 5)	; G
	db (110b shl 5)	; G#
	db (010b shl 5)	; A
	db (110b shl 5)	; A#
	db (011b shl 5)	; B


public PIANO_LABEL_PUT_RAW
piano_label_put_raw	proc near
	xor	ah, ah
	shl	al, 3
	add	ax, offset _PIANO_LABEL_FONT
	mov	si, ax
	mov	cx, PIANO_LABEL_FONT_W

@@row_loop:
	movsb
	add	di, ROW_SIZE - 1
	loop	@@row_loop
	retn
piano_label_put_raw	endp
