	.386
	locals

include libs/master.lib/macros.inc
include th04/math/motion.inc
include th05/main/bullet/types.inc
include th04/main/bullet/bullet.inc

MAIN_03 group MAIN_031_TEXT

extrn _bullet_template:bullet_template_t
extrn _playperf:byte

; ----------------------------------------------------------------------------

MAIN_031_TEXT	segment	word public 'CODE' use16
	assume cs:MAIN_03

tune	proc
public TUNE_FOR_EASY
public TUNE_FOR_HARD
public TUNE_FOR_LUNATIC

; Local variable registers
; ------------------------
@@group_reg equ <bx>
@@group equ <bl>

@@group_table equ <cx>

@@spread_reg equ <ax>
@@spread equ <al>
@@spread_angle_delta equ <ah>

@@stack_reg equ <dx>
@@stack equ <dl>
@@stack_speed_delta equ <dh>
; ------------------------

TUNE_FOR_EASY	label near
	movzx	@@group_reg, _bullet_template.BT_group
	cmp	@@group, BG_SPREAD
	jb	short @@easy_ret
	cmp	@@group, BG_RANDOM_ANGLE_AND_SPEED
	ja	short @@easy_ret
	sub	@@group, BG_SPREAD
	mov	@@group_table, offset @@easy_group_table
	jmp	short @@set_vars_and_dispatch
; ---------------------------------------------------------------------------

@@easy_spread:
@@easy_spread_stack:
	cmp	@@spread, 3
	jb	short @@easy_ret
	sub	_bullet_template.spread, 2
	retn
; ---------------------------------------------------------------------------

@@easy_stack:
	shr	@@stack_speed_delta, 2
	sub	_bullet_template.stack_speed_delta, @@stack_speed_delta

	; Since unused fields of the bullet template aren't typically reset, this
	; translates to "delta of the last spread that was fired" - whenever that
	; was. uth05win thought this is a bug and changed it to @@stack.
	cmp	@@spread_angle_delta, 2
	jb	short @@easy_ret
	dec	_bullet_template.BT_stack
	retn
; ---------------------------------------------------------------------------

@@easy_ring:
@@easy_ring_stack:
@@easy_random:
	shr	_bullet_template.spread, 1

@@easy_ret:
	retn
; ---------------------------------------------------------------------------

	even
@@easy_group_table	label word
	dw offset @@easy_spread
	dw offset @@easy_ring
	dw offset @@easy_stack
	dw offset @@easy_spread_stack
	dw offset @@easy_ring_stack
	dw offset @@easy_random

; ---------------------------------------------------------------------------
; ---------------------------------------------------------------------------

TUNE_FOR_HARD	label near
	movzx	@@group_reg, _bullet_template.BT_group

	; "Well, I'd like to tune single bullets on Hard, but not spreads… so
	; let's just handle single bullets outside the table dispatch! :zunpet:"
	cmp	@@group, BG_SINGLE_AIMED
	jbe	short @@hard_single

	cmp	@@group, BG_RING
	jb	short @@hard_ret
	cmp	@@group, BG_RANDOM_ANGLE_AND_SPEED
	ja	short @@hard_ret
	sub	@@group, BG_RING
	mov	@@group_table, offset @@hard_group_table

@@set_vars_and_dispatch:
	mov	@@spread_reg, word ptr _bullet_template.spread
	mov	@@stack_reg, word ptr _bullet_template.BT_stack
	and	@@group, (not BGC0_AIMED)
	add	@@group_reg, @@group_table
	jmp	word ptr cs:[@@group_reg]
; ---------------------------------------------------------------------------

@@hard_single:
	add	_bullet_template.BT_group, BGCS_STACK
	mov	word ptr _bullet_template.BT_stack, (6 shl 8) or 2
	retn
; ---------------------------------------------------------------------------

@@hard_stack:
@@hard_spread_stack:
	shr	@@stack_speed_delta, 1
	add	_bullet_template.stack_speed_delta, @@stack_speed_delta
	retn
; ---------------------------------------------------------------------------

@@hard_ring:
@@hard_ring_stack:
	shr	@@spread, 2
	cmp	@@spread, 6
	jbe	short @@hard_add_to_spread
	mov	@@spread, 6

@@hard_add_to_spread:
	add	_bullet_template.spread, @@spread

@@hard_ret:
	retn
; ---------------------------------------------------------------------------

@@hard_random:
	shr	@@spread, 1
	jmp	short @@hard_add_to_spread

	even
@@hard_group_table	label word
	dw offset @@hard_ring
	dw offset @@hard_stack
	dw offset @@hard_spread_stack
	dw offset @@hard_ring_stack
	dw offset @@hard_random

; ---------------------------------------------------------------------------
; ---------------------------------------------------------------------------

TUNE_FOR_LUNATIC	label near
	movzx	@@group_reg, _bullet_template.BT_group
	cmp	@@group, BG_RANDOM_ANGLE_AND_SPEED
	ja	short @@lunatic_ret
	mov	@@group_table, offset @@lunatic_group_table
	jmp	short @@set_vars_and_dispatch
; ---------------------------------------------------------------------------

@@lunatic_single:
	add	_bullet_template.BT_group, BGCC_SPREAD
	mov	word ptr _bullet_template.spread, (6 shl 8) or 3
	retn
; ---------------------------------------------------------------------------

@@lunatic_stack:
	shr	@@stack_speed_delta, 1
	add	_bullet_template.stack_speed_delta, @@stack_speed_delta
	inc	_bullet_template.BT_stack
	retn
; ---------------------------------------------------------------------------

@@lunatic_spread:
@@lunatic_spread_stack:
	add	_bullet_template.spread, 2
	retn
; ---------------------------------------------------------------------------

@@lunatic_ring:
@@lunatic_ring_stack:
	; mov	al, @@spread
	xor	ah, ah
	mov	dl, 3
	div	dl	; @@spread /= 3
	cmp	@@spread, 12
	jbe	short @@lunatic_add_to_spread
	mov	@@spread, 12

@@lunatic_add_to_spread:
@@lunatic_random:
	add	_bullet_template.spread, @@spread

@@lunatic_ret:
	retn

	even
@@lunatic_group_table	label word
	dw offset @@lunatic_single
	dw offset @@lunatic_spread
	dw offset @@lunatic_ring
	dw offset @@lunatic_stack
	dw offset @@lunatic_spread_stack
	dw offset @@lunatic_ring_stack
	dw offset @@lunatic_random
tune	endp
MAIN_031_TEXT	ends

	end
