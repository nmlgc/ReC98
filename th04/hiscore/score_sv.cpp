// Leaves [hi] in encoded state.
void pascal near hiscore_scoredat_save(playchar_t playchar, rank_t rank)
{
	scoredat_encode(hi);

	file_append(SCOREDAT_FN);

	// ZUN bloat: The TH05 version is correct for both games and all binaries.
#if (GAME == 5)
	file_seek(
		(((playchar * RANK_COUNT) + rank) * sizeof(scoredat_section_t)),
		SEEK_SET
	);
#else
	file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
	if(playchar != PLAYCHAR_REIMU) {
		file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
	}
#endif
	file_write(&hi, sizeof(scoredat_section_t));
	file_close();
}
