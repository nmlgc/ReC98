; TODO: Remove the anti-collision SHOT_ prefixes once this gets
; decompiled.
shot_t struc
	flag       	db ?
	SHOT_age   	db ?
	pos        	motion_t <?>
	; The displayed sprite changes between this one and
	; [patnum_base + 1] every two frames.
if GAME eq 5
	patnum_base	db ?
	SHOT_type  	db ?
else
	patnum_base	dw ?
endif
	damage     	db ?
	SHOT_angle 	db ? ; Unused in TH04
shot_t ends

if GAME eq 5
	HITSHOT_FRAMES_PER_CEL = 3
	SHOT_COUNT = 64
else
	HITSHOT_FRAMES_PER_CEL = 4
	SHOT_COUNT = 68
endif

HITSHOT_FRAMES = (HITSHOT_CELS * HITSHOT_FRAMES_PER_CEL)

if (GAME eq 4)
	SF_FREE = 0
	SF_ALIVE = 1
	SF_HIT = 2
	SF_REMOVE = (SF_HIT + HITSHOT_FRAMES)
endif

public _shots
_shots	shot_t SHOT_COUNT dup(<?>)
_shots_end	label byte
