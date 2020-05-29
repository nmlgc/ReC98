BOS_SLOT_COUNT = 4
BOS_FAST_SLOT_COUNT = 2
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

public _bos_images, _bos_fast_images
_bos_images	bos_t BOS_SLOT_COUNT dup(<?>)
_bos_fast_images	bos_t BOS_FAST_SLOT_COUNT dup(<?>)
