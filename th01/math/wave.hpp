inline pixel_t wave_x(pixel_t amp, int t) {
	return ((static_cast<long>(amp) * Sin8(t)) / 0x100);
}
