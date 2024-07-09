/* ReC98
 * -----
 * TH01-specific extensions to planar.h
 */

// *Not* grcg_*, because they fully abstract away the GRCG's existence
#define vram_erase(offset, dots, bit_count) \
	grcg_setcolor_rmw(0); \
	grcg_put(offset, dots, bit_count); \
	grcg_off_func();

#define vram_erase_on_0(offset, dots, bit_count) \
	grcg_setcolor_rmw(0); \
	graph_accesspage_func(0); \
	grcg_put(offset, dots, bit_count); \
	grcg_off_func();
