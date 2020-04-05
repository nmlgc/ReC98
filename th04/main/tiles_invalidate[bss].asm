public _SCROLL_LINE_ON_PLANE, _TILE_INVALIDATE_BOX
_scroll_line_on_plane	dw 2 dup(?)
; Width and height, in screen pixels, of a box around the center passed to
; tiles_invalidate_around(). *Not* the radius.
_tile_invalidate_box	Point <?>
