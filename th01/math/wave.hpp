inline int wave_x(int amp, int t) {
	return ((static_cast<long>(amp) * Sin8(t)) / 0x100);
}
