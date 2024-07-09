	.386
	.model use16 large SHARED
	locals

include pc98.inc
include libs/master.lib/macros.inc
include libs/kaja/kaja.inc
include th04/hardware/grcg.inc
include th05/op/piano.inc

PIANO_LEFT = 384
PIANO_H = 15
PIANO_KEY_W = 4
PIANO_BLACK_H = 9
PIANO_BLACK_PRESSED_H = 8

PIANO_OCTAVES = 8
PIANO_OCTAVE_W = (7 * PIANO_KEY_W)

PIANO_VRAM_LEFT = (PIANO_LEFT / 8)
PIANO_VRAM_W = ((PIANO_OCTAVES * PIANO_OCTAVE_W) / 8)

	extern _sPIANO_LABEL_FONT:byte
	extern _PIANO_KEYS_BLACK:byte:PIANO_VRAM_W
	extern _piano_notes_cur:piano_notes_t
	extern _piano_notes_prev:piano_notes_t

; 1bpp sprite data
; ----------------

PIANO_KEYS_WHITE = 1110111011101110b

PIANO_LABEL_FONT_W = 8
PIANO_LABEL_FONT_H = 8
; ----------------

	.code SHARED

; void __usercall near piano_fm_part_put_raw(
; 	void far *vram_at_x0_and_top_of_part<es:di>,
; 	int fm_part_id<si>,
; 	QQ near *near *qq<bx>,
; 	void __seg *original_data_ds<fs>
; );
public @piano_fm_part_put_raw
@piano_fm_part_put_raw proc near
	call	@piano_current_note_from
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
	call	_piano_part_keys_put_raw
	mov	ah, GC_RI
	call	@grcg_setcolor_direct_raw$qv
	mov	al, _piano_notes_cur.fm[si]
	call	@piano_pressed_key_put

@@ret:
	pop	ds
	retn
@piano_fm_part_put_raw endp


; char __usercall near piano_current_note_from(QQ near *near *part<bx>);
public @piano_current_note_from
@piano_current_note_from proc near
	push	bx
	mov	bx, [bx]
	mov	ax, word ptr [bx+qq.leng] ; [leng] in AL, [qdat] in AH
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
@piano_current_note_from endp


; void __usercall near piano_part_keys_put_raw(
; 	void far *vram_at_x0_and_top_of_part<es:di>
; )
public _piano_part_keys_put_raw
_piano_part_keys_put_raw proc near
	push	di
	push	si
	mov	ah, GC_GI
	call	@grcg_setcolor_direct_raw$qv
	add	di, PIANO_VRAM_LEFT
	mov	ax, PIANO_KEYS_WHITE
	mov	dl, PIANO_H

@@white_key_loop:
	mov	cx, PIANO_VRAM_W / 2
	rep stosw
	add	di, ROW_SIZE - PIANO_VRAM_W
	dec	dl
	jnz	short @@white_key_loop
	mov	ah, GC_RGI
	call	@grcg_setcolor_direct_raw$qv
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
_piano_part_keys_put_raw endp


; void __fastcall near @piano_pressed_key_put(
; 	void far *vram_at_x0_and_top_of_part<es:di>, char onkai
; )
public @piano_pressed_key_put
@piano_pressed_key_put proc near
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
	add	ax, cs:PIANO_NOTE_LEFT[bx]
	mov	cx, ax
	shr	ax, 3
	add	di, ax
	and	cl, 7
	jmp	cs:BLACK_OR_WHITE[bx]

@@white_key:
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

@@black_key:
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

; ---------------------------------------------------------------------------
BLACK_OR_WHITE label word
	dw offset @@white_key	; C
	dw offset @@black_key	; C#
	dw offset @@white_key	; D
	dw offset @@black_key	; D#
	dw offset @@white_key	; E
	dw offset @@white_key	; F
	dw offset @@black_key	; F#
	dw offset @@white_key	; G
	dw offset @@black_key	; G#
	dw offset @@white_key	; A
	dw offset @@black_key	; A#
	dw offset @@white_key	; B

PIANO_NOTE_LEFT label word
	dw PIANO_LEFT + 0	; C
	dw PIANO_LEFT + 2	; C#
	dw PIANO_LEFT + 4	; D
	dw PIANO_LEFT + 6	; D#
	dw PIANO_LEFT + 8	; E
	dw PIANO_LEFT + 12	; F
	dw PIANO_LEFT + 14	; F#
	dw PIANO_LEFT + 16	; G
	dw PIANO_LEFT + 18	; G#
	dw PIANO_LEFT + 20	; A
	dw PIANO_LEFT + 22	; A#
	dw PIANO_LEFT + 24	; B
@piano_pressed_key_put endp

; 1bpp sprite data for the top part of a pressed key, in the black key row.
PIANO_KEY_PRESSED_TOP label byte
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


; void __fastcall near @piano_label_put_raw(
; 	void far *vram_offset<es:di>, piano_label_t label_char
; )
public @piano_label_put_raw
@piano_label_put_raw proc near
	xor	ah, ah
	shl	al, 3 ; *= PIANO_LABEL_FONT_H
	add	ax, offset _sPIANO_LABEL_FONT
	mov	si, ax
	mov	cx, PIANO_LABEL_FONT_W

@@row_loop:
	movsb
	add	di, (ROW_SIZE - (PIANO_LABEL_FONT_W / BYTE_DOTS))
	loop	@@row_loop
	retn
@piano_label_put_raw endp

GRCG_SETCOLOR_DIRECT_DEF

	end
