; ReC98
; Relevant function definitions from master.h, together with the necessary
; types. Meant as a master.h equivalent for standalone, non-slice ASM
; translation units.

include libs/master.lib/macros.inc

extern _SinTable8:word:256
extern _CosTable8:word:256

EGC_OFF procdesc pascal far
GAIJI_PUTSA procdesc pascal far \
	x:word, y:word, strp_seg:word, strp_off:word, atrb:word
GRAPH_PACK_PUT_8_NOCLIP procdesc pascal far \
	left:word, top:word, linepat_sgm:word, linepat_off:word, len:word
GRAPH_PI_FREE procdesc pascal far \
	header:far ptr, image:far ptr
extrn GRCG_SETCOLOR:proc
PALETTE_SHOW procdesc pascal far
