void pascal near bb_boss_load(const char far *fn)
{
	#if (GAME == 5)
		bb_boss_seg = bb_load(fn);
	#else
		file_ropen(fn);
		bb_boss_seg = HMem<bb_tiles8_t>::allocbyte(BB_SIZE);
		file_read(bb_boss_seg, BB_SIZE);
		file_close();
	#endif
}

#if (GAME == 5)
	void near bb_boss_free(void)
#else
	void far bb_boss_free(void)
#endif
{
	if(bb_boss_seg) {
		HMem<bb_tiles8_t>::free(bb_boss_seg);
		bb_boss_seg = 0;
	}
}
