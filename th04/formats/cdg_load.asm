	.386
	.model large SHARED_
	locals

include th03/arg_bx.inc
include th03/formats/cdg.inc

	extrn FILE_ROPEN:proc
	extrn FILE_READ:proc
	extrn FILE_SEEK:proc
	extrn FILE_CLOSE:proc
	extrn HMEM_ALLOCBYTE:proc
	extrn HMEM_FREE:proc
	extrn _cdg_slots:cdg_t:CDG_SLOT_COUNT
	extrn _cdg_noalpha:byte
	extrn cdg_images_to_load:byte

g_SHARED group SHARED, SHARED_
SHARED	segment word public 'CODE' use16
SHARED	ends

SHARED_	segment word public 'CODE' use16
	assume cs:g_SHARED

public CDG_LOAD_SINGLE_NOALPHA
public CDG_LOAD_SINGLE

cdg_load_single_noalpha label proc
	mov	_cdg_noalpha, 1
	align	2

cdg_load_single	proc far

@@n   	=  word ptr  6
@@fn  	= dword	ptr  8
@@slot	=  word ptr  12

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, [bp+@@slot]
	push	di
	nop	; This was definitely compiled from C...
	call	cdg_free
	shl	di, 4	; *= size cdg_t
	add	di, offset _cdg_slots
	call	file_ropen pascal, large [bp+@@fn]
	call	file_read pascal, ds, di, size cdg_t
	mov	ax, [di+cdg_t.CDG_plane_size]
	mov	dx, ax
	cmp	[di+cdg_t.plane_layout], CDG_COLORS
	jz	short @@read
	shl	ax, 2
	cmp	[di+cdg_t.plane_layout], CDG_ALPHA
	jz	short @@read
	add	ax, dx

@@read:
	mul	[bp+@@n]
	movzx	eax, ax
	call	file_seek pascal, eax, 1
	call	cdg_read_single
	call	file_close
	mov	_cdg_noalpha, 0
	pop	di
	pop	si
	pop	bp
	retf	8
cdg_load_single endp
	align	2

; Reads a single CDG image from the master.lib file, which previously has been
; positioned at the beginning of the image data, into the slot in DI.
cdg_read_single proc near
	mov	al, [di+cdg_t.plane_layout]
	or	al, al	; AL == CDG_COLORS?
	jz	short @@colors
	cmp	al, CDG_ALPHA
	jz	short @@alpha
	cmp	_cdg_noalpha, 0
	jnz	short @@skip_alpha

@@alpha:
	call	hmem_allocbyte pascal, [di+cdg_t.CDG_plane_size]
	mov	[di+cdg_t.seg_alpha], ax
	call	file_read pascal, ax, 0, [di+cdg_t.CDG_plane_size]
	jmp	short @@colors

@@skip_alpha:
	movzx	eax, [di+cdg_t.CDG_plane_size]
	call	file_seek pascal, eax, 1

@@colors:
	cmp	[di+cdg_t.plane_layout], CDG_ALPHA
	jz	short @@ret
	mov	ax, [di+cdg_t.CDG_plane_size]
	shl	ax, 2
	call	hmem_allocbyte pascal, ax
	mov	[di+cdg_t.seg_colors], ax
	push	ax
	push	0
	mov	ax, [di+cdg_t.CDG_plane_size]
	shl	ax, 2
	push	ax
	call	file_read

@@ret:
	retn
cdg_read_single endp


public CDG_LOAD_ALL_NOALPHA
public CDG_LOAD_ALL

cdg_load_all_noalpha label proc
	mov	_cdg_noalpha, 1
	align	2

cdg_load_all proc far

@@fn        	= dword	ptr  6
@@slot_first	=  word ptr  10

	push	bp
	mov	bp, sp
	push	si
	push	di
	call	file_ropen pascal, large [bp+@@fn]
	mov	di, [bp+@@slot_first]
	shl	di, 4	; *= size cdg_t
	add	di, offset _cdg_slots
	call	file_read pascal, ds, di, size cdg_t
	mov	si, di
	mov	bp, [bp+@@slot_first]
	mov	al, cdg_t.image_count[si]
	mov	cdg_images_to_load, al
	push	ds
	pop	es

@@loop:
	call	cdg_free pascal, bp
	mov	cx, (cdg_t.seg_alpha / dword)
	rep movsd
	sub	si, cdg_t.seg_alpha
	sub	di, cdg_t.seg_alpha
	call	cdg_read_single
	inc	bp
	add	di, size cdg_t
	dec	cdg_images_to_load
	jnz	short @@loop
	call	file_close
	mov	_cdg_noalpha, 0
	pop	di
	pop	si
	pop	bp
	retf	6
cdg_load_all endp


public CDG_FREE
cdg_free proc far
arg_bx	far, @slot:word

	push	di
	mov	di, @slot
	shl	di, 4	; *= size cdg_t
	add	di, offset _cdg_slots.seg_alpha
	cmp	word ptr [di], 0
	jz	short @@colors
	call	hmem_free pascal, word ptr [di]
	mov	word ptr [di], 0

@@colors:
	add	di, word ; = seg_colors
	cmp	word ptr [di], 0
	jz	short @@ret
	call	hmem_free pascal, word ptr [di]
	mov	word ptr [di], 0

@@ret:
	pop	di
	ret_bx
cdg_free endp
	align 2


public CDG_FREE_ALL
cdg_free_all proc far
	push	si
	mov	si, CDG_SLOT_COUNT - 1

@@loop:
	call	cdg_free pascal, si
	dec	si
	jge	short @@loop
	pop	si
	retf
cdg_free_all endp
SHARED_	ends

	end
