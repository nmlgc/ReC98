if GAME eq 5
SCOREDAT_PLACES = 5
SCOREDAT_NOT_CLEARED = 18
SCOREDAT_CLEARED = 80h
else
SCOREDAT_PLACES = 10
SCOREDAT_NOT_CLEARED = 25
SCOREDAT_CLEARED_A = 1
SCOREDAT_CLEARED_B = 2
SCOREDAT_CLEARED_BOTH = SCOREDAT_CLEARED_A or SCOREDAT_CLEARED_B
endif

SCOREDAT_NAME_LEN = 8

scoredat_t struc
	g_name  	db SCOREDAT_PLACES dup ((SCOREDAT_NAME_LEN + 1) dup (?))
	g_score 	db SCOREDAT_PLACES dup (SCORE_DIGITS dup (?))

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

ifdef BINARY
	scoredat_decode_func equ <scoredat_decode>
	scoredat_encode_func equ <scoredat_encode>
	if BINARY eq 'O'
		scoredat_decode_func equ <scoredat_decode_both>
	elseif (BINARY eq 'M') and (GAME eq 4)
		scoredat_decode_func equ <scoredat_decode pascal, offset _hi>
		scoredat_encode_func equ <scoredat_encode pascal, offset _hi>
	endif

	if GAME eq 5
		if BINARY eq 'O'
			scoredat_recreate_func equ <scoredat_recreate_op>
		elseif BINARY eq 'E'
			scoredat_recreate_func equ <scoredat_recreate_maine>
		endif
	else
		scoredat_recreate_func equ <scoredat_recreate>
	endif
endif
