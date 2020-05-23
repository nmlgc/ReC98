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
