; Spark sprites, as seen when killing enemies or grazing.
; TODO: Remove the anti-collision SPARK_ prefix once this gets decompiled.
spark_t struc
	flag	db ?
	age 	db ?
	; Center position, stored in 1/16th-pixel playfield coordinates.
	pos 	motion_t <?>
	; Set during sparks_init() and never again, and only involved in
	; determining the initial velocity in sparks_add_*().
	SPARK_angle	dw ?
spark_t ends

if GAME eq 5
SPARK_COUNT = 64
else
SPARK_COUNT = 96
endif
; sparks_invalidate() and sparks_init() accidentally still this value in TH05.
SPARK_COUNT_BUG = 96

public _sparks
_sparks	spark_t SPARK_COUNT dup(<?>)
_sparks_unused	spark_t 4 dup(<?>)
