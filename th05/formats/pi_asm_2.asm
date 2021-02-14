; Second TH05 .PI assembly translation unit.

	.386
	.model large
	locals

include pc98.inc
include libs/master.lib/func.inc
include libs/master.lib/master.inc
include th03/arg_bx.inc

	extrn Palettes:palette_t
	extrn _pi_headers:PiHeader
	extrn _pi_buffers:far ptr

SHARED_	segment word public 'CODE' use16
	assume cs:SHARED_

public PI_PUT_8_ROWLOOP
pi_put_8_rowloop proc pascal near
; Can't use ARG, because the function doesn't `PUSH BP`!
@@stride_packed	= word ptr [bp+2]
@@w	= word ptr [bp+4]
@@top	= word ptr [bp+6]
@@left	= word ptr [bp+8]
@@h equ di

	mov	bp, sp

@@put_row:
	push	es
	call	graph_pack_put_8_noclip pascal, @@left, @@top, es, si, @@w
	pop	es
	inc	@@top
	cmp	@@top, RES_Y
	jb	short @@next_row
	sub	@@top, RES_Y

@@next_row:
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
pi_put_8_rowloop endp


public PI_PALETTE_APPLY
func pi_palette_apply
arg_bx	far, @slot:word

	push	si
	push	di
	mov	si, @slot
	imul	si, size PiHeader
	add	si, offset _pi_headers + PiHeader._palette
	mov	di, offset Palettes
	mov	ax, ds
	mov	es, ax
	mov	cx, (size palette_t / dword)
	rep movsd
	call	palette_show
	pop	di
	pop	si
	ret_bx
endfunc

public PI_FREE
func pi_free
arg_bx	far, @slot:word

	mov	bx, @slot
	mov	ax, bx
	shl	bx, 2
	add	bx, offset _pi_buffers
	cmp	dword ptr [bx], 0
	jz	short @@ret
	imul	ax, size PiHeader
	add	ax, offset _pi_headers
	push	ds
	push	ax
	push	word ptr [bx+2]
	push	word ptr [bx]
	mov	dword ptr [bx], 0
	call	graph_pi_free
@@ret:
	ret	2
endfunc

SHARED_	ends

	end
