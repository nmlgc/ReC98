extern const char near* SCOREDAT_FN_PTR; // ZUN bloat: Use the macro.

bool pascal near scoredat_load_and_decode(rank_t rank)
{
	if(!file_exist(SCOREDAT_FN_PTR)) {
		// scoredat_recreate() uses file_append(), which fails if the file
		// doesn't exist yet.
		file_create(SCOREDAT_FN_PTR);
		file_close();

		scoredat_recreate();
		return true;
	}
	file_ropen(SCOREDAT_FN_PTR);
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
