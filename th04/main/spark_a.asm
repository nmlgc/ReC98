; Has no reason to be in ASM, it's only because of stupidly reordered
; instructions compared to what Turbo C++ would normally generate.

	.186
	.model use16 large
	locals

include th02/main/playfld.inc
include th04/main/spark.inc

@RANDRING2_NEXT16_AND$QUI procdesc pascal near \
	mask:word
VECTOR2_NEAR procdesc pascal near \
	ret:word, angle:byte, length:word

extern _sparks:spark_t:SPARK_COUNT
extern _spark_ring_offset:word

main_03 group SPARK_A_TEXT

	.code
	assume cs:main_03

clip macro center_x:req, center_y:req, label_if_clipped:req
	; if(
	; 	(static_cast<unsigned int>(center_x.v) > to_sp(PLAYFIELD_W)) ||
	; 	(static_cast<unsigned int>(center_y.v) > to_sp(PLAYFIELD_H))
	; ) {
	; 	goto label_if_clipped;
	; }
	cmp	center_x, (PLAYFIELD_W shl 4)
	ja	short label_if_clipped
	cmp	center_y, (PLAYFIELD_H shl 4)
	ja	short label_if_clipped
endm

init macro p:req, center_x:req, center_y:req
	; p->flag = F_ALIVE;
	; p->age = 0;
	; p->pos.cur.x = center_x;
	; p->pos.cur.y = center_y;
	mov	word ptr [p+spark_t.flag], F_ALIVE or (0 shl 8)
	mov	ax, @@center_x
	mov	[p+spark_t.pos.cur.x], ax
	mov	ax, @@center_y
	mov	[p+spark_t.pos.cur.y], ax
endm

ring_offset_next macro
	add	_spark_ring_offset, size spark_t
	cmp	_spark_ring_offset, (SPARK_COUNT * size spark_t)
	jb	short @@not_wrapped
	mov	_spark_ring_offset, 0

@@not_wrapped:
endm

public @SPARKS_ADD_RANDOM$Q20%SUBPIXELBASE$TI$TI%T1II
@sparks_add_random$q20%SubpixelBase$ti$ti%t1ii proc far
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@count:word, @@radius_min:word, @@center_y:word, @@center_x:word

	@@p equ <si>
	@@sparks_remaining equ <di>

	push	bp
	mov	bp, sp
	clip	@@center_x, @@center_y, @@ret

	; The fact that these are here and not at the top of the function is the
	; entire reason why this function is undecompilable.
	push	si
	push	di

	mov 	@@sparks_remaining, @@count

@@loop:
	mov 	@@p, _spark_ring_offset
	add 	@@p, offset _sparks
	cmp 	[@@p+spark_t.flag], F_FREE
	jnz 	short @@next
	init	@@p, @@center_x, @@center_y

	; vector2_near(
	; 	p.pos.velocity,
	; 	p.angle,
	; 	randring2_next16_ge_lt_sp(radius_min, (radius_min + 2.0f))
	; );
	call	@randring2_next16_and$qui pascal, ((2 shl 4) - 1)
	add 	ax, @@radius_min
	lea 	bx, [@@p+spark_t.pos.velocity]
	call	vector2_near pascal, bx, [@@p+spark_t.SPARK_ANGLE], ax

@@next:
	ring_offset_next
	dec	@@sparks_remaining
	jnz	short @@loop
	pop	di
	pop	si

@@ret:
	pop	bp
	retf	8
@sparks_add_random$q20%SubpixelBase$ti$ti%t1ii endp


public @SPARKS_ADD_CIRCLE$Q20%SUBPIXELBASE$TI$TI%T1II
@sparks_add_circle$q20%SubpixelBase$ti$ti%t1ii proc near
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@count:word, @@radius_min:word, @@center_y:word, @@center_x:word

	@@p equ <si>
	@@angle_premultiplied equ <di>

	push	bp
	mov 	bp, sp
	clip	@@center_x, @@center_y, @@ret

	; The fact that these are here and not at the top of the function is the
	; entire reason why this function is undecompilable.
	push	si
	push	di

	; Premultiply 360° by the number of circle points, for added precision when
	; dividing later.
	mov 	@@angle_premultiplied, @@count
	shl 	@@angle_premultiplied, 8 ; *= 0x100

@@loop:
	mov 	@@p, _spark_ring_offset
	add 	@@p, offset _sparks
	cmp 	[@@p+spark_t.flag], F_FREE
	jnz 	short @@next
	init	@@p, @@center_x, @@center_y

	; vector2_near(p.pos.velocity, ((0x100 * i) / count), radius);
	; (with [i] simply being the current loop iteration)
	lea 	ax, [@@p+spark_t.pos.velocity]
	push	ax
	xor 	dx, dx
	mov 	ax, @@angle_premultiplied
	div 	@@count
	xor 	ah, ah
	push	ax
	push	@@radius_min
	call	vector2_near

@@next:
	ring_offset_next
	sub	@@angle_premultiplied, 100h
	jnz	short @@loop
	pop	di
	pop	si

@@ret:
	pop	bp
	retn	8
@sparks_add_circle$q20%SubpixelBase$ti$ti%t1ii endp
	even

	end
