CUSTOM_COUNT = 64

custom_t struc
	db 26 dup (?)
custom_t ends

; Stage 2 star particles
; ----------------------
S2PARTICLE_COUNT = 64
S2PARTICLE_W = 16
S2PARTICLE_H = 16

s2particle_t struc
	flag	db ?
	S2P_angle	db ?
	pos	motion_t <?>
	zoom	dw ?
		dw 5 dup (?)
s2particle_t ends

s2particles	equ <_custom_entities>
; ----------------------

public _custom_entities
