	.386
	locals

include libs/master.lib/master.inc
include th03/arg_bx.inc
include th02/main/playfld.inc
include th04/math/motion.inc
include th04/hardware/input.inc
include th04/main/player/player.inc

VECTOR2_AT procdesc pascal far \
	ret:ptr Point, origin_x:word, origin_y:word, length:word, angle:byte

MAIN_01 group MAIN_0_TEXT, MAIN_01_TEXT
MAIN_0_TEXT	segment byte public 'CODE' use16
	TILES_INVALIDATE_AROUND procdesc pascal near \
		center:Point
MAIN_0_TEXT ends

extrn _tile_invalidate_box:Point
extrn _miss_time:byte
extrn _miss_explosion_angle:byte
extrn _miss_explosion_radius:word
extrn _drawpoint:Point
extrn _player_option_pos_prev:Point

extrn _player_pos:motion_t
extrn _playchar_speed_aligned:word
extrn _playchar_speed_diagonal:word

; ----------------------------------------------------------------------------

MAIN_01_TEXT	segment	word public 'CODE' use16
	assume cs:MAIN_01

; void pascal near player_invalidate(void);
public PLAYER_INVALIDATE
PLAYER_INVALIDATE	proc pascal near
	mov	_tile_invalidate_box.y, PLAYER_H
	cmp	_miss_time, 0
	jz	short @@alive
	push	di
	mov	_tile_invalidate_box.x, MISS_EXPLOSION_W
	mov	di, _miss_explosion_radius
	; Go back a frame
	add	di, -MISS_EXPLOSION_RADIUS_VELOCITY
	mov	al, _miss_explosion_angle
	add	al, -MISS_EXPLOSION_ANGLE_VELOCITY
	mov	ah, MISS_EXPLOSION_COUNT

@@loop:
	cmp	ah, MISS_EXPLOSION_COUNT / 2
	jnz	short @@invalidate
	shr	di, 1
	neg	al

@@invalidate:
	push	ax
	call	VECTOR2_AT pascal, offset _drawpoint, _player_pos.cur.x, _player_pos.cur.y, di, ax
	MISS_EXPLOSION_CLIP	 @@next
	call	TILES_INVALIDATE_AROUND pascal, large [_drawpoint]

@@next:
	pop	ax
	add	al, 256 / (MISS_EXPLOSION_COUNT / 2)
	dec	ah
	jnz	short @@loop
	pop	di
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@alive:
	mov	_tile_invalidate_box.x, PLAYER_W
	call	TILES_INVALIDATE_AROUND pascal, large [_player_pos.prev]
	mov	_tile_invalidate_box.x, PLAYER_OPTION_W + PLAYER_W + PLAYER_OPTION_W
	mov	_tile_invalidate_box.y, PLAYER_OPTION_H
	call	TILES_INVALIDATE_AROUND pascal, large [_player_option_pos_prev]

@@ret:
	retn
PLAYER_INVALIDATE	endp


	even


public @PLAYER_MOVE$QUI
@player_move$qui proc near
arg_bx	near, @input:word

@@diagonal_x equ ax
@@diagonal_y equ cx
@@aligned equ dx

	mov	bx, @input
	cmp	bl, INPUT_RIGHT or INPUT_DOWN
	ja	short @@invalid
	mov	@@diagonal_y, _playchar_speed_diagonal
	mov	@@diagonal_x, @@diagonal_y
	mov	@@aligned, _playchar_speed_aligned
	and	bh, low INPUT_MOVEMENT
	jz	short @@switch
	or	bl, bl
	jnz	short @@invalid
	shr	bx, 8
	cmp	bl, 8
	ja	short @@invalid
	add	bl, 11

@@switch:
	add	bx, bx
	jmp	word ptr cs:@@switch_table[bx]

@@up:
	neg	@@aligned

@@down:
	mov	_player_pos.velocity.y, @@aligned
	jmp	short @@moved
; ---------------------------------------------------------------------------

@@left:
	neg	@@aligned

@@right:
	mov	_player_pos.velocity.x, @@aligned
	jmp	short @@moved
; ---------------------------------------------------------------------------

@@up_right:
	neg	@@diagonal_y
	jmp	short @@down_right
; ---------------------------------------------------------------------------

@@up_left:
	neg	@@diagonal_y

@@down_left:
	neg	@@diagonal_x

@@down_right:
	mov	_player_pos.velocity.x, @@diagonal_x
	mov	_player_pos.velocity.y, @@diagonal_y
	jmp	short @@moved
; ---------------------------------------------------------------------------

@@standing_still:
	mov	al, MOVE_NOINPUT
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@invalid:
	xor	al, al
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@moved:
	mov	al, MOVE_VALID

@@ret:
	ret_bx

; ---------------------------------------------------------------------------
@@switch_table	label word
	dw @@standing_still
	dw @@up
	dw @@down
	dw @@invalid
	dw @@left
	dw @@up_left
	dw @@down_left
	dw @@invalid
	dw @@right
	dw @@up_right
	dw @@down_right
	dw @@invalid
	dw @@up_left
	dw @@up_right
	dw @@invalid
	dw @@down_left
	dw @@invalid
	dw @@invalid
	dw @@invalid
	dw @@down_right
@player_move$qui endp
MAIN_01_TEXT	ends

	end
