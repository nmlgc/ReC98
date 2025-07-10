#if (BINARY == 'L')
#define recreated
#define loaded
void pascal near scoredat_load_and_decode(rank_t rank)
#else
#define recreated true
#define loaded false
bool16 pascal near scoredat_load_and_decode(rank_t rank)
#endif
{
	if(!file_exist(SCOREDAT_FN)) {
		// Unnecessary, since scoredat_recreate() would also create the file?
		file_create(SCOREDAT_FN);
		file_close();

		scoredat_recreate();
		return recreated;
	}
	file_ropen(SCOREDAT_FN);
	file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
	file_read(&hi, sizeof(scoredat_section_t));
	file_close();
	scoredat_decode();
	if(scoredat_sum_invalid()) {
		scoredat_recreate();
		return recreated;
	}
	return loaded;

	#undef recreated
	#undef loaded
}
