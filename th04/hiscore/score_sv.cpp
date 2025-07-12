// Leaves [hi] in encoded state.
void near hiscore_scoredat_save(void)
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
#if (BINARY == 'M')
	if(resident->playchar_ascii == ('0' + PLAYCHAR_MARISA)) {
		file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
	}
#else
	if(playchar != PLAYCHAR_REIMU) {
		file_seek((RANK_COUNT * sizeof(scoredat_section_t)), SEEK_CUR);
	}
#endif
#endif
	file_write(&hi, sizeof(scoredat_section_t));

#if (BINARY == 'E')
	// Re-encode the entire score file with newly randomized encraption keys.
	// ZUN bloat: Could have been its own function, and not thrashed [hi].
	for(int i = 0; i < ((RANK_COUNT * PLAYCHAR_COUNT)); i++) {
		file_seek((i * sizeof(scoredat_section_t)), SEEK_SET);
		file_read(&hi, sizeof(scoredat_section_t));
		scoredat_decode(hi);
		scoredat_encode(hi);
		file_seek((i * sizeof(scoredat_section_t)), SEEK_SET);
		file_write(&hi, sizeof(scoredat_section_t));
	}
#endif
	file_close();
}
