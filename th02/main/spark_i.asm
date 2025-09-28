	.386
	.model use16 small

include th01/math/subpixel.inc
include th02/main/entity.inc
include th02/main/sparks.inc

	@TILES_INVALIDATE_RECT$QIIII procdesc far
	extrn _page_back:byte
	extrn _page_front:byte
	extrn _sparks:spark_t:SPARK_COUNT

	.code

public @sparks_invalidate$qv
@sparks_invalidate$qv proc far
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	ax, offset _sparks
	mov	si, ax
	xor	di, di
	jmp	short @@more?

@@loop:
	cmp	[si+spark_t.SPARK_flag], F_FREE
	jz	short @@next
	mov	al, _page_back
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	mov	ax, [bx+si+spark_t.SPARK_screen_topleft+Point.x]
	sar	ax, SUBPIXEL_BITS
	push	ax	; left
	mov	ax, [bx+si+spark_t.SPARK_screen_topleft+Point.y]
	sar	ax, SUBPIXEL_BITS
	push	ax	; top
	cmp	[si+spark_t.SPARK_render_as], SRA_DOT
	jnz	short @@is_sprite
	push	1	; w
	push	1	; h
	jmp	short @@invalidate

@@is_sprite:
	push	SPARK_W	; w
	push	SPARK_H	; h

@@invalidate:
	call	@tiles_invalidate_rect$qiiii
	cmp	[si+spark_t.SPARK_flag], F_REMOVE
	jnz	short @@flip_pos
	mov	[si+spark_t.SPARK_flag], F_FREE
	jmp	short @@next

@@flip_pos:
	mov	al, _page_front
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	mov	ax, [bx+si+spark_t.SPARK_screen_topleft+Point.x]
	mov	dx, [bx+si+spark_t.SPARK_screen_topleft+Point.y]
	xor	bx, size Point
	mov	[bx+si+spark_t.SPARK_screen_topleft+Point.x], ax
	mov	[bx+si+spark_t.SPARK_screen_topleft+Point.y], dx

@@next:
	inc	di
	add	si, size spark_t

@@more?:
	cmp	di, SPARK_COUNT
	jl	short @@loop
	pop	di
	pop	si

	; ZUN bloat: This mismatched LEAVE is the entire reason this is
	; undecompilable without either code generation or mistake patching:
	;
	; 	https://rec98.nmlgc.net/blog/2023-03-30#mistakes-2023-03-30
	leave

	ret
@sparks_invalidate$qv endp
_TEXT ends

	end
