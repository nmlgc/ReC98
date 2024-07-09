; Fills the playfield around the 256×256 pixels starting at (64, 56) with the
; current GRCG tile.
; Assumes that the GRCG is set to TDW mode.

public @REIMU_MARISA_BACKDROP_COLORFILL$QV
public @MAI_YUKI_BACKDROP_COLORFILL$QV
label @mai_yuki_backdrop_colorfill$qv near
@reimu_marisa_backdrop_colorfill$qv proc near
		push	di
		mov	ax, GRAM_400 + (PLAYFIELD_TOP * ROW_SIZE) shr 4
		mov	es, ax
		assume es:nothing
		mov	di, (55 * ROW_SIZE) + PLAYFIELD_VRAM_LEFT
		nop

@@rows_next:
		mov	cx, PLAYFIELD_VRAM_W / 4

@@rows_top_and_bottom:
		mov	es:[di+(312 * ROW_SIZE)], eax
		stosd
		loop	@@rows_top_and_bottom
		sub	di, ROW_SIZE + PLAYFIELD_VRAM_W
		jge	short @@rows_next
		mov	ax, GRAM_400 + ((56 + PLAYFIELD_TOP) * ROW_SIZE) shr 4
		mov	es, ax
		assume es:nothing
		mov	di, (255 * ROW_SIZE) + PLAYFIELD_VRAM_LEFT
		nop

@@cols:
		mov	es:[di+(320 / 8)], eax
		stosd
		mov	es:[di+(320 / 8)], eax
		stosd
		sub	di, ROW_SIZE + 8
		jge	short @@cols
		pop	di
		retn
@reimu_marisa_backdrop_colorfill$qv endp
	even
