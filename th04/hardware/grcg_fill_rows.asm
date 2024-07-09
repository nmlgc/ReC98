; Fills the given playfield rows between ES:0 (top row) and ES:DI (left byte
; in the bottom row) with the current GRCG tile.
; Assumes that the GRCG is set to TDW mode.

; void __usercall grcg_fill_playfield_rows(void far *vram_byte_at_bottom_left<es:di>);
public _grcg_fill_playfield_rows
_grcg_fill_playfield_rows	proc near
	mov	cx, PLAYFIELD_VRAM_W / 4
	rep stosd
	sub	di, ROW_SIZE + PLAYFIELD_VRAM_W
	jge	short _grcg_fill_playfield_rows
	retn
_grcg_fill_playfield_rows	endp
	nop
