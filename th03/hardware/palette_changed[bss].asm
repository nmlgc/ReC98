; Must be set to 1 if the hardware palette should be updated at the end of a
; regular, non-menu game frame. Otherwise, palette or tone changes during a
; frame won't actually be visible.
public _palette_changed
_palette_changed	db ?
