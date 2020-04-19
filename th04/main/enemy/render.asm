public ENEMIES_RENDER
enemies_render	proc near

@@patnum	= byte ptr -5
@@top   	= word ptr -4
@@i     	= word ptr -2

	enter	6, 0
	push	si
	push	di
	mov	si, offset _enemies
	mov	[bp+@@i], 0
	jmp	@@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	byte ptr [si+enemy_t.flag], EF_ALIVE
	jz	short @@outside_playfield?
	cmp	byte ptr [si+enemy_t.flag], EF_KILL_ANIM
	jb	@@next

@@outside_playfield?:
	cmp	[si+enemy_t.pos.prev.y], (-(ENEMY_H / 2) shl 4)
	jle	@@next
	cmp	[si+enemy_t.pos.prev.y], ((PLAYFIELD_H + (ENEMY_H / 2)) shl 4)
	jge	@@next
	mov	al, [si+enemy_t.E_patnum_base]
	mov	[bp+@@patnum], al
	cmp	[si+enemy_t.E_anim_cels], 1
	jbe	short @@put
	mov	al, [si+enemy_t.age]
	mov	ah, 0
	mov	dl, [si+enemy_t.E_anim_frames_per_cel]
	mov	dh, 0
	push	dx
	cwd
	pop	bx
	idiv	bx
	or	dx, dx
	jnz	short @@still_same_cel
	inc	[si+enemy_t.E_anim_cur_cel]
	mov	al, [si+enemy_t.E_anim_cur_cel]
	cmp	al, [si+enemy_t.E_anim_cels]
	jb	short @@still_same_cel
	mov	[si+enemy_t.E_anim_cur_cel], 0

@@still_same_cel:
	mov	al, [si+enemy_t.E_anim_cur_cel]
	add	[bp+@@patnum], al

@@put:
	mov	ax, [si+enemy_t.cur.pos.x]
	sar	ax, 4
	add	ax, (PLAYFIELD_X - (ENEMY_W / 2))
	mov	di, ax
	call	scroll_subpixel_y_to_vram_seg1 pascal, [si+enemy_t.pos.cur.y]
	mov	[bp+@@top], ax
	or	di, di
	jle	short @@next
	cmp	di, PLAYFIELD_RIGHT
	jge	short @@next
	cmp	[si+enemy_t.pos.cur.y], (-(ENEMY_H / 2) shl 4)
	jle	short @@next
	cmp	[si+enemy_t.pos.cur.y], ((PLAYFIELD_H + (ENEMY_H / 2)) shl 4)
	jge	short @@next
	cmp	[si+enemy_t.E_damaged_this_frame], 0
	jnz	short @@damaged
	push	di
	push	ax
	mov	al, [bp+@@patnum]
	mov	ah, 0
	push	ax
	call	super_roll_put
	jmp	short @@next
; ---------------------------------------------------------------------------

@@damaged:
	push	di
	push	[bp+@@top]
	mov	al, [bp+@@patnum]
	mov	ah, 0
	push	ax
	pushd	PLANE_PUT or GC_BRGI
	call	super_roll_put_1plane
	mov	[si+enemy_t.E_damaged_this_frame], 0

@@next:
	inc	[bp+@@i]
	add	si, size enemy_t

@@more?:
	cmp	[bp+@@i], ENEMY_COUNT
	jl	@@loop
	pop	di
	pop	si
	leave
	retn
enemies_render	endp
