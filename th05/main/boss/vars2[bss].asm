; Variables for the secondary on-screen boss. Used for Yuki in the first part
; of the Stage 4 boss fight, for Shinki's leave animation at the beginning of
; the Stage 5 boss fight, and, weirdly enough, for the knife launch position
; in Phase 8 of the same fight.
public _boss2, _yuki
public _boss2_pos, _boss2_hp, _boss2_sprite, _boss2_phase, _boss2_phase_frame
public  _yuki_pos,  _yuki_hp,  _yuki_sprite,  _yuki_phase,  _yuki_phase_frame
public _boss2_damage_this_frame, _boss2_mode, _boss2_angle, _boss2_mode_change
public  _yuki_damage_this_frame,  _yuki_mode,  _yuki_angle,  _yuki_mode_change
public _boss2_phase_end_hp
public  _yuki_phase_end_hp

label _boss2 byte
label _yuki byte

label _yuki_pos motion_t
_boss2_pos	motion_t <?>

label _yuki_hp word
_boss2_hp 	dw ?

label _yuki_sprite byte
_boss2_sprite	db ?

label _yuki_phase byte
_boss2_phase	db ?

label _yuki_phase_frame word
_boss2_phase_frame	dw ?

label _yuki_damage_this_frame byte
_boss2_damage_this_frame 	db ?

label _yuki_mode byte
_boss2_mode	db ?

label _yuki_angle byte
_boss2_angle	db ?

label _yuki_mode_change byte
_boss2_mode_change	db ?

label _yuki_phase_end_hp word
_boss2_phase_end_hp	dw ?
