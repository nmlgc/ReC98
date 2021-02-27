	@piano_fm_part_put_raw	procdesc near
	@piano_current_note_from	procdesc near
	_piano_part_keys_put_raw	procdesc near
	@piano_pressed_key_put	procdesc near
	@piano_label_put_raw	procdesc near
	_grcg_setcolor_direct_seg1_raw	procdesc near

	PIANO_LABEL_FONT_W = 8
	PIANO_LABEL_FONT_H = 8

piano_label_puts macro row:req, chr1:req, chr2:req, chr3:req
	piano_label_putc	0, row, chr1
	piano_label_putc	1, row, chr2
	piano_label_putc	2, row, chr3
endm

piano_label_putc macro col:req, row:req, chr:req
	mov 	al, chr
	mov 	di, ((PIANO_LABEL_TOP + (row * PIANO_H_PADDED)) * ROW_SIZE) + ((PIANO_LABEL_LEFT + (col * PIANO_LABEL_FONT_W)) / 8)
	call	@piano_label_put_raw
endm


public _piano_setup
_piano_setup proc far
	push	si
	push	di
	GRCG_SETMODE_VIA_MOV al, GC_RMW
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	di, (PIANO_TOP + (0 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
	mov	di, (PIANO_TOP + (1 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
	mov	di, (PIANO_TOP + (2 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
	mov	di, (PIANO_TOP + (3 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
	mov	di, (PIANO_TOP + (4 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
	mov	di, (PIANO_TOP + (5 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
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
_piano_setup endp


public _piano_render
_piano_render proc far
	push	si
	push	di
	push	ds
	push	ds
	pop	fs
	GRCG_SETMODE_VIA_MOV al, GC_RMW
	mov	ax, GRAM_400
	mov	es, ax
	mov	di, (PIANO_TOP + (5 * PIANO_H_PADDED)) * ROW_SIZE
	call	_piano_part_keys_put_raw
	lds	bx, _pmd_workadr	; FMPart[0]
	mov	di, (PIANO_TOP + (0 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[0]
	call	@piano_fm_part_put_raw
	add	bx, 2	; FMPart[1]
	mov	di, (PIANO_TOP + (1 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[1]
	call	@piano_fm_part_put_raw
	add	bx, 2	; FMPart[2]
	mov	di, (PIANO_TOP + (2 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[2]
	call	@piano_fm_part_put_raw
	add	bx, 2	; FMPart[3]
	mov	di, (PIANO_TOP + (3 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[3]
	call	@piano_fm_part_put_raw
	add	bx, 2	; FMPart[4]
	mov	di, (PIANO_TOP + (4 * PIANO_H_PADDED)) * ROW_SIZE
	mov	si, offset piano_notes_t.fm[4]
	call	@piano_fm_part_put_raw
	mov	ah, GC_RI
	call	_grcg_setcolor_direct_seg1_raw
	mov	di, (PIANO_TOP + (5 * PIANO_H_PADDED)) * ROW_SIZE
	add	bx, 4	; SSGPart[0]
	call	@piano_current_note_from
	call	@piano_pressed_key_put
	add	bx, 2	; SSGPart[1]
	call	@piano_current_note_from
	call	@piano_pressed_key_put
	GRCG_OFF_VIA_XOR al
	pop	ds
	pop	di
	pop	si
	retf
_piano_render endp
