BYTEREGS	struc ;	(sizeof=0x8, standard type)
_al		db ?
_ah		db ?
_bl		db ?
_bh		db ?
_cl		db ?
_ch		db ?
_dl		db ?
_dh		db ?
BYTEREGS	ends

WORDREGS	struc ;	(sizeof=0x10, standard type)
_ax		dw ?
_bx		dw ?
_cx		dw ?
_dx		dw ?
_si		dw ?
_di		dw ?
_cflags		dw ?
_flags		dw ?
WORDREGS	ends

REGS		union ;	(sizeof=0x10, standard type)
_w		WORDREGS <?>
_h		BYTEREGS <?>
REGS		ends

SREGS		struc ;	(sizeof=0x8, standard type)
_es		dw ?
_cs		dw ?
_ss		dw ?
_ds		dw ?
SREGS		ends
