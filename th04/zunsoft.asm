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
	call	@polar$qiii
	add	ax, -128
	mov	@@draw_x, ax
	push	[si+zunsoft_pyro_t.origin.y]
	push	[si+zunsoft_pyro_t.distance]
	mov	al, [si+zunsoft_pyro_t.angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	call	@polar$qiii
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
	call	@polar$qiii
	add	ax, -256
	mov	@@draw_x, ax
	push	[si+zunsoft_pyro_t.origin.y]
	push	[si+zunsoft_pyro_t.distance]
	mov	al, [si+zunsoft_pyro_t.angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	call	@polar$qiii
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


public _zunsoft_animate
_zunsoft_animate proc near

@@frame		= word ptr -8
@@i		= word ptr -6
@@fade_out		= byte ptr -4
@@fade_in		= byte ptr -3
@@skip		= byte ptr -2
@@page		= byte ptr -1

	enter	8, 0
	push	si
	push	di
	mov	[bp+@@skip], 0
	mov	[bp+@@fade_in], 0
	mov	[bp+@@fade_out], 100
	mov	PaletteTone, 0
	call	palette_show
	graph_accesspage 1
	call	pi_load pascal, 0, ds, offset aZun00_pi
	call	pi_palette_apply pascal, 0
	call	pi_put_8 pascal, large 0, 0
if GAME eq 5
	call	pi_free pascal, 0
else
	freePISlotLarge	0
endif
	push	0
	call	graph_copy_page
	call	_bgimage_snap
	graph_accesspage 1
	call	graph_clear
	graph_accesspage 0
	call	graph_clear
	xor	si, si
	jmp	short @@more_colors?
; ---------------------------------------------------------------------------

@@next_color:
	mov	bx, si
	imul	bx, size rgb_t
	mov	al, Palettes[bx].r
	mov	bx, si
	imul	bx, size rgb_t
	mov	_zunsoft_palette[bx].r, al
	mov	bx, si
	imul	bx, size rgb_t
	mov	al, Palettes[bx].g
	mov	bx, si
	imul	bx, size rgb_t
	mov	_zunsoft_palette[bx].g, al
	mov	bx, si
	imul	bx, size rgb_t
	mov	al, Palettes[bx].b
	mov	bx, si
	imul	bx, size rgb_t
	mov	_zunsoft_palette[bx].b, al
	mov	bx, si
	imul	bx, size rgb_t
	mov	Palettes[bx].r, 0
	mov	bx, si
	imul	bx, size rgb_t
	mov	Palettes[bx].g, 0
	mov	bx, si
	imul	bx, size rgb_t
	mov	Palettes[bx].b, 0
	inc	si

@@more_colors?:
	cmp	si, 15
	jl	short @@next_color
	call	snd_load pascal, ds, offset aLogo, SND_LOAD_SONG
	kajacall	KAJA_SONG_PLAY
	mov	[bp+@@i], offset _zunsoft_pyros
	xor	si, si
	jmp	short @@more_pyros?
; ---------------------------------------------------------------------------

@@next_pyro:
	mov	bx, [bp+@@i]
	mov	word ptr [bx+zunsoft_pyro_t.alive], 0
	inc	si
	add	[bp+@@i], size zunsoft_pyro_t

@@more_pyros?:
	cmp	si, ZUNSOFT_PYRO_COUNT
	jl	short @@next_pyro
	call	snd_delay_until_measure pascal, (2 shl 16) or 0
	mov	PaletteTone, 100
	call	palette_show
	call	super_entry_bfnt pascal, ds, offset aZun02_bft
	call	super_entry_bfnt pascal, ds, offset aZun04_bft
	call	super_entry_bfnt pascal, ds, offset aZun01_bft
	call	super_entry_bfnt pascal, ds, offset aZun03_bft
	mov	[bp+@@page], 0
	graph_accesspage 1
	graph_showpage 0
if GAME eq 4
	call	_input_reset_sense
endif
	xor	di, di
	jmp	@@more_frames?
; ---------------------------------------------------------------------------

@@next_frame:
if GAME eq 5
	call	_input_reset_sense_held
else
	call	_input_sense
endif
	cmp	_key_det, INPUT_NONE
	jz	short @@not_skipping
	mov	[bp+@@skip], 1

@@not_skipping:
	mov	[bp+@@frame], di
	mov	cx, 12
	mov	bx, offset word_BEA5

@@frame_switch_loop:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@frame]
	jz	short @@frame_found
	add	bx, 2
	loop	@@frame_switch_loop
	jmp	short @@no_new_pyro_this_frame	; default
; ---------------------------------------------------------------------------

@@frame_found:
	jmp	word ptr cs:[bx+18h] ; switch jump

frame_0:	; case 0
	push	(180 shl 16) or 180
	jmp	short @@new_pyro_n_20_patnum_0
frame_16:	; case 16
	push	(460 shl 16) or 220
	jmp	short @@new_pyro_n_20_patnum_10
frame_24:	; case 24
	push	(220 shl 16) or 160
	jmp	short @@new_pyro_n_20_patnum_0
frame_32:	; case 32
	push	(380 shl 16) or 240
	jmp	short @@new_pyro_n_20_patnum_10
frame_44:	; case 44
	push	(340 shl 16) or 200
	jmp	short @@new_pyro_n_20_patnum_10
frame_48:	; case 48
	push	(280 shl 16) or 170
	jmp	short @@new_pyro_n_20_patnum_0
frame_52:	; case 52
	push	(380 shl 16) or 260
	jmp	short @@new_pyro_n_20_patnum_10
frame_40_56:	; case 40, 56
	push	(200 shl 16) or 190

@@new_pyro_n_20_patnum_0:	; case 0, 24, 40, 48, 56
	push	20
	jmp	short @@new_pyro_patnum_0

frame_60:	; case 60
	push	(440 shl 16) or 210

@@new_pyro_n_20_patnum_10:	; case 16, 32, 44, 52, 60
	push	20
	jmp	short @@new_pyro_patnum_10

frame_64:	; case 64
	push	(320 shl 16) or 200
	push	64

@@new_pyro_patnum_0:	; case 0, 24, 40, 48, 56, 64
	push	0
	jmp	short @@new_pyro_call
; ---------------------------------------------------------------------------

frame_68:	; case 68
	push	(320 shl 16) or 200
	push	64

@@new_pyro_patnum_10:	; case 16, 32, 44, 52, 60, 68
	push	10

@@new_pyro_call:
	call	zunsoft_pyro_new

@@no_new_pyro_this_frame:
	call	_bgimage_put	; default
	call	zunsoft_update_and_render
if GAME eq 4
	call	_input_reset_sense
endif

@@2_frame_delay:
	cmp	vsync_Count1, 2
	jb	short @@2_frame_delay
	mov	vsync_Count1, 0
	graph_accesspage [bp+@@page]
	mov	al, 1
	sub	al, [bp+@@page]
	mov	[bp+@@page], al
	graph_showpage al
	cmp	[bp+@@skip], 0
	jnz	short @@skipping
	cmp	di, 16
	jl	short @@apply_fade_in
	cmp	[bp+@@fade_in], 100
	jnb	short @@apply_fade_in
	mov	al, [bp+@@fade_in]
	add	al, 2
	mov	[bp+@@fade_in], al

@@apply_fade_in:
	mov	al, [bp+@@fade_in]
	mov	ah, 0
	push	ax
	call	zunsoft_palette_update_and_show
	jmp	short @@end_of_frame
; ---------------------------------------------------------------------------

@@skipping:
	cmp	[bp+@@fade_out], 0
	jbe	short @@ret
	mov	al, [bp+@@fade_out]
	add	al, -2
	mov	[bp+@@fade_out], al
	mov	al, [bp+@@fade_out]
	mov	ah, 0
	mov	PaletteTone, ax
	call	palette_show

@@end_of_frame:
	call	_snd_se_update
	inc	di

@@more_frames?:
	cmp	di, 170
	jl	@@next_frame
	call	palette_black_out pascal, 1

@@ret:
	call	super_free
	call	_bgimage_free
	pop	di
	pop	si
	leave
	retn
_zunsoft_animate endp

; ---------------------------------------------------------------------------
if GAME eq 4
		db 0
endif
word_BEA5	dw	0, 16, 24, 32
			dw 40, 44, 48, 52 ; value table for switch	statement
			dw 56, 60, 64, 68
		dw offset frame_0	; jump table for switch	statement
		dw offset frame_16
		dw offset frame_24
		dw offset frame_32
		dw offset frame_40_56
		dw offset frame_44
		dw offset frame_48
		dw offset frame_52
		dw offset frame_40_56
		dw offset frame_60
		dw offset frame_64
		dw offset frame_68
