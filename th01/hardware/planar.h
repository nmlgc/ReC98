/* ReC98
 * -----
 * TH01-specific extensions to planar.h
 */

// *Not* grcg_*, because they fully abstract away the GRCG's existence
#define vram_erase(offset, dots, bit_count) \
	grcg_setcolor_rmw(0); \
	grcg_put(offset, dots, bit_count); \
	grcg_off();

#define vram_erase_on_0(offset, dots, bit_count) \
	grcg_setcolor_rmw(0); \
	page_access(0); \
	grcg_put(offset, dots, bit_count); \
	grcg_off();
