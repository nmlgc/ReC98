BOS_ENTITY_SLOT_COUNT = 4
BOS_ANIM_SLOT_COUNT = 2
BOS_IMAGES_PER_SLOT = 8

bos_image_t struc
	BOS_B	dd ?
	BOS_R	dd ?
	BOS_G	dd ?
	BOS_E	dd ?
	BOS_alpha	dd ?
bos_image_t ends

bos_t struc
	BOS_image	bos_image_t BOS_IMAGES_PER_SLOT dup (<?>)
bos_t ends

public _bos_entity_images, _bos_anim_images
_bos_entity_images	bos_t BOS_ENTITY_SLOT_COUNT dup(<?>)
_bos_anim_images  	bos_t BOS_ANIM_SLOT_COUNT dup(<?>)
