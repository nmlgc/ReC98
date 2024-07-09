// Darkens the [w]×[h] area starting at [vram_offset], by writing an
// alternating dot pattern in the given [col].
#define darken(vram_offset, w, h, col) \
	vram_byte_amount_t x; \
	pixel_t y; \
	grcg_setcolor(GC_RMW, col); \
	dots32_t pattern = 0xAAAAAAAA; \
	\
	y = 0; \
	while(y < h) { \
		pattern = ((y & 1) == 0) ? 0xAAAAAAAA : 0x55555555; \
		\
		x = 0; \
		while(x < (w / BYTE_DOTS)) { \
			grcg_put(vram_offset, pattern, 32); \
			x += static_cast<vram_byte_amount_t>(sizeof(pattern)); \
			vram_offset += static_cast<vram_offset_t>(sizeof(pattern)); \
		} \
		y++; \
		vram_offset += (ROW_SIZE - (w / BYTE_DOTS)); \
	} \
	grcg_off();
