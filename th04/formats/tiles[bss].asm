; Each tile defines a 384×80 section of the background, which internally are
; further divided into 5 rows of 16 pixels each.
if GAME eq 5
public _tile_index_ptr
_tile_index_ptr	dw ?
else
public _tile_index
_tile_index    	dw ?
endif

public _tile_row, _tile_scrollspeed_ptr
_tile_row	db ?
         	db ?
_tile_scrollspeed_ptr	dw ?
