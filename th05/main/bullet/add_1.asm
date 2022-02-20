	.386
	locals

include libs/master.lib/macros.inc
include th04/math/motion.inc
include th04/main/bullet/bullet.inc
include th05/main/bullet/types.inc

extrn _randring:byte
extrn _randring_p:word
extrn _playperf:byte

extrn _group_is_special:byte

extrn _group_fixedspeed:byte
extrn _group_i_spread_angle:byte
extrn _group_i:byte
extrn _group_i_absolute_angle:byte
extrn _group_i_speed:byte
extrn _group_i_velocity:Point
extrn _bullet_template:bullet_template_t
extrn _bullet_zap:byte

PLAYER_ANGLE_FROM procdesc pascal near \
	x:word, y:word, plus_angle:byte
VECTOR2_NEAR procdesc pascal near \
	ret:word, angle:byte, length:word
_bullets_add_raw procdesc near

MAIN_03 group BULLET_A_TEXT

; ----------------------------------------------------------------------------

BULLET_A_TEXT	segment	word public 'CODE' use16
	assume cs:MAIN_03

; The main algorithm is identical to the TH04 version...
public @playperf_speedtune
@playperf_speedtune proc near
	@@speed_from_playperf	equ <cl>

	shr	al, 1
	mov	@@speed_from_playperf, al
	mul	_playperf
	; ...except for this divisor (32 here vs. 16 in TH04)
	shr	ax, 5
	add	al, @@speed_from_playperf
	cmp	al, (8 shl 4)
	jbe	short @@below_half_a_pixel_per_frame?
	mov	al, (8 shl 4)

@@below_half_a_pixel_per_frame?:
	cmp	al, ((1 shl 4) / 2)
	jnb	short @@ret
	mov	al, ((1 shl 4) / 2)

@@ret:
	ret
@playperf_speedtune endp


public _bullets_add_regular
_bullets_add_regular proc near
	cmp	_bullet_zap, 0
	jnz	short @@ret
	push	word ptr _bullet_template.BT_angle
	call	_bullets_add_raw
	pop	word ptr _bullet_template.BT_angle

@@ret:
	retn
_bullets_add_regular endp
	even


public _bullets_add_special
_bullets_add_special proc near
	cmp	_bullet_zap, 0
	jnz	short @@ret
	mov	_group_is_special, 1
	push	word ptr _bullet_template.BT_angle
	call	_bullets_add_raw
	pop	word ptr _bullet_template.BT_angle
	mov	_group_is_special, 0

@@ret:
	retn
_bullets_add_special endp
	even


public _bullets_add_regular_fixedspeed
_bullets_add_regular_fixedspeed proc near
	mov	_group_fixedspeed, 1
	call	_bullets_add_regular
	mov	_group_fixedspeed, 0
	retn
_bullets_add_regular_fixedspeed endp


public _bullets_add_special_fixedspeed
_bullets_add_special_fixedspeed proc near
	mov	_group_fixedspeed, 1
	call	_bullets_add_special
	mov	_group_fixedspeed, 0
	retn
_bullets_add_special_fixedspeed endp


public _bullet_velocity_and_angle_set
_bullet_velocity_and_angle_set proc pascal near
	uses si, di
	@@spread 	equ <bl>
	@@stack  	equ <bh>
	@@speed  	equ <cl>
	@@group_i	equ <ch>
	@@angle  	equ <si> ; Why 16-bit? Just makes the ASM harder to understand.
	@@done   	equ <di>

	set_done_if_last macro value:req
		local @@nope

		ifdifi <value>, <al>
			mov	al, value
		endif
		dec	al
		cmp	al, @@group_i
		ja	short @@nope
		inc	@@done
	@@nope:
	endm

	xor	@@angle, @@angle
	mov	@@group_i, _group_i
	mov	@@speed, _bullet_template.speed
	mov	bl, _bullet_template.BT_group
	xor	bh, bh

	; This effectively defaults invalid group values to BG_FORCESINGLE, fixing
	; TH01's and TH04's bug that completely filled the array in that case.
	; But come on, that's one MOV instruction we're wastefully executing for
	; regularly conforming code!
	cmp	bx, BG_FORCESINGLE_AIMED
	mov	@@done, 1
	ja	@@no_aim

	xor	@@done, @@done
	add	bx, bx
	mov	ax, cs:@@switch_table[bx]
	mov	@@spread, _bullet_template.spread
	mov	@@stack, _bullet_template.BT_stack

	; Make sure @@spread is ≥ 1, so that we can safely divide by it below.
	or	@@spread, @@spread
	jnz	short @@switch
	inc	@@spread

@@switch:
	jmp	ax
; ---------------------------------------------------------------------------

@@case_single_aimed:
	inc	@@done
	jmp	@@aim
; ---------------------------------------------------------------------------

@@case_single:
	inc	@@done
	jmp	@@no_aim
; ---------------------------------------------------------------------------

@@case_spread_or_ring_stack:
	; Spawns the @@spread bullets within a single level of the stack first,
	; before moving to the next level on the stack.

	; @@speed += ((group_i / @@spread) * bullet_template.stack_speed_delta)
	xor	ah, ah
	mov	al, @@group_i
	div	@@spread
	mov	dl, _bullet_template.stack_speed_delta
	; Ignores the remainder that the DIV above put into AH.
	; Also note that this can easily overflow...
	mul	dl
	add	@@speed, al

	; A ring or spread stack consists of (@@spread * @@stack) bullets in total.
	mov	al, @@spread
	mul	@@stack
	set_done_if_last al

	; @@group_i %= @@spread
	; Then we can continue with regular spread / ring angle calculation.
	xor	ah, ah
	mov	al, @@group_i
	div	@@spread
	mov	@@group_i, ah ; Again, that's where `DIV r8` leaves the remainder!

	; We arrive here for:
	; | not aimed | BG_RING_STACK       | BG_SPREAD_STACK       |
	; | aimed     | BG_RING_STACK_AIMED | BG_SPREAD_STACK_AIMED |
	cmp	_bullet_template.BT_group, BG_RING_STACK
	jz	short @@calculate_ring_angle
	cmp	_bullet_template.BT_group, BG_RING_STACK_AIMED
	jz	short @@calculate_ring_angle
	jmp	short @@calculate_spread_angle
; ---------------------------------------------------------------------------

@@case_spread:
	set_done_if_last	@@spread

	; Mostly identical to TH04's code, except that odd- and even-numbered
	; spreads now use the same code beyond the first bullet.
@@calculate_spread_angle:
	xor	ah, ah	; Remember, @@angle is 16-bit...
	test	@@spread, 1
	jz	short @@even_spread

@@odd_spread:
	or	@@group_i, @@group_i
	jnz	short @@odd_spread_and_not_first_bullet

@@odd_spread_and_first_bullet:
	mov	_group_i_spread_angle, 0
	; Remember, @@angle is still 0x00, from the beginning of the function.
	jmp	short @@got_spread_angle

@@odd_spread_and_not_first_bullet:
	test	@@group_i, 1
	jz	short @@even_numbered_bullet

@@odd_numbered_bullet:
	; @@angle = (group_i_spread_angle += bullet_template.spread_angle_delta)
	mov	al, _bullet_template.spread_angle_delta
	add	_group_i_spread_angle, al
	mov	al, _group_i_spread_angle
	mov	@@angle, ax
	jmp	short @@got_spread_angle

@@even_numbered_bullet:
	; @@angle = (0x100 - group_i_spread_angle)
	mov	al, _group_i_spread_angle
	neg	al
	mov	@@angle, ax
	jmp	short @@got_spread_angle

@@even_spread:
	or	@@group_i, @@group_i
	jnz	short @@even_spread_and_not_first_bullet

@@even_spread_and_first_bullet:
	; @@angle = group_i_spread_angle = (bullet_template.spread_angle_delta / 2)
	mov	al, _bullet_template.spread_angle_delta
	shr	al, 1
	mov	_group_i_spread_angle, al
	mov	@@angle, ax
	jmp	short @@got_spread_angle

@@even_spread_and_not_first_bullet:
	test	@@group_i, 1
	jnz	short @@even_numbered_bullet
	jmp	short @@odd_numbered_bullet

@@got_spread_angle:
	; We arrive here for:
	; | not aimed | BG_SPREAD       | BG_SPREAD_STACK       |
	; | aimed     | BG_SPREAD_AIMED | BG_SPREAD_STACK_AIMED |
	cmp	_bullet_template.BT_group, BG_SPREAD
	jz	@@no_aim
	cmp	_bullet_template.BT_group, BG_SPREAD_STACK
	jz	@@no_aim
	jmp	short @@aim
; ---------------------------------------------------------------------------

@@case_ring:
	set_done_if_last	@@spread

@@calculate_ring_angle:
	; @@angle = ((@@group_i * 0x100) / @@spread)
	; Setting AL to 0 and loading @@group_i directly into AH optimizes away the
	; otherwise necessary multiplication / bit shift. Nifty!
	xor	al, al
	mov	ah, @@group_i
	div	@@spread
	xor	ah, ah
	mov	@@angle, ax

	; We arrive here for:
	; | not aimed | BG_RING       | BG_RING_STACK       |
	; | aimed     | BG_RING_AIMED | BG_RING_STACK_AIMED |
	cmp	_bullet_template.BT_group, BG_RING
	jz	short @@no_aim
	cmp	_bullet_template.BT_group, BG_RING_STACK
	jz	short @@no_aim
	jmp	short @@aim
; ---------------------------------------------------------------------------

@@case_random_angle_and_added_speed:
	; So that's why [randring_p] was needlessly turned into a 16-bit variable
	; in TH04! x86 doesn't support indexing with an 8-bit register. (And who
	; uses XLAT anyway, right?)

	; @@speed += randring_next8_and(to_sp(2.0f) - 1)
	mov	si, _randring_p
	mov	al, _randring[si]
	inc	byte ptr _randring_p
	and	al, 1Fh
	add	@@speed, al

@@case_random_angle:
	; Equivalent to `set_done_if_last @@spread`. Looks like somewhere down the
	; line, ZUN realized that incrementing @@group_i itself is superior over
	; moving to a register and decrementing? At least once we're done with that
	; register.
	inc	@@group_i
	cmp	@@group_i, @@spread
	jb	short @@random_angle_not_done_yet
	inc	@@done

@@random_angle_not_done_yet:
	; @@angle = randring_next8()
	mov	si, _randring_p
	mov	@@angle, word ptr _randring[si]
	and	@@angle, (100h - 1)
	inc	byte ptr _randring_p

	jmp	short @@no_aim
; ---------------------------------------------------------------------------

@@case_stack:
	; @@speed += (bullet_template.stack_speed_delta * group_i)
	mov	al, _bullet_template.stack_speed_delta
	mul	@@group_i
	add	@@speed, al

	; Equivalent to `set_done_if_last @@stack`.
	mov	al, @@stack
	dec	al
	cmp	al, @@group_i
	jle	short @@stack_done

	; Stop spawning bullets if @@speed >= 10.0f, just like in TH04
	cmp	@@speed, (10 shl 4)
	jb	short @@stack_not_speed_capped_yet

@@stack_done:
	inc	@@done

@@stack_not_speed_capped_yet:
	cmp	_bullet_template.BT_group, BG_STACK
	jz	short @@no_aim
; ---------------------------------------------------------------------------

@@aim:
	; Note that the high byte of @@angle is in fact ignored everywhere.
	mov	_group_i_speed, @@speed
	call	player_angle_from pascal, _bullet_template.BT_origin.x, _bullet_template.BT_origin.y, @@angle
	mov	@@speed, _group_i_speed
	mov	@@angle, ax

@@no_aim:
	push	offset _group_i_velocity	; ret
	mov	ax, @@angle
	add	al, _bullet_template.BT_angle
	push	ax	; angle
	mov	_group_i_absolute_angle, al
	mov	_group_i_speed, @@speed
	mov	al, @@speed
	mov	ah, 0
	push	ax	; length
	call	vector2_near
	mov	ax, @@done
	ret

; ---------------------------------------------------------------------------
@@switch_table label word
	dw offset @@case_single
	dw offset @@case_single_aimed
	dw offset @@case_spread
	dw offset @@case_spread ; (aimed)
	dw offset @@case_ring
	dw offset @@case_ring ; (aimed)
	dw offset @@case_stack
	dw offset @@case_stack ; (aimed)
	dw offset @@case_spread_or_ring_stack
	dw offset @@case_spread_or_ring_stack ; (aimed)
	dw offset @@case_spread_or_ring_stack
	dw offset @@case_spread_or_ring_stack ; (aimed)
	dw offset @@case_random_angle
	dw offset @@case_random_angle_and_added_speed
	dw offset @@case_single
	dw offset @@case_single_aimed
_bullet_velocity_and_angle_set endp
BULLET_A_TEXT	ends

	end
