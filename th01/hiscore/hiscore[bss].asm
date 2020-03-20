SCOREDAT_PLACES = 10
SCOREDAT_NAME_KANJI = 8
SCOREDAT_NAME_BYTES = (SCOREDAT_NAME_KANJI * 2)

SCOREDAT_CLEARED = 40
SCOREDAT_CLEARED_MAKAI = (SCOREDAT_CLEARED + 10)
SCOREDAT_CLEARED_JIGOKU = (SCOREDAT_CLEARED + 20)

SCOREDAT_NAME_KEY = 9Ch

scoredat_names_t struc
	dw SCOREDAT_PLACES dup (SCOREDAT_NAME_KANJI dup (?))
scoredat_names_t ends

scoredat_points_t struc
	dd SCOREDAT_PLACES dup (?)
scoredat_points_t ends

scoredat_stages_t struc
	dw SCOREDAT_PLACES dup (?)
scoredat_stages_t ends

scoredat_routes_t struc
	dw SCOREDAT_PLACES dup (?)
scoredat_routes_t ends

public _scoredat_names, _scoredat_routes, _scoredat_stages, _scoredat_points
public _name_entered_left, _name_entered_top
_scoredat_names	dd ?
_scoredat_routes	dd ?
_scoredat_stages	dd ?
_name_entered_left	dw ?
_name_entered_top	dw ?
_scoredat_points	dd ?
