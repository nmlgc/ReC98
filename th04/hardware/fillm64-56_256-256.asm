; Fills the playfield around the 256×256 pixels starting at (64, 56) with the
; current GRCG tile.
; Assumes that the GRCG is set to TDW mode.

; void pascal playfield_fillm_64_56_256_256();
public PLAYFIELD_FILLM_64_56_256_256
playfield_fillm_64_56_256_256	proc near
		push	di
		mov	ax, GRAM_400 + (PLAYFIELD_Y * ROW_SIZE) shr 4
		mov	es, ax
		assume es:nothing
		mov	di, (55 * ROW_SIZE) + PLAYFIELD_VRAM_X
		nop

@@rows_next:
		mov	cx, PLAYFIELD_VRAM_W / 4

@@rows_top_and_bottom:
		mov	es:[di+(312 * ROW_SIZE)], eax
		stosd
		loop	@@rows_top_and_bottom
		sub	di, ROW_SIZE + PLAYFIELD_VRAM_W
		jge	short @@rows_next
		mov	ax, GRAM_400 + ((56 + PLAYFIELD_Y) * ROW_SIZE) shr 4
		mov	es, ax
		assume es:nothing
		mov	di, (255 * ROW_SIZE) + PLAYFIELD_VRAM_X
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
playfield_fillm_64_56_256_256	endp
	even
