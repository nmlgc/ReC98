; Variables for the secondary on-screen boss. Used for Yuki in the first part
; of the Stage 4 boss fight, for Shinki's leave animation at the beginning of
; the Stage 5 boss fight, and, weirdly enough, for the knife launch position
; in Phase 8 of the same fight.
public _boss2_pos, _boss2_hp, _boss2_sprite
public  _yuki_pos,  _yuki_hp,  _yuki_sprite

label _yuki_pos motion_t
_boss2_pos	motion_t <?>

label _yuki_hp word
_boss2_hp 	dw ?

label _yuki_sprite byte
_boss2_sprite	db ?

	db ?
_boss2_unused	dw ?
