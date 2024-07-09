; First TH05 .PI assembly translation unit.

	.386
	.model use16 large SHARED
	locals

include pc98.inc
include libs/master.lib/master.inc

	extrn _PI_MASKS:word
	extrn _pi_mask_ptr:word
	extrn _pi_mask_y:word
	extrn _pi_put_masked_vram_offset:word

	.code SHARED
	@pi_mask_setup_egc_and_advance$qv procdesc near

public @PI_PUT_MASKED_8_ROWLOOP$QIIIUI
@pi_put_masked_8_rowloop$qiiiui proc near
; Can't use ARG, because the function doesn't `PUSH BP`!
@@stride_packed	= word ptr [bp+2]
@@w            	= word ptr [bp+4]
@@top          	= word ptr [bp+6]
@@left         	= word ptr [bp+8]
@@mask_id equ ax
@@h equ di

; Each original row is first blitted to this fixed row in VRAM, before being
; blitted to its actual destination with the EGC active.
TEMP_ROW = RES_Y

	shl	@@mask_id, 3	; *= PI_MASK_H * word
	add	@@mask_id, offset _PI_MASKS
	mov	_pi_mask_ptr, @@mask_id
	mov	bp, sp
	mov	dx, @@left
	shr	dx, 3
	mov	ax, @@top
	shl	ax, 6
	add	dx, ax
	shr	ax, 2
	add	dx, ax
	mov	_pi_put_masked_vram_offset, dx
	mov	_pi_mask_y, 0

@@put_row:
	push	es
	call	graph_pack_put_8_noclip pascal, 0, TEMP_ROW, es, si, @@w
	push	ds
	push	@@h
	push	si
	mov	di, _pi_put_masked_vram_offset
	add	_pi_put_masked_vram_offset, ROW_SIZE
	cmp	_pi_put_masked_vram_offset, PLANE_SIZE
	jb	short @@next_row
	sub	_pi_put_masked_vram_offset, PLANE_SIZE

@@next_row:
	call	@pi_mask_setup_egc_and_advance$qv
	mov	ax, SEG_PLANE_B
	mov	es, ax
	assume es:nothing
	mov	ds, ax
	assume ds:nothing
	mov	si, (ROW_SIZE * TEMP_ROW)
	mov	cx, @@w
	shr	cx, 4
	rep movsw
	call	egc_off
	pop	si
	pop	@@h
	pop	ds
	pop	es
	add	si, @@stride_packed

	; .PI pointer normalization, see pi_buffer_p_normalize()
	mov	ax, si
	shr	ax, 4
	mov	dx, es
	add	dx, ax
	mov	es, dx
	and	si, 0Fh

	dec	@@h
	jnz	short @@put_row
	retn	8
@pi_put_masked_8_rowloop$qiiiui endp

	end
