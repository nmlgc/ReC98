PTN_W = 32
PTN_H = 32
PTN_SLOT_COUNT = 8

PTN_IMAGES_PER_SLOT = 64
PTN_SLOT_0 = (0 * PTN_IMAGES_PER_SLOT)
PTN_SLOT_1 = (1 * PTN_IMAGES_PER_SLOT)
PTN_SLOT_2 = (2 * PTN_IMAGES_PER_SLOT)
PTN_SLOT_3 = (3 * PTN_IMAGES_PER_SLOT)
PTN_SLOT_4 = (4 * PTN_IMAGES_PER_SLOT)
PTN_SLOT_5 = (5 * PTN_IMAGES_PER_SLOT)

ptn_planar_t struc
	PTN_B	dd PTN_H dup (?)
	PTN_R	dd PTN_H dup (?)
	PTN_G	dd PTN_H dup (?)
	PTN_E	dd PTN_H dup (?)
ptn_planar_t ends

ptn_t struc
		db ?
	planes	ptn_planar_t <?>
	PTN_alpha	dd PTN_H dup (?)
ptn_t ends

public _ptn_images
_ptn_images	dd PTN_SLOT_COUNT dup(?)

GRX_COUNT = 16
PLANAR_STREAM_PER_GRX_COUNT = 16

public _rle_streams, _planar_streams, _planar_stream_count
_rle_streams	dd GRX_COUNT dup (?)
_planar_streams	dd GRX_COUNT dup (PLANAR_STREAM_PER_GRX_COUNT dup (?))
_planar_stream_count	db GRX_COUNT dup (?)
