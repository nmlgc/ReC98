PTN_W = 32
PTN_H = 32
PTN_SLOT_COUNT = 8

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
