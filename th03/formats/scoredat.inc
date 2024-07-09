SCOREDAT_PLACES = 10
SCOREDAT_NAME_LEN = 8

SCOREDAT_NOT_CLEARED = 18
SCOREDAT_CLEARED = 99

scoredat_t struc
	SD_name	db (SCOREDAT_PLACES * SCOREDAT_NAME_LEN) dup(?)
	SD_cleared	db ?
	SD_unknown	db ?
	SD_score	db (SCOREDAT_PLACES * (SCORE_DIGITS + 2)) dup(?)
	SD_playchar	db SCOREDAT_PLACES dup(?)
	SD_stage	db SCOREDAT_PLACES dup(?)
	SD_key1 	db ?
	SD_key2 	db ?
scoredat_t ends

scoredat_section_t struc
	SDS_sum  	dw ?
	SDS_score	scoredat_t <?>
scoredat_section_t ends
