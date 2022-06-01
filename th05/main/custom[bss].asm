CUSTOM_COUNT = 64

custom_t struc
	db 26 dup (?)
custom_t ends

; Stage 2 star particles
; ----------------------
S2PARTICLE_COUNT = 64

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

; Cheeto bullets
; --------------
cheeto_template_t struc
		db ?
	CBTMPL_angle	db ?
	pos	motion_t <?>
		dw ?
		dw ?
	CBTMPL_col	dw ?
		dd ?
	CBTMPL_speed	db ?
		db ?
cheeto_template_t ends

cheeto_head_t struc
	flag	db ?
	CBH_angle	db ?
	pos	motion_t <?>
		dw ?
		dw ?
	CBH_sprite	dw ?
		dd ?
	CBH_speed	db ?
		db ?
cheeto_head_t ends

cheeto_template	equ <_custom_entities>
cheeto_heads	equ <_custom_entities[1 * size cheeto_head_t]>
; --------------

; Mai's and Yuki's 32×32 balls
; ----------------------------
B4BALL_COUNT = 63
B4BALL_W = 32
B4BALL_H = 32

b4ball_t struc
	flag	db ?
	B4B_angle	db ?
	pos	motion_t <?>
	B4B_age	dw ?
	B4B_revenge	dw ?
	B4B_patnum_tiny_base	dw ?
	B4B_hp	dw ?
	B4B_damaged_this_frame	dw ?
	B4B_speed db ?
		db ?
b4ball_t ends

b4ball_template	equ <_custom_entities>
b4balls	equ <_custom_entities[1 * size b4ball_t]>
; ------------------------------

; Yumeko's swords
; ---------------
SWORD_COUNT = 63
SWORD_W = 32
SWORD_H = 32

sword_t struc
	flag	db ?
	SWORD_angle	db ?
	pos	motion_t <?>
	twirl_time	dw ?
		dw ?
	SWORD_patnum_tiny	dw ?
	SWORD_decay_frames	dw ?
		dw ?
	SWORD_speed	db ?
		db ?
sword_t ends

sword_template	equ <_custom_entities>
swords	equ <_custom_entities[1 * size sword_t]>
; ---------------

; Shinki's 32×32 balls
; --------------------
B6BALL_COUNT = 63
B6BALL_W = 32
B6BALL_H = 32

b6ball_t struc
	flag	db ?
		db ?
	pos	motion_t <?>
		dw ?
	cloud_radius	dw ?
	B6B_patnum_tiny	dw ?
		dw ?
		dw ?
		db ?
		db ?
b6ball_t ends

b6balls	equ <_custom_entities[1 * size b6ball_t]>
; --------------------

public _custom_entities
_custom_entities	custom_t CUSTOM_COUNT dup (<?>)
	custom_t <?> ; 1 additional unused one, for some reason?
