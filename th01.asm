; MASTER.LIB code used in the combined TH01 binary.

		.386
		.model use16 large _TEXT

include ReC98.inc

; ===========================================================================

; Segment type:	Pure code
_TEXT		segment	word public 'CODE' use16
		assume cs:_TEXT
		assume es:nothing, ds:DGROUP, fs:nothing, gs:nothing

include libs/master.lib/text_clear.asm
include libs/master.lib/text_fillca.asm
include libs/master.lib/graph_400line.asm
include libs/master.lib/graph_clear.asm
include libs/master.lib/graph_show.asm
include libs/master.lib/graph_start.asm
include libs/master.lib/graph_scrollup.asm
include libs/master.lib/palette_show.asm
include libs/master.lib/palette_init.asm
include libs/master.lib/resdata.asm
include libs/master.lib/file_read.asm
include libs/master.lib/file_close.asm
include libs/master.lib/file_exist.asm
include libs/master.lib/file_ropen.asm
include libs/master.lib/file_write.asm
include libs/master.lib/file_create.asm
include libs/master.lib/file_seek.asm
include libs/master.lib/dos_free.asm
include libs/master.lib/dos_axdx.asm
include libs/master.lib/keystart.asm
include libs/master.lib/key_sense.asm
include libs/master.lib/keybios.asm
include libs/master.lib/dos_ropen.asm
include libs/master.lib/grcg_setcolor.asm
include libs/master.lib/grcg_pset.asm
include libs/master.lib/egc.asm
include libs/master.lib/iatan2.asm
include libs/master.lib/isqrt.asm
include libs/master.lib/gdc_outpw.asm
include libs/master.lib/random.asm
_TEXT		ends

	.data

include libs/master.lib/version[data].asm
include libs/master.lib/tx[data].asm
include libs/master.lib/grp[data].asm
include libs/master.lib/pal[data].asm
include libs/master.lib/fil[data].asm
include libs/master.lib/keytable[data].asm
include libs/master.lib/keystart[data].asm
include libs/master.lib/keyback[data].asm
include libs/master.lib/dos_ropen[data].asm
include libs/master.lib/clip[data].asm
include libs/master.lib/sin8[data].asm
include libs/master.lib/atan8[data].asm
include libs/master.lib/rand[data].asm

	.data?

include libs/master.lib/pal[bss].asm
include libs/master.lib/fil[bss].asm
include libs/master.lib/keystart[bss].asm

	end
