bool pascal near scoredat_load_and_decode(rank_t rank)
{
	if(!file_exist(SCOREDAT_FN)) {
		// scoredat_recreate() uses file_append(), which fails if the file
		// doesn't exist yet.
		file_create(SCOREDAT_FN);
		file_close();

		scoredat_recreate();
		return true;
	}
	file_ropen(SCOREDAT_FN);
	file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
	file_read(&hi, sizeof(scoredat_section_t));
	file_close();
	scoredat_decode();
	if(scoredat_sum_invalid()) {
		scoredat_recreate();
		return true;
	}
	return false;
}
