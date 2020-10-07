PLAYER_ANIM_IMAGES_PER_SLOT = 32

CPlayerAnim struc
	PA_alpha	dd PLAYER_ANIM_IMAGES_PER_SLOT dup(?)
	PA_B	dd PLAYER_ANIM_IMAGES_PER_SLOT dup(?)
	PA_R	dd PLAYER_ANIM_IMAGES_PER_SLOT dup(?)
	PA_G	dd PLAYER_ANIM_IMAGES_PER_SLOT dup(?)
	PA_E	dd PLAYER_ANIM_IMAGES_PER_SLOT dup(?)
	PA_vram_w	dw ?
	PA_h	dw ?
	PA_bos_image_count	dw ?
CPlayerAnim ends

public _player_anim_forward, _player_anim_slide
_player_anim_forward	CPlayerAnim <?>
_player_anim_slide	CPlayerAnim <?>
