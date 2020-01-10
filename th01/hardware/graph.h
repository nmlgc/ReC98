/// Pages
/// -----
// Also updates [page_back].
void graph_showpage_func(page_t page);
void graph_accesspage_func(int page);
/// -----

/// GRCG
/// ----
void grcg_setcolor_rmw(int col);
void grcg_setcolor_tdw(int col);
void grcg_off_func(void);
#undef grcg_off
#define grcg_off grcg_off_func
/// ----

/// Blitting
/// --------
// Copies the given rectangle from
//     (⌊left/8⌋*8, top)
// to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// on the current back page to the same position on the current front page.
void graph_copy_byterect_back_to_front(
	int left, int top, int right, int bottom
);

// Moves the given source rectangle from
//     (⌊left/8⌋*8, top)
// to
//     (⌊left/8⌋*8 + ⌊(right-left)/8⌋*8, bottom)
// on the [src] page to the given position
// in the [dst] page. Already assumes [src] to be the currently accessed page.
void graph_move_byterect_interpage(
	int src_left, int src_top, int src_right, int src_bottom,
	int dst_left, int dst_top,
	page_t src, page_t dst
);
/// --------
