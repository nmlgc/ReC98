public _scroll_line_on_plane, _tile_invalidate_box
_scroll_line_on_plane	dw 2 dup(?)
; Width and height, in screen pixels, of a box around the center passed to
; tiles_invalidate_around(). *Not* the radius.
_tile_invalidate_box	Point <?>
