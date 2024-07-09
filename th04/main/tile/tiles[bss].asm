TILES_MEMORY_X = 512 / TILE_W

public _map_seg
_map_seg	dw ?

public _halftiles_dirty, _halftiles_dirty_end
_halftiles_dirty	db (TILES_MEMORY_X * TILE_FLAGS_Y) dup(?)
_halftiles_dirty_end	label byte

public _tile_ring
_tile_ring	dw (TILES_MEMORY_X * TILES_Y) dup(?)

; .STD files reference 384×80 (25×5) sections of tiles.
if GAME eq 5
public _std_map_section_p
_std_map_section_p	dw ?
else
public _std_map_section_id
_std_map_section_id    	dw ?
endif

public _tile_row_in_section, _std_scroll_speed
_tile_row_in_section	db ?
         	db ?
_std_scroll_speed	dw ?
