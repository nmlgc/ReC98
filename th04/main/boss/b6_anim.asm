Y6SS_VANISHED = 0
Y6SS_PARASOL_BACK_OPEN = 1
Y6SS_PARASOL_BACK_CLOSED = 2
Y6SS_PARASOL_FORWARD = 3
Y6SS_PARASOL_LEFT = 4
Y6SS_PARASOL_SHIELD = 8

public _yuuka6_anim_parasol_back_close
_yuuka6_anim_parasol_back_close	proc near

@@frame		= word ptr -2

	enter	2, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_OPEN
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 5		; switch 5 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+0Ah] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_OPEN
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_HALFOPEN
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_HALFCLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_3:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_CLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_CLOSED
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
@@switch_table	dw	1, 7, 13, 19, 25	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@cel_3
	dw offset @@done
_yuuka6_anim_parasol_back_close	endp


public _yuuka6_anim_parasol_back_open
_yuuka6_anim_parasol_back_open	proc near

@@frame		= word ptr -2

	enter	2, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_CLOSED
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 5		; switch 5 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+0Ah] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_CLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_HALFCLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_HALFOPEN
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_3:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_OPEN
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_OPEN
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
	db 0
@@switch_table	dw	1, 7, 13, 19, 25	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@cel_3
	dw offset @@done
_yuuka6_anim_parasol_back_open	endp


public _yuuka6_anim_parasol_back_pull_forward
_yuuka6_anim_parasol_back_pull_forward	proc near

@@frame		= word ptr -2

	enter	2, 0
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 5		; switch 5 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+0Ah] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_CLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_LEFT_PULL
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_LEFT_FORWARD_PULL
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_3:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_FORWARD_CLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_FORWARD
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
@@switch_table	dw	1, 7, 13, 19, 25	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@cel_3
	dw offset @@done
_yuuka6_anim_parasol_back_pull_forward	endp


public _yuuka6_anim_parasol_back_pull_left
_yuuka6_anim_parasol_back_pull_left	proc near

@@frame		= word ptr -2

	enter	2, 0
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 4		; switch 4 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+8] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_CLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_LEFT_PULL
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_LEFT
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_LEFT
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
@@switch_table	dw	1, 7, 13, 19	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@done
_yuuka6_anim_parasol_back_pull_left	endp


public _yuuka6_anim_parasol_left_spin_back
_yuuka6_anim_parasol_left_spin_back	proc near
	push	bp
	mov	bp, sp
	inc	_yuuka6_anim_frame
	mov	bx, _yuuka6_anim_frame
	dec	bx
	cmp	bx, 27h	; '''
	ja	short @@still_animating
	add	bx, bx
	jmp	cs:@@switch_table[bx]

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_LEFT
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_LEFT_FORWARD_PULL
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_0
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_3:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_1
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_4:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_2
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_5:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_3
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_6:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_4
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_7:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_5
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_8:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_6
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_9:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_7
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_10:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_8
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_11:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SPIN_BACK_9
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_12:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_CLOSED
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_CLOSED
	mov	al, 1
	pop	bp
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	pop	bp
	retn
; ---------------------------------------------------------------------------
	db 0
@@switch_table	dw offset @@cel_0
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_1
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_2
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_3
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_4
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_5
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_6
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_7
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_8
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_9
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_10
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_11
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@cel_12
	dw offset @@still_animating
	dw offset @@still_animating
	dw offset @@done
_yuuka6_anim_parasol_left_spin_back	endp


public _yuuka6_anim_vanish
_yuuka6_anim_vanish	proc near

@@frame		= word ptr -2

	enter	2, 0
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 6		; switch 6 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+0Ch] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_0
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_1
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_2
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_3:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_3
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_4:
	mov	_boss_sprite, 0
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_VANISHED
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
@@switch_table	dw	1, 8, 15, 22, 29, 36	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@cel_3
	dw offset @@cel_4
	dw offset @@done
_yuuka6_anim_vanish	endp


public _yuuka6_anim_appear
_yuuka6_anim_appear	proc near

@@frame		= word ptr -2

	enter	2, 0
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 6		; switch 6 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+0Ch] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_3
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_2
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_1
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_3:
	mov	_boss_sprite, PAT_YUUKA6_VANISH_0
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_4:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_OPEN
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_OPEN
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
	db 0
@@switch_table	dw	1, 8, 15, 22, 29, 36	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@cel_3
	dw offset @@cel_4
	dw offset @@done
_yuuka6_anim_appear	endp


public _yuuka6_anim_parasol_shield
_yuuka6_anim_parasol_shield	proc near

@@frame		= word ptr -2

	enter	2, 0
	inc	_yuuka6_anim_frame
	mov	ax, _yuuka6_anim_frame
	mov	[bp+@@frame], ax
	mov	cx, 4		; switch 4 cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+8] ; switch jump

@@cel_0:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_OPEN
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_1:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SHIELD_0
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@cel_2:
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_SHIELD_1
	jmp	short @@still_animating
; ---------------------------------------------------------------------------

@@done:
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_SHIELD
	mov	al, 1
	leave
	retn
; ---------------------------------------------------------------------------

@@still_animating:
	mov	al, 0
	leave
	retn
; ---------------------------------------------------------------------------
	db 0
@@switch_table	dw	1, 7, 13, 19	; value	table for switch statement
	dw offset @@cel_0	; jump table for switch	statement
	dw offset @@cel_1
	dw offset @@cel_2
	dw offset @@done
_yuuka6_anim_parasol_shield	endp
