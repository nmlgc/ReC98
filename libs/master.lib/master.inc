; ReC98
; Relevant function definitions from master.h, together with the necessary
; types. Meant as a master.h equivalent for standalone, non-slice ASM
; translation units.

include libs/master.lib/macros.inc

GAIJI_PUTSA procdesc pascal far \
	x:word, y:word, strp_seg:word, strp_off:word, atrb:word
GRAPH_PI_FREE procdesc pascal far \
	header:far ptr, image:far ptr
PALETTE_SHOW procdesc pascal far
