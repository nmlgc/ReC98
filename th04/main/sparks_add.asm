; Adds [count] new spark sprites with the given [distance] in random
; directions away from ([center_x], [center_y]).

; int pascal sparks_add_random(Subpixel center_x, Subpixel center_y, Subpixel distance, int count);
public SPARKS_ADD_RANDOM
sparks_add_random	proc far

@@count   	= word ptr  6
@@distance	= word ptr  8
@@center_y	= word ptr  0Ah
@@center_x	= word ptr  0Ch

	push	bp
	mov	bp, sp
	cmp	[bp+@@center_x], (PLAYFIELD_W shl 4)
	ja	short @@ret
	cmp	[bp+@@center_y], (PLAYFIELD_H shl 4)
	ja	short @@ret
	push	si
	push	di
	mov	di, [bp+@@count]

@@loop:
	mov	si, _spark_next_free_offset
	add	si, offset _sparks
	cmp	[si+spark_t.flag], 0
	jnz	short @@wrap_offset?
	mov	word ptr [si+spark_t.flag], 1
	mov	ax, [bp+@@center_x]
	mov	[si+spark_t.pos.cur.x],	ax
	mov	ax, [bp+@@center_y]
	mov	[si+spark_t.pos.cur.y],	ax
	call	randring2_next16_and pascal, ((2 shl 4) - 1)
	add	ax, [bp+@@distance]
	lea	bx, [si+spark_t.pos.velocity]
	call	vector2_near pascal, bx, [si+spark_t.SPARK_ANGLE], ax

@@wrap_offset?:
	add	_spark_next_free_offset, size spark_t
	cmp	_spark_next_free_offset, SPARK_COUNT * size spark_t
	jb	short @@more?
	mov	_spark_next_free_offset, 0

@@more?:
	dec	di
	jnz	short @@loop
	pop	di
	pop	si

@@ret:
	pop	bp
	retf	8
sparks_add_random	endp


; Adds [count] new spark sprites along a circle with the given [distance] away
; from ([center_x], [center_y]). Obviously ignores the random angle set in
; sparks_init().

; int pascal sparks_add_circle(Subpixel center_x, Subpixel center_y, Subpixel distance, int count);
public SPARKS_ADD_CIRCLE
sparks_add_circle	proc near

@@count   	= word ptr  4
@@distance	= word ptr  6
@@center_y	= word ptr  8
@@center_x	= word ptr  0Ah

	push	bp
	mov	bp, sp
	cmp	[bp+@@center_x], (PLAYFIELD_W shl 4)
	ja	short @@ret
	cmp	[bp+@@center_y], (PLAYFIELD_H shl 4)
	ja	short @@ret
	push	si
	push	di
	mov	di, [bp+@@count]
	shl	di, 8

@@loop:
	mov	si, _spark_next_free_offset
	add	si, offset _sparks
	cmp	[si+spark_t.flag], 0
	jnz	short @@wrap_offset?
	mov	word ptr [si+spark_t.flag], 1
	mov	ax, [bp+@@center_x]
	mov	[si+spark_t.pos.cur.x],	ax
	mov	ax, [bp+@@center_y]
	mov	[si+spark_t.pos.cur.y],	ax
	lea	ax, [si+spark_t.pos.velocity]
	push	ax
	xor	dx, dx
	mov	ax, di
	div	[bp+@@count]
	xor	ah, ah
	push	ax
	push	[bp+@@distance]
	call	vector2_near

@@wrap_offset?:
	add	_spark_next_free_offset, size spark_t
	cmp	_spark_next_free_offset, SPARK_COUNT * size spark_t
	jb	short @more?
	mov	_spark_next_free_offset, 0

@more?:
	sub	di, 256
	jnz	short @@loop
	pop	di
	pop	si

@@ret:
	pop	bp
	retn	8
sparks_add_circle	endp
	nop
