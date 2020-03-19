void pascal vram_planes_set(void)
{
	VRAM_PLANE_B = (dots8_t *)MK_FP(0xA800, 0);
	VRAM_PLANE_R = (dots8_t *)MK_FP(0xB000, 0);
	VRAM_PLANE_G = (dots8_t *)MK_FP(0xB800, 0);
	VRAM_PLANE_E = (dots8_t *)MK_FP(0xE000, 0);
}
