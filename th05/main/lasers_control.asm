; Adds a new shoot-out laser based on the [laser_template].

; void near lasers_add_shoutout(void);
lasers_add_shoutout	proc near
@@speed		= word ptr -2

	push	bp
	mov	bp, sp
	sub	sp, 2
	push	si
	push	di
	mov	al, byte ptr _laser_template.shootout_speed
	call	@playperf_speedtune
	mov	ah, 0
	mov	[bp+@@speed], ax
	mov	si, offset _lasers
	xor	di, di
	jmp	short @@more?

@@loop:
	cmp	[si+laser_t.mode], LM_NONE
	jnz	short @@next
	mov	[si+laser_t.mode], LM_SHOOTOUT
	mov	[si+laser_t.coords.starts_at_distance], (16 shl 4)
	mov	[si+laser_t.coords.ends_at_distance], (16 shl 4)
	mov	[si+laser_t.LASER_age], 0
	mov	ax, _laser_template.moveout_at_age
	mov	[si+laser_t.moveout_at_age], ax
	mov	al, _laser_template.LASER_color
	mov	[si+laser_t.LASER_color], al
	mov	ax, [bp+@@speed]
	mov	[si+laser_t.shootout_speed], ax
	mov	[si+laser_t.grow_to_width], 6
	mov	[si+laser_t.coords.LASER_width], 6
	mov	al, _laser_template.coords.angle
	mov	[si+laser_t.coords.angle], al
	lea	ax, [si+laser_t.coords]
	push	ax
	push	_laser_template.coords.origin.x
	push	_laser_template.coords.origin.y
	push	128
	mov	al, _laser_template.coords.angle
	mov	ah, 0
	push	ax
	call	vector2_at
	call	snd_se_play pascal, 5
	jmp	short @@ret

@@next:
	inc	di
	add	si, size laser_t

@@more?:
	cmp	di, LASER_COUNT
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	leave
	ret
lasers_add_shoutout	endp


; Creates a new fixed laser based on the [laser_template] in the given [slot]
; if that one is currently empty.

; void pascal near lasers_new_fixed_in_slot(unsigned int slot);
lasers_new_fixed_in_slot	proc near
@@slot		= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	ax, [bp+@@slot]
	imul	ax, size laser_t
	add	ax, offset _lasers
	mov	si, ax
	cmp	[si+laser_t.mode], LM_NONE
	jnz	short @@ret
	mov	[si+laser_t.mode], LM_FIXED_WAIT_TO_GROW
	mov	eax, _laser_template.coords.origin
	mov	dword ptr [si+laser_t.coords.origin], eax
	mov	[si+laser_t.coords.starts_at_distance], (16 shl 4)
	mov	[si+laser_t.coords.ends_at_distance], (550 shl 4)
	mov	[si+laser_t.LASER_age], 0
	mov	ax, _laser_template.grow_at_age
	mov	[si+laser_t.grow_at_age], ax
	mov	ax, _laser_template.shrink_at_age
	mov	[si+laser_t.shrink_at_age], ax
	mov	al, _laser_template.LASER_color
	mov	[si+laser_t.LASER_color], al
	mov	al, _laser_template.coords.LASER_width
	mov	[si+laser_t.grow_to_width], al
	mov	[si+laser_t.coords.LASER_width], 1
	mov	al, _laser_template.coords.angle
	mov	[si+laser_t.coords.angle], al
	call	snd_se_play pascal, 5

@@ret:
	pop	si
	pop	bp
	ret	2
lasers_new_fixed_in_slot	endp


; Creates a new fixed, manually controlled laser based on the [laser_template]
; in the given [slot] if that one is currently empty.

; void pascal near lasers_new_fixed_and_manual_in_slot(unsigned int slot);
lasers_new_fixed_and_manual_in_slot	proc near
@@slot		= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	ax, [bp+@@slot]
	imul	ax, size laser_t
	add	ax, offset _lasers
	mov	si, ax
	cmp	[si+laser_t.mode], LM_NONE
	jnz	short @@ret
	mov	[si+laser_t.mode], LM_FIXED_WAIT_TO_GROW
	mov	eax, _laser_template.coords.origin
	mov	dword ptr [si+laser_t.coords.origin], eax
	mov	[si+laser_t.coords.starts_at_distance], (16 shl 4)
	mov	[si+laser_t.coords.ends_at_distance], (550 shl 4)
	mov	[si+laser_t.LASER_age], 0
	mov	[si+laser_t.grow_at_age], -1
	mov	[si+laser_t.shrink_at_age], -1
	mov	al, _laser_template.LASER_color
	mov	[si+laser_t.LASER_color], al
	mov	[si+laser_t.coords.LASER_width], 1
	mov	al, _laser_template.coords.LASER_width
	mov	[si+laser_t.grow_to_width], al
	mov	al, _laser_template.coords.angle
	mov	[si+laser_t.coords.angle], al
	call	snd_se_play pascal, 5

@@ret:
	pop	si
	pop	bp
	ret	2
lasers_new_fixed_and_manual_in_slot	endp


; Starts the growing phase of the manually controlled fixed laser at [slot].

; void pascal near lasers_grow_manual_in_slot(unsigned int slot);
lasers_grow_manual_in_slot	proc near
@@slot		= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@slot]
	mov	bx, si
	imul	bx, size laser_t
	cmp	_lasers[bx].mode, LM_FIXED_WAIT_TO_GROW
	jnz	short @@ret
	mov	bx, si
	imul	bx, size laser_t
	mov	_lasers[bx].mode, LM_FIXED_GROW
	call	snd_se_play pascal, 6

@@ret:
	pop	si
	pop	bp
	ret	2
lasers_grow_manual_in_slot	endp


; Transitions the laser at [slot] to a stopping phase appropriate for its
; current one.

; void pascal lasers_stop_in_slot(unsigned int slot);
lasers_stop_in_slot	proc near
@@slot		= word ptr  4

	push	bp
	mov	bp, sp
	mov	ax, [bp+@@slot]
	mov	bx, ax
	imul	bx, size laser_t
	cmp	_lasers[bx].mode, LM_FIXED_ACTIVE
	jnz	short @@shootout?
	mov	bx, ax
	imul	bx, size laser_t
	mov	_lasers[bx].mode, LM_FIXED_SHRINK
	pop	bp
	ret	2

@@shootout?:
	mov	bx, ax
	imul	bx, size laser_t
	cmp	_lasers[bx].mode, LM_SHOOTOUT
	jnz	short @@fixed_shrink?
	mov	bx, ax
	imul	bx, size laser_t
	mov	_lasers[bx].mode, LM_DECAY
	pop	bp
	ret	2

@@fixed_shrink?:
	mov	bx, ax
	imul	bx, size laser_t
	cmp	_lasers[bx].mode, LM_FIXED_SHRINK
	jz	short @@ret
	mov	bx, ax
	imul	bx, size laser_t
	cmp	_lasers[bx].mode, LM_DECAY
	jz	short @@ret
	mov	bx, ax
	imul	bx, size laser_t
	mov	_lasers[bx].mode, LM_NONE

@@ret:
	pop	bp
	ret	2
lasers_stop_in_slot	endp
