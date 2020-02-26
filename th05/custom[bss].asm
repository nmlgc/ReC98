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

; Alice's puppets
; ---------------
PUPPET_COUNT = 2
PUPPET_W = 32
PUPPET_H = 32
PUPPET_HP = 500

puppet_t struc
	flag	db ?
	PUPPET_angle	db ?
	pos	motion_t <?>
	phase_frame	dw ?

	radius_motion	label word
	radius_gather	label word
		dw ?

	PUPPET_patnum	dw ?
	PUPPET_hp_cur	dw ? ; _cur to avoid a collision with PUPPET_HP
	PUPPET_damage_this_frame	dw ?
		dw ?
puppet_t ends

puppets	equ <_custom_entities>
puppet0	equ <puppets[0 * size puppet_t]>
puppet1	equ <puppets[1 * size puppet_t]>
; ---------------

; Curve bullets
; -------------
curvebullet_template_t struc
		db ?
	CBTMPL_angle	db ?
	pos	motion_t <?>
	CBTMPL_age	dw ?
		dw ?
	CBTMPL_col	dw ?
		dd ?
	CBTMPL_speed	db ?
		db ?
curvebullet_template_t ends

curvebullet_head_t struc
	flag	db ?
	CBH_angle	db ?
	pos	motion_t <?>
	CBH_age	dw ?
		dw ?
	CBH_sprite	dw ?
		dd ?
	CBH_speed	db ?
		db ?
curvebullet_head_t ends

curvebullet_template	equ <_custom_entities>
curvebullet_heads	equ <_custom_entities[1 * size curvebullet_head_t]>
; -------------

public _custom_entities
