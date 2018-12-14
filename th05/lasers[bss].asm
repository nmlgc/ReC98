; Modes
; -----
LM_NONE = 0
LM_SHOOTOUT = 1
LM_FIXED_WAIT_TO_GROW = 2
LM_FIXED_GROW = 3
; Fixed laser has reached its target width and will now actually kill the
; player on contact
LM_FIXED_ACTIVE = 4
LM_FIXED_SHRINK = 5
LM_FIXED_SHRINK_AND_WAIT_TO_GROW = 6
LM_DECAY = 7
; -----

; Structures
; ----------
; TODO: Remove the anti-collision LASER_ prefixes once this gets decompiled.

; [origin] and the two distances are stored in units of 1/16th of a pixel.
laser_coords_t struc
	origin            	Point <?>

	; Start and end point on the infinite [angle]° line starting at [origin]
	; that make up the actually rendered (and damaging) laser.
	starts_at_distance	dw ?
	ends_at_distance  	dw ?

	angle             	db ?
	LASER_width       	db ?
laser_coords_t ends

laser_t struc
	mode          	db ?

	LASER_color   	db ?

	coords        	laser_coords_t <?>

	; 1/16th pixel units per frame.
	shootout_speed	dw ?
	LASER_age     	dw ?

	; [age] at which a fixed laser should transition from LM_FIXED_WAIT_TO_GROW
	; to LM_FIXED_GROW.
	grow_at_age   	label word
	; [age] at which a shoot-out laser should stop growing and start moving
	; along the infinite [angle]° line.
	moveout_at_age	label word
	              	dw ?

	; [age] at which a fixed laser should transition from LM_FIXED_ACTIVE to
	; LM_FIXED_SHRINK.
	shrink_at_age 	dw ?
	; [width] at which a fixed laser should transition from LM_FIXED_GROW to
	; LM_FIXED_ACTIVE.
	grow_to_width 	db ?
	              	db 3 dup(?)
laser_t ends
; ----------

LASER_COUNT = 32
_lasers        	laser_t LASER_COUNT dup(<?>)
_laser_template	laser_t <?>
