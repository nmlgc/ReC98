EXPLOSION_TYPED macro
	mov	[si+explosion_t.flag], 1
	mov	[si+explosion_t.age], 0
	mov	ax, _boss_pos.cur.x
	mov	[si+explosion_t.center.x], ax
	mov	ax, _boss_pos.cur.y
	mov	[si+explosion_t.center.y], ax
	mov	[si+explosion_t.EXPLOSION_radius_cur.x], 8
	mov	[si+explosion_t.EXPLOSION_radius_cur.y], 8
	mov	[si+explosion_t.EXPLOSION_radius_delta.x], (11 shl 4)
	mov	[si+explosion_t.EXPLOSION_radius_delta.y], (11 shl 4)
	mov	[si+explosion_t.angle_offset], 0
	mov	bx, [bp+@@type]
	dec	bx
	cmp	bx, 3
	ja	short @@ret
	add	bx, bx
	jmp	cs:@@switch[bx]

@@type1:
	mov	[si+explosion_t.angle_offset], 32
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@type2:
	mov	[si+explosion_t.angle_offset], -32
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@type3:
	mov	[si+explosion_t.EXPLOSION_radius_delta.x], (13 shl 4)
	mov	[si+explosion_t.EXPLOSION_radius_delta.y], (7 shl 4)
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@type4:
	mov	[si+explosion_t.EXPLOSION_radius_delta.x], (7 shl 4)
	mov	[si+explosion_t.EXPLOSION_radius_delta.y], (13 shl 4)

@@ret:
	call	snd_se_play pascal, 15
	pop	si
	pop	bp
	retn	2

@@switch	label word
	dw offset @@type1
	dw offset @@type2
	dw offset @@type3
	dw offset @@type4
endm

public @BOSS_EXPLODE_SMALL$Q16EXPLOSION_TYPE_T
@boss_explode_small$q16explosion_type_t proc near

@@type	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _explosions_small
	cmp	[si+explosion_t.flag], 0
	jz	short @@set
	add	si, size explosion_t

@@set:
	EXPLOSION_TYPED
@boss_explode_small$q16explosion_type_t endp
