PLAYFIELD_LEFT = 32
PLAYFIELD_TOP = 16
PLAYFIELD_W = 384
PLAYFIELD_H = 368

PLAYFIELD_RIGHT = PLAYFIELD_LEFT + PLAYFIELD_W
PLAYFIELD_BOTTOM = PLAYFIELD_TOP + PLAYFIELD_H

PLAYFIELD_VRAM_LEFT = PLAYFIELD_LEFT / 8
PLAYFIELD_VRAM_W = PLAYFIELD_W / 8
PLAYFIELD_VRAM_RIGHT = PLAYFIELD_RIGHT / 8

PLAYFIELD_TRAM_LEFT = PLAYFIELD_LEFT / 8
PLAYFIELD_TRAM_TOP = PLAYFIELD_TOP / 16
PLAYFIELD_TRAM_W = PLAYFIELD_W / 8
PLAYFIELD_TRAM_RIGHT = PLAYFIELD_RIGHT / 8
PLAYFIELD_TRAM_BOTTOM = PLAYFIELD_BOTTOM / 16

if GAME eq 5
	playfield_tram_x_loop	macro @@atrb:req
		call	text_putsa pascal, PLAYFIELD_TRAM_LEFT, si, _PLAYFIELD_BLANK_ROW, @@atrb
	endm
else
	playfield_tram_x_loop	macro @@atrb:req
	local @@x_loop, @@x_more?
		mov	di, PLAYFIELD_TRAM_LEFT
		jmp	short @@x_more?
	; ---------------------------------------------------------------------------

	@@x_loop:
		call	text_putca pascal, di, si, (' ' shl 16) + @@atrb
		inc	di

	@@x_more?:
		cmp	di, PLAYFIELD_TRAM_RIGHT
		jl	short @@x_loop
	endm
endif

playfield_tram_loop	macro @@atrb:req
	mov	si, PLAYFIELD_TRAM_TOP
	jmp	short @@y_more?
; ---------------------------------------------------------------------------

@@y_loop:
	playfield_tram_x_loop	<@@atrb>
	inc	si

@@y_more?:
	cmp	si, PLAYFIELD_TRAM_BOTTOM
	jl	short @@y_loop
endm

playfield_tram_loop_func	macro @@funcname:req, @@dist:req, @@atrb:req
	public @@funcname
	@@funcname	proc @@dist
		push	bp
		mov	bp, sp
		push	si
		if GAME ne 5
			push	di
			playfield_tram_loop	<@@atrb>
			pop	di
		else
			playfield_tram_loop	<@@atrb>
		endif
		pop	si
		pop	bp
		ret
	@@funcname	endp
endm

TILE_W = 16
TILE_H = 16
TILE_VRAM_W = (TILE_W / 8)
TILES_Y = 1 + (PLAYFIELD_H / TILE_H) + 1
TILES_X = (PLAYFIELD_W / TILE_W)

TILE_FLAG_H = (TILE_H / 2)
TILE_FLAGS_Y = TILES_Y * (TILE_H / TILE_FLAG_H)
