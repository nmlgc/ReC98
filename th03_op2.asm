	.386
	.model use16 large _TEXT

include ReC98.inc

_TEXT	segment	word public 'CODE' use16
	assume cs:_TEXT
	assume es:nothing, ds:_DATA, fs:nothing, gs:nothing

include libs/master.lib/bfnt_entry_pat.asm
include libs/master.lib/bfnt_extend_header_skip.asm
include libs/master.lib/bfnt_header_read.asm
include libs/master.lib/bfnt_header_analysis.asm
include libs/master.lib/bcloser.asm
include libs/master.lib/bfill.asm
include libs/master.lib/bfnt_palette_set.asm
include libs/master.lib/bgetc.asm
include libs/master.lib/palette_black_out.asm
include libs/master.lib/bopenr.asm
include libs/master.lib/bread.asm
include libs/master.lib/bseek.asm
include libs/master.lib/bseek_.asm
include libs/master.lib/dos_axdx.asm
include libs/master.lib/dos_keyclear.asm
include libs/master.lib/dos_puts2.asm
include libs/master.lib/dos_setvect.asm
include libs/master.lib/egc.asm
include libs/master.lib/egc_shift_left_all.asm
include libs/master.lib/file_append.asm
include libs/master.lib/file_close.asm
include libs/master.lib/file_create.asm
include libs/master.lib/file_exist.asm
include libs/master.lib/file_read.asm
include libs/master.lib/file_ropen.asm
include libs/master.lib/file_seek.asm
include libs/master.lib/file_write.asm
include libs/master.lib/dos_close.asm
include libs/master.lib/dos_ropen.asm
include libs/master.lib/grcg_boxfill.asm
include libs/master.lib/grcg_byteboxfill_x.asm
include libs/master.lib/grcg_polygon_c.asm
include libs/master.lib/grcg_pset.asm
include libs/master.lib/grcg_setcolor.asm
include libs/master.lib/gaiji_backup.asm
include libs/master.lib/gaiji_entry_bfnt.asm
include libs/master.lib/gaiji_putsa.asm
include libs/master.lib/gaiji_read.asm
include libs/master.lib/gaiji_write.asm
include libs/master.lib/graph_400line.asm
include libs/master.lib/graph_clear.asm
include libs/master.lib/graph_copy_page.asm
include libs/master.lib/graph_extmode.asm
include libs/master.lib/graph_gaiji_puts.asm
include libs/master.lib/graph_pi_free.asm
include libs/master.lib/graph_pi_load_pack.asm
include libs/master.lib/graph_pack_put_8.asm
include libs/master.lib/graph_show.asm
include libs/master.lib/graph_start.asm
include libs/master.lib/js_end.asm
include libs/master.lib/keybeep.asm
include libs/master.lib/make_linework.asm
include libs/master.lib/palette_init.asm
include libs/master.lib/palette_show.asm
include libs/master.lib/pfclose.asm
include libs/master.lib/pfgetc.asm
include libs/master.lib/pfread.asm
include libs/master.lib/pfrewind.asm
include libs/master.lib/pfseek.asm
include libs/master.lib/random.asm
include libs/master.lib/palette_entry_rgb.asm
include libs/master.lib/rottbl.asm
include libs/master.lib/smem_release.asm
include libs/master.lib/smem_wget.asm
include libs/master.lib/soundio.asm
include libs/master.lib/text_clear.asm
include libs/master.lib/txesc.asm
include libs/master.lib/text_putsa.asm
include libs/master.lib/vsync.asm
include libs/master.lib/vsync_wait.asm
include libs/master.lib/palette_white_in.asm
include libs/master.lib/hmem_lallocate.asm
include libs/master.lib/mem_assign_dos.asm
include libs/master.lib/mem_assign.asm
include libs/master.lib/memheap.asm
include libs/master.lib/mem_unassign.asm
include libs/master.lib/super_free.asm
include libs/master.lib/super_entry_pat.asm
include libs/master.lib/super_entry_at.asm
include libs/master.lib/super_entry_bfnt.asm
include libs/master.lib/super_cancel_pat.asm
include libs/master.lib/super_put.asm
include libs/master.lib/respal_exist.asm
include libs/master.lib/respal_free.asm
include libs/master.lib/pfint21.asm
		db 0
include libs/master.lib/js_start.asm
include libs/master.lib/js_sense.asm
		db 0
include libs/master.lib/draw_trapezoid.asm
include th03/formats/pfopen.asm
include libs/master.lib/pf_str_ieq.asm
_TEXT	ends

	.data

public gpSTART, gpVS_START
public gpMUSIC_ROOM, gpHISCORE, gpOPTION, gpQUIT, gpRANK, gpMUSIC, gpKEYCONFIG
public gpEASY, gpNORMAL, gpHARD, gpLUNATIC, gpOFF, gpFM_86, gpMIDI_SC88, gpOFF
public gpFM_86, gpMIDI_SC88, gpKEY_VS_KEY, gpJOY_VS_KEY, gpKEY_VS_JOY
gpSTART	db 30h, 31h, 32h, 0
gpVS_START	db 33h, 34h, 35h, 36h, 37h, 38h, 0
gpMUSIC_ROOM	db 41h, 42h, 43h, 44h, 45h, 46h, 47h, 0
gpHISCORE	db 82h, 83h, 84h, 85h, 86h, 0
gpOPTION	db 3Dh, 3Eh, 3Fh, 40h, 0
gpQUIT	db 48h, 49h, 4Ah, 0
gpRANK	db 6Eh, 6Fh, 70h, 0
gpMUSIC	db 4Bh, 4Ch, 4Dh, 4Eh, 0
gpKEYCONFIG	db 5Ch, 5Dh, 5Eh, 5Fh, 60h, 61h, 0
g4SPACES	db 0CFh, 0CFh, 0CFh, 0CFh, 0
gpEASY	db 71h, 72h, 73h, 0
gpNORMAL	db 74h, 75h, 76h, 77h, 0
gpHARD	db 78h, 79h, 7Ah, 0
gpLUNATIC	db 7Bh, 7Ch, 7Dh, 7Eh, 0
gpOFF	db 0CFh, 0CFh, 5Ah, 5Bh, 0CFh, 0CFh, 0CFh, 0
gpFM_86	db 0CFh, 4Fh, 50h, 51h, 52h, 0CFh, 0CFh, 0
gpMIDI_SC88	db 53h, 54h, 55h, 56h, 57h, 58h, 59h, 0
gpTYPE1	db 62h, 63h, 64h, 65h, 0
gpTYPE2	db 62h, 63h, 64h, 66h, 0
gpTYPE3	db 62h, 63h, 64h, 67h, 0
gpKEY_VS_KEY	db 68h, 69h, 6Ch, 6Dh, 68h, 69h, 0
gpJOY_VS_KEY	db 6Ah, 6Bh, 6Ch, 6Dh, 68h, 69h, 0
gpKEY_VS_JOY	db 68h, 69h, 6Ch, 6Dh, 6Ah, 6Bh, 0

public _menu_sel, _quit, byte_D953, _main_menu_initialized, _option_initialized
_menu_sel	db 0
_quit	db 0
byte_D953	db 1
_main_menu_initialized	db 0
_option_initialized	db 0

public _CFG_FN, _BINARY_MAINL
_CFG_FN	db 'YUME.CFG',0
_BINARY_MAINL	db 'mainl',0

public asc_D965, aVfvcvbgngngbgn, aUmx, aViosrfvVVkvqbd, aCOul
public aGbgvgkxsslvVBb, aMikoft_bft
asc_D965	db '        ',0
aVfvcvbgngngbgn	db '‚f‚c‚bƒNƒƒbƒN‚ª‚T‚l‚g‚š‚É‚È‚Á‚Ä‚¢‚Ü‚·B',0Ah,0
aUmx	db '“Œ•û–²‹ó‚Í‚QD‚T‚l‚g‚š‚Å‚È‚¢‚Æ³í‚ÉƒQ[ƒ€‚ªƒvƒŒƒCo—ˆ‚Ü‚¹‚ñ',0Ah,0
aViosrfvVVkvqbd	db 0Ah
	db '‚¨è”‚Å‚·‚ª‚QD‚T‚l‚g‚š‚ÉØ‚è‘Ö‚¦‚ÄA‚à‚¤ˆê“xÀs‚µ‚Ä‚ËB',0Ah,0
aCOul	db '–²‹ó1.dat',0
aGbgvgkxsslvVBb	db 0Ah
	db 'ƒƒ‚ƒŠ•s‘«‚Å‚·Bƒƒ‚ƒŠ‹ó‚«‚ğ‘‚â‚µ‚Ä‚©‚çÀs‚µ‚Ä‚­‚è‚á‚ê',0Ah,0
aMikoft_bft	db 'MIKOFT.bft',0
	evendata
include libs/master.lib/bfnt_id[data].asm
include libs/master.lib/clip[data].asm
include libs/master.lib/edges[data].asm
include libs/master.lib/fil[data].asm
include libs/master.lib/dos_ropen[data].asm
include libs/master.lib/gaiji_backup[data].asm
include libs/master.lib/gaiji_entry_bfnt[data].asm
include libs/master.lib/grp[data].asm
include libs/master.lib/js[data].asm
include libs/master.lib/pal[data].asm
include libs/master.lib/pf[data].asm
include libs/master.lib/rand[data].asm
include libs/master.lib/sin8[data].asm
include libs/master.lib/tx[data].asm
include libs/master.lib/vs[data].asm
include libs/master.lib/wordmask[data].asm
include libs/master.lib/mem[data].asm
include libs/master.lib/super_entry_bfnt[data].asm
include libs/master.lib/superpa[data].asm
public _snd_active
_snd_active	db 0
	evendata
include libs/master.lib/respal_exist[data].asm
include libs/master.lib/draw_trapezoid[data].asm
include th02/formats/pfopen[data].asm
include th03/formats/cdg[data].asm

	.data?

public _main_input_allowed, _option_input_allowed, _in_option, _putfunc
_main_input_allowed	db ?
_option_input_allowed	db ?
_in_option	db ?
	evendata
_putfunc	dw ?
include libs/master.lib/clip[bss].asm
include libs/master.lib/fil[bss].asm
include libs/master.lib/js[bss].asm
include libs/master.lib/pal[bss].asm
include libs/master.lib/vs[bss].asm
include libs/master.lib/vsync[bss].asm
include libs/master.lib/mem[bss].asm
include libs/master.lib/superpa[bss].asm
include th01/hardware/vram_planes[bss].asm
include th02/snd/snd[bss].asm
include th02/snd/load[bss].asm
include libs/master.lib/pfint21[bss].asm
include th03/hardware/input[bss].asm
include th03/formats/cdg[bss].asm
include th02/formats/pi_slots[bss].asm
include th03/formats/hfliplut[bss].asm

	end
