GRC_SLOT_COUNT = 8
GRC_IMAGES_PER_SLOT = 8

grc_t struc
	GRC_vram_w	dw ?
	GRC_h     	dw ?
	GRC_image_count	dw ?
	GRC_dots	dd GRC_IMAGES_PER_SLOT dup(?)
grc_t ends

public _grc_images
_grc_images	grc_t GRC_SLOT_COUNT dup(<?>)
