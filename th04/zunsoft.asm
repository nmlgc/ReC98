public ZUNSOFT_PYRO_NEW
zunsoft_pyro_new	proc pascal near
	local @@pyros_created:word, @@i:word
	arg @@origin:Point, @@n:word, @@patnum_base:byte

	push	si
	push	di
	mov	di, @@origin.y
	mov	@@pyros_created, 0
	mov	ax, 16
	imul	@@origin.x
	mov	@@origin.x, ax
	mov	ax, 16
	imul	di
	mov	di, ax
	mov	si, offset _zunsoft_pyros
	mov	@@i, 0
	jmp	short loc_B68D

loc_B63E:
	cmp	[si+zunsoft_pyro_t.alive], 0
	jnz	short loc_B687
	mov	[si+zunsoft_pyro_t.alive], 1
	mov	[si+zunsoft_pyro_t.frame], 0
	mov	[si+zunsoft_pyro_t.origin.x], di
	mov	ax, @@origin.x
	mov	[si+zunsoft_pyro_t.origin.y], ax
	mov	[si+zunsoft_pyro_t.distance], 0
	mov	[si+zunsoft_pyro_t.distance_prev], 0
	call	IRand
	mov	bx, 224
	cwd
	idiv	bx
	add	dx, 64
	mov	[si+zunsoft_pyro_t.speed], dx
	call	IRand
	mov	[si+zunsoft_pyro_t.angle], al
	mov	al, @@patnum_base
	mov	[si+zunsoft_pyro_t.patnum_base], al
	inc	@@pyros_created
	mov	ax, @@pyros_created
	cmp	ax, @@n
	jge	short loc_B694

loc_B687:
	inc	@@i
	add	si, size zunsoft_pyro_t

loc_B68D:
	cmp	@@i, ZUNSOFT_PYRO_COUNT
	jl	short loc_B63E

loc_B694:
	pop	di
	pop	si
	ret
zunsoft_pyro_new	endp


public ZUNSOFT_UPDATE_AND_RENDER
zunsoft_update_and_render	proc pascal near
	local @@patnum:word, @@draw_y:word, @@draw_x:word, @@anim_sprite:word

	push	si
	push	di
	mov	si, offset _zunsoft_pyros
	xor	di, di
	jmp	loc_B7B9

loc_B6A8:
	cmp	[si+zunsoft_pyro_t.alive], 1
	jnz	loc_B7B5
	inc	[si+zunsoft_pyro_t.frame]
	mov	al, [si+zunsoft_pyro_t.frame]
	mov	ah, 0
	mov	bx, 4
	cwd
	idiv	bx
	mov	@@anim_sprite, ax
	mov	al, [si+zunsoft_pyro_t.patnum_base]
	mov	ah, 0
	add	ax, @@anim_sprite
	mov	@@patnum, ax
	cmp	[si+zunsoft_pyro_t.frame], 40
	jb	short loc_B6DB
	mov	[si+zunsoft_pyro_t.alive], 0
	mov	[si+zunsoft_pyro_t.frame], 0
	jmp	loc_B7B5

loc_B6DB:
	cmp	[si+zunsoft_pyro_t.frame], 16
	jnb	short loc_B6FA
	mov	ax, [si+zunsoft_pyro_t.origin.x]
	mov	bx, 16
	cwd
	idiv	bx
	add	ax, -8
	push	ax
	mov	ax, [si+zunsoft_pyro_t.origin.y]
	cwd
	idiv	bx
	add	ax, -8
	jmp	loc_B7AC

loc_B6FA:
	cmp	[si+zunsoft_pyro_t.frame], 32
	jnb	short loc_B754
	cmp	[si+zunsoft_pyro_t.frame], 16
	jnz	short loc_B70D
	call	snd_se_play pascal, 15

loc_B70D:
	mov	ax, [si+zunsoft_pyro_t.distance]
	mov	[si+zunsoft_pyro_t.distance_prev], ax
	mov	ax, [si+zunsoft_pyro_t.speed]
	add	[si+zunsoft_pyro_t.distance], ax
	push	[si+zunsoft_pyro_t.origin.x]
	push	[si+zunsoft_pyro_t.distance]
	mov	al, [si+zunsoft_pyro_t.angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_CosTable8[bx]
	call	vector1_at
	add	ax, -128
	mov	@@draw_x, ax
	push	[si+zunsoft_pyro_t.origin.y]
	push	[si+zunsoft_pyro_t.distance]
	mov	al, [si+zunsoft_pyro_t.angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	call	vector1_at
	add	ax, -128
	jmp	short loc_B799

loc_B754:
	mov	ax, [si+zunsoft_pyro_t.distance]
	mov	[si+zunsoft_pyro_t.distance_prev], ax
	mov	ax, [si+zunsoft_pyro_t.speed]
	add	[si+zunsoft_pyro_t.distance], ax
	push	[si+zunsoft_pyro_t.origin.x]
	push	[si+zunsoft_pyro_t.distance]
	mov	al, [si+zunsoft_pyro_t.angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_CosTable8[bx]
	call	vector1_at
	add	ax, -256
	mov	@@draw_x, ax
	push	[si+zunsoft_pyro_t.origin.y]
	push	[si+zunsoft_pyro_t.distance]
	mov	al, [si+zunsoft_pyro_t.angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	call	vector1_at
	add	ax, -256

loc_B799:
	mov	@@draw_y, ax
	mov	ax, @@draw_x
	mov	bx, 16
	cwd
	idiv	bx
	push	ax
	mov	ax, @@draw_y
	cwd
	idiv	bx

loc_B7AC:
	push	ax
	push	@@patnum
	call	super_put_rect

loc_B7B5:
	inc	di
	add	si, size zunsoft_pyro_t

loc_B7B9:
	cmp	di, ZUNSOFT_PYRO_COUNT
	jl	loc_B6A8
	pop	di
	pop	si
	ret
zunsoft_update_and_render	endp


public ZUNSOFT_PALETTE_UPDATE_AND_SHOW
zunsoft_palette_update_and_show	proc near
	arg @@tone:word

	push	bp
	mov	bp, sp
	push	si
	push	di
	xor	si, si
	jmp	short loc_B7F6

loc_B7CE:
	xor	di, di
	jmp	short loc_B7F0

loc_B7D2:
	mov	bx, si
	imul	bx, size rgb_t
	mov	al, _zunsoft_palette[bx+di]
	mov	ah, 0
	imul	@@tone
	mov	bx, 100
	cwd
	idiv	bx
	mov	bx, si
	imul	bx, size rgb_t
	mov	Palettes[bx+di], al
	inc	di

loc_B7F0:
	cmp	di, size rgb_t
	jl	short loc_B7D2
	inc	si

loc_B7F6:
	cmp	si, 15
	jl	short loc_B7CE
	call	palette_show
	pop	di
	pop	si
	pop	bp
	retn	2
zunsoft_palette_update_and_show	endp
