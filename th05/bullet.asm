	.386
	locals

include libs/master.lib/macros.inc
include th04/math/motion.inc
include th04/main/bullet/bullet.inc
include th04/main/gather.inc
include th05/main/bullet/types.inc
include th05/sprites/main_pat.inc

extrn _bullet_template:bullet_template_t
extrn _bullet_template_special_angle:bullet_special_angle_t
extrn _bullet_clear_time:byte
extrn _pellets:bullet_t:PELLET_COUNT
extrn _bullets16:bullet_t:PELLET_COUNT
extrn _gather_template:gather_template_t

BULLET_PATNUM_FOR_ANGLE procdesc pascal near \
	patnum_base:word, angle:byte
_bullets_add_regular procdesc near
_bullet_velocity_and_angle_set procdesc near
_bullet_template_clip procdesc near
_gather_add_bullets procdesc near

; Own data
extrn _group_is_special:byte

; Own BSS
extrn _group_i:byte
extrn _group_i_absolute_angle:byte
extrn _group_i_speed:byte
extrn _group_i_velocity:Point

MAIN_03 group MAIN_031_TEXT

; ----------------------------------------------------------------------------

MAIN_031_TEXT	segment	word public 'CODE' use16
	assume cs:MAIN_03

; Identical to TH04's decompiled version, except for:
; • regular and special bullets being handled within the same function,
; • the TH05-specific changes to the spawn types, and
; • the TH05-specific changes related to BMS_SLOWDOWN (see bullet.hpp)
public _bullets_add_raw
_bullets_add_raw proc near
	@@group_done	equ <cl>

	; Sigh. Dropping down to ASM, and then not even turning [spawn_type] into
	; a proper bitfield. If it was, then a TEST for BST_GATHER_PELLET would
	; have been enough here.
	cmp	_bullet_template.spawn_type, (BST_GATHER_PELLET or BST_NO_SLOWDOWN)
	jz	short @@is_gather_pellet
	cmp	_bullet_template.spawn_type, BST_GATHER_PELLET
	jnz	short @@no_gather

@@is_gather_pellet:
	mov	eax, _bullet_template.BT_origin
	mov	_gather_template.GT_center, eax
	mov	_gather_template.GT_velocity, 0
	mov	_gather_template.GT_radius, (64 shl 4)
	mov	_gather_template.GT_angle_delta, 02h
	mov	_gather_template.GT_col, 9
	mov	_gather_template.GT_ring_points, 8
	push	word ptr _bullet_template.spawn_type
	dec	_bullet_template.spawn_type
	cmp	_group_is_special, 0
	jz	short @@gather_not_special
	mov	_bullet_template.spawn_type, BST_GATHER_NORMAL_SPECIAL_MOVE

@@gather_not_special:
	call	_gather_add_bullets
	pop	word ptr _bullet_template.spawn_type

@@clipped:
	retn
; ---------------------------------------------------------------------------

@@no_gather:
	call	_bullet_template_clip
	or	al, al
	jnz	short  @@clipped
	push	si
	push	di
	cmp	_bullet_template.patnum, 0
	jnz	short @@is_bullet16
	mov	si, offset _pellets[(PELLET_COUNT - 1) * size bullet_t]
	mov	di, PELLET_COUNT
	jmp	short @@determine_spawn_state
; ---------------------------------------------------------------------------

@@is_bullet16:
	mov	si, offset _bullets16[(BULLET16_COUNT - 1) * size bullet_t]
	mov	di, BULLET16_COUNT

@@determine_spawn_state:
	mov	dl, BSS_GRAZEABLE
	mov	al, _bullet_template.spawn_type
	and	al, (BST_NO_SLOWDOWN - 1)
	cmp	al, BST_CLOUD_BACKWARDS
	jz	short @@is_cloud_backwards
	cmp	al, BST_CLOUD_FORWARDS
	jnz	short @@determine_move_state
	mov	dl, BSS_CLOUD_FORWARDS
	jmp	short @@determine_move_state
; ---------------------------------------------------------------------------

@@is_cloud_backwards:
	mov	dl, BSS_CLOUD_BACKWARDS

@@determine_move_state:
	cmp	_group_is_special, 0
	; If special, we don't care about AL, as the code path that contains
	; @@move_state is never taken. so any garbage in AL doesn't matter.
	; (Jumping over the @@move_state assignment would have surely been
	; prettier, though!)
	jnz	short @@got_both_spawn_and_move_states

	mov	al, BMS_REGULAR
	cmp	_bullet_template.speed, (BMS_SLOWDOWN_BASE_SPEED - 8)
	jb	short @@speed_below_slowdown_threshold
	cmp	_bullet_clear_time, 0
	jz	short @@got_both_spawn_and_move_states

@@speed_below_slowdown_threshold:
	test	_bullet_template.spawn_type, BST_NO_SLOWDOWN
	jnz	short @@got_both_spawn_and_move_states
	xor	al, al	; BMS_SLOWDOWN

@@got_both_spawn_and_move_states:
	mov	cs:@@spawn_state, dl
	mov	cs:@@move_state, al
	mov	_group_i, 0
	jmp	short $+2

@@loop:
	cmp	[si+bullet_t.flag], 0
	jnz	@@next
	mov	[si+bullet_t.flag], 1

	@@spawn_state = byte ptr $+3
	mov	[si+bullet_t.spawn_state], 123
	mov	eax, _bullet_template.BT_origin
	mov	dword ptr [si+bullet_t.pos.cur], eax
	cmp	_group_is_special, 0
	jnz	short @@init_special

	@@move_state = byte ptr $+3
	mov	[si+bullet_t.move_state], 123
	mov	[si+bullet_t.slowdown_time], BMS_SLOWDOWN_FRAMES
	mov	al, BMS_SLOWDOWN_BASE_SPEED
	sub	al, _bullet_template.speed
	mov	[si+bullet_t.slowdown_speed_delta], al
	jmp	short @@init_common
; ---------------------------------------------------------------------------

@@init_special:
	mov	dword ptr [si+bullet_t.BULLET_origin], eax
	mov	[si+bullet_t.move_state], BMS_SPECIAL
	mov	[si+bullet_t.distance], 0
	mov	[si+bullet_t.BULLET_ax], 0
	mov	al, _bullet_template_special_angle
	mov	[si+bullet_t.BULLET_dx], al
	mov	al, _bullet_template.BT_special_motion
	mov	[si+bullet_t.special_motion], al

@@init_common:
	mov	[si+bullet_t.age], 0
	mov	al, _bullet_template.BT_group
	mov	[si+bullet_t.from_group], al
	call	_bullet_velocity_and_angle_set
	mov	@@group_done, al
	mov	al, _bullet_template.patnum
	mov	ah, 0
	cmp	al, PAT_BULLET16_D
	jb	short @@is_nondirectional
	call	bullet_patnum_for_angle pascal, ax, word ptr _group_i_absolute_angle

@@is_nondirectional:
	mov	[si+bullet_t.BULLET_patnum], ax
	mov	eax, _group_i_velocity
	mov	dword ptr [si+bullet_t.pos.velocity], eax
	mov	al, _group_i_absolute_angle
	mov	[si+bullet_t.BULLET_angle], al
	mov	al, _group_i_speed
	mov	[si+bullet_t.speed_final], al
	mov	[si+bullet_t.speed_cur], al
	or	@@group_done, @@group_done
	jnz	short @@ret
	inc	_group_i

@@next:
	sub	si, size bullet_t
	dec	di
	jnz	@@loop

@@ret:
	pop	di
	pop	si
	retn
_bullets_add_raw endp


public _bullets_add_regular_far
_bullets_add_regular_far proc far
		call	_bullets_add_regular
		retf
_bullets_add_regular_far endp


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
	mov	@@group_table, offset MAIN_03:@@easy_group_table
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
	mov	@@group_table, offset MAIN_03:@@hard_group_table

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
	mov	@@group_table, offset MAIN_03:@@lunatic_group_table
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
