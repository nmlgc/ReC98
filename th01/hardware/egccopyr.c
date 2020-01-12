// Alternate version that sets the value first
#define OUTW2(port, val) __asm { \
	mov ax, val; \
	mov dx, port; \
	out dx, ax; \
}

void pascal egc_start_copy(void)
{
	egc_on();
	OUTW2(EGC_ACTIVEPLANEREG, 0xFFF0);
	OUTW2(EGC_READPLANEREG, 0x00FF);
	// EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD
	OUTW2(EGC_MODE_ROP_REG, 0x3100);
	OUTW2(EGC_MASKREG, 0xFFFF);
	OUTW2(EGC_ADDRRESSREG, 0);
	OUTW2(EGC_BITLENGTHREG, 0xF);
}

void egc_copy_rect_1_to_0(int x, int y, int w, int h)
{
	register int x_end = x;
	register int x_floor = x_end;
	int row;
	int col;
	int row_p;
	planar16_t bits;
	int p;

	x_end += w;
	x_floor &= 0xFFF0;
	row_p = VRAM_OFFSET(x_floor, y);
	egc_start_copy();
	for(row = 0; row < h; row++) {
		for(col = x_floor, p = row_p; col < x_end; p += 2, col += 16) {
			graph_accesspage_func(1); VRAM_SNAP(bits, B, p, 16);
			graph_accesspage_func(0); VRAM_PUT(B, p, bits, 16);
		}
		row_p += 640 / 8;
	}
	egc_off();
}
