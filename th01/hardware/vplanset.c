void pascal vram_planes_set(void)
{
	VRAM_PLANE_B = MK_FP(0xA800, 0);
	VRAM_PLANE_R = MK_FP(0xB000, 0);
	VRAM_PLANE_G = MK_FP(0xB800, 0);
	VRAM_PLANE_E = MK_FP(0xE000, 0);
}
