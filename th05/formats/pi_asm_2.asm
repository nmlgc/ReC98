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
