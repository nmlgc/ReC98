extern bb_tiles8_t __seg *bb_stage_seg;

void pascal near bb_stage_load(const char *fn)
{
#if GAME == 5
	bb_stage_seg = bb_load(fn);
#else
	file_ropen(fn);
	bb_stage_seg = HMem<bb_tiles8_t>::allocbyte(BB_SIZE);
	file_read(bb_stage_seg, BB_SIZE);
	file_close(fn);
#endif
}

#if GAME == 5
void pascal near bb_stage_free(void)
#else
void pascal far bb_stage_free(void)
#endif
{
	if(bb_stage_seg) {
		HMem<bb_tiles8_t>::free(bb_stage_seg);
		bb_stage_seg = 0;
	}
}
