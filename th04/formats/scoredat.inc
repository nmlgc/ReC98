if GAME eq 5
SCOREDAT_PLACES = 5
SCOREDAT_NOT_CLEARED = 18
SCOREDAT_CLEARED = 80h
else
SCOREDAT_PLACES = 10
SCOREDAT_NOT_CLEARED = 25
endif

SCOREDAT_NAME_LEN = 8

scoredat_t struc
	g_name  	db SCOREDAT_PLACES dup ((SCOREDAT_NAME_LEN + 1) dup (?))
	g_points	db SCOREDAT_PLACES dup (SCORE_DIGITS dup (?))

if GAME eq 5
	g_stage 	db SCOREDAT_PLACES dup (?)
	cleared 	db ?
	        	db ?
else
	cleared 	db ?
	        	db ?
	g_stage 	db SCOREDAT_PLACES dup (?)
	        	db SCOREDAT_PLACES dup (?)
endif
scoredat_t ends

scoredat_section_t struc
	key1 	db ?
	key2 	db ?
	sum   	dw ?
	score	scoredat_t <?>
scoredat_section_t ends
