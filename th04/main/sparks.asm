public _sparks_update
_sparks_update proc near
	push	si
	push	di
	mov	di, SPARK_COUNT
	mov	si, offset _sparks

@@loop:
	cmp	[si+spark_t.flag], 0
	jz	short @@more?
	cmp	[si+spark_t.flag], 1
	jz	short @@update
	mov	[si+spark_t.flag], 0
	jmp	short @@more?

@@update:
	lea	ax, [si+spark_t.pos]
	call	@PlayfieldMotion@update_seg1$qv pascal, ax
	add	ax, ((SPARK_W / 2) shl 4)
	cmp	ax, ((PLAYFIELD_W + SPARK_W) shl 4)
	jnb	short @@remove
	add	dx, ((SPARK_H / 2) shl 4)
	cmp	dx, ((PLAYFIELD_H + SPARK_H) shl 4)
	jb	short @@age

@@remove:
	mov	[si+spark_t.flag], 2
	jmp	short @@more?

@@age:
	inc	[si+spark_t.pos.velocity.y]
	inc	[si+spark_t.age]
	cmp	[si+spark_t.age], 40
	jbe	short @@more?
	mov	[si+spark_t.flag], 2

@@more?:
	add	si, size spark_t
	dec	di
	jg	short @@loop
	pop	di
	pop	si
	retn
_sparks_update endp


public _sparks_render
_sparks_render proc near
	push	si
	push	di
	mov	ah, GC_BR
	call	_grcg_setcolor_direct_seg1_raw
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	di, SPARK_COUNT
	mov	si, offset _sparks

@@loop:
	cmp	[si+spark_t.flag], 1
	jnz	short @@more?
	mov	ax, [si+spark_t.pos.cur.y]
	add	ax, ((PLAYFIELD_TOP - (SPARK_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	mov	dx, ax
	mov	ax, [si+spark_t.pos.cur.x]
	add	ax, ((PLAYFIELD_LEFT - (SPARK_W / 2)) shl 4)
	sar	ax, 4	; → actual pixels
	mov	cl, [si+spark_t.age]
	call	@spark_render

@@more?:
	add	si, size spark_t
	dec	di
	jg	short @@loop
	pop	di
	pop	si
	retn
_sparks_render endp
	even


public _sparks_invalidate
_sparks_invalidate proc near
	push	si
	push	di
	mov	_tile_invalidate_box, (SPARK_W shl 16) or SPARK_H
	mov	di, SPARK_COUNT_BUG
	mov	si, offset _sparks

@@loop:
	cmp	[si+spark_t.flag], 0
	jz	short @@more?
	call	tiles_invalidate_around pascal, dword ptr [si+spark_t.pos.prev]

@@more?:
	add	si, size spark_t
	dec	di
	jg	short @@loop
	pop	di
	pop	si
	retn
_sparks_invalidate endp


public _sparks_init
_sparks_init proc near
	push	si
	push	di
	mov	si, offset _sparks
	mov	di, SPARK_COUNT_BUG

@@loop:
	call	IRand
	mov	byte ptr [si+spark_t.SPARK_angle], al
	add	si, size spark_t
	dec	di
	jnz	short @@loop
	mov	byte ptr _spark_next_free_offset, 0
	pop	di
	pop	si
	retn
_sparks_init endp
