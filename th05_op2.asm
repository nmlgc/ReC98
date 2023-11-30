GAME = 5

	.386
	.model use16 large _TEXT

include ReC98.inc

g_SHARED group SHARED, SHARED_

_TEXT	segment	word public 'CODE' use16
	assume cs:_TEXT
	assume es:nothing, ds:_DATA, fs:nothing, gs:nothing

include libs/master.lib/bfnt_entry_pat.asm
include libs/master.lib/bfnt_header_read.asm
include libs/master.lib/bfnt_header_analysis.asm
include libs/master.lib/atrtcmod.asm
include libs/master.lib/bcloser.asm
include libs/master.lib/bfill.asm
include libs/master.lib/bfnt_palette_set.asm
include libs/master.lib/bgetc.asm
include libs/master.lib/palette_black_in.asm
include libs/master.lib/palette_black_out.asm
include libs/master.lib/bopenr.asm
include libs/master.lib/bread.asm
include libs/master.lib/bseek.asm
include libs/master.lib/bseek_.asm
include libs/master.lib/dos_axdx.asm
include libs/master.lib/dos_keyclear.asm
include libs/master.lib/dos_puts2.asm
include libs/master.lib/dos_read.asm
include libs/master.lib/dos_seek.asm
include libs/master.lib/dos_setvect.asm
include libs/master.lib/egc.asm
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
include libs/master.lib/grcg_byteboxfill_x.asm
include libs/master.lib/grcg_hline.asm
include libs/master.lib/grcg_polygon_c.asm
include libs/master.lib/grcg_setcolor.asm
include libs/master.lib/grcg_vline.asm
include libs/master.lib/get_machine_98.asm
include libs/master.lib/get_machine_at.asm
include libs/master.lib/get_machine_dosbox.asm
include libs/master.lib/check_machine_fmr.asm
include libs/master.lib/get_machine.asm
include libs/master.lib/graph_400line.asm
include libs/master.lib/graph_clear.asm
include libs/master.lib/graph_copy_page.asm
include libs/master.lib/graph_extmode.asm
include libs/master.lib/graph_pi_free.asm
include libs/master.lib/graph_pi_load_pack.asm
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
include libs/master.lib/rottbl.asm
include libs/master.lib/smem_release.asm
include libs/master.lib/smem_wget.asm
include libs/master.lib/soundio.asm
include libs/master.lib/text_clear.asm
include libs/master.lib/txesc.asm
include libs/master.lib/vsync.asm
include libs/master.lib/vsync_wait.asm
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
include libs/master.lib/super_put_rect.asm
include libs/master.lib/super_put.asm
include libs/master.lib/respal_exist.asm
include libs/master.lib/respal_free.asm
include libs/master.lib/js_start.asm
include libs/master.lib/draw_trapezoid.asm
include libs/master.lib/js_sense.asm
include libs/master.lib/bgm_bell_org.asm
include libs/master.lib/bgm_mget.asm
include libs/master.lib/bgm_read_sdata.asm
include libs/master.lib/bgm_timer.asm
include libs/master.lib/bgm_pinit.asm
include libs/master.lib/bgm_timerhook.asm
include libs/master.lib/bgm_play.asm
include libs/master.lib/bgm_sound.asm
include libs/master.lib/bgm_effect_sound.asm
include libs/master.lib/bgm_stop_play.asm
include libs/master.lib/bgm_set_tempo.asm
include libs/master.lib/bgm_init_finish.asm
include libs/master.lib/bgm_stop_sound.asm
include libs/master.lib/graph_pack_put_8_noclip.asm
include libs/master.lib/graph_gaiji_puts.asm
include libs/master.lib/graph_gaiji_putc.asm
include libs/master.lib/pfint21.asm
		db 0
include th03/formats/pfopen.asm
include libs/master.lib/pf_str_ieq.asm
_TEXT	ends

OP_SETUP_TEXT segment byte public 'CODE' use16
OP_SETUP_TEXT ends

CFG_TEXT segment byte public 'CODE' use16
CFG_TEXT ends

OP_TITLE_TEXT segment byte public 'CODE' use16
OP_TITLE_TEXT ends

op_01_TEXT segment byte public 'CODE' use16
op_01_TEXT ends

HI_VIEW_TEXT segment byte public 'CODE' use16
HI_VIEW_TEXT ends

M_CHAR_TEXT segment byte public 'CODE' use16
M_CHAR_TEXT ends

SHARED	segment	word public 'CODE' use16
SHARED	ends

SHARED_	segment	word public 'CODE' use16
	assume cs:g_SHARED
	assume es:nothing, ss:nothing, ds:_DATA, fs:nothing, gs:nothing

include th04/hardware/grppsafx.asm
SHARED_	ends

	.data

include libs/master.lib/atrtcmod[data].asm
include libs/master.lib/bfnt_id[data].asm
include libs/master.lib/clip[data].asm
include libs/master.lib/edges[data].asm
include libs/master.lib/fil[data].asm
include libs/master.lib/dos_ropen[data].asm
include libs/master.lib/get_machine_98[data].asm
include libs/master.lib/get_machine_at[data].asm
include libs/master.lib/grp[data].asm
include libs/master.lib/js[data].asm
include libs/master.lib/machine[data].asm
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
include libs/master.lib/respal_exist[data].asm
include libs/master.lib/draw_trapezoid[data].asm
include libs/master.lib/bgm_timerhook[data].asm
include libs/master.lib/bgm[data].asm
include th04/snd/se_priority[data].asm
include th04/hardware/grppsafx[data].asm
include th03/snd/se_state[data].asm
include th04/hardware/bgimage[data].asm
include th05/mem[data].asm
include th05/op/piano[data].asm
include th05/sprites/piano_l.asp
include th05/snd/load[data].asm
include th04/snd/snd[data].asm
include th03/formats/pi_put_masked[data].asm
include th05/formats/pi_buffers[bss].asm
include th05/hardware/vram_planes[data].asm
include th03/formats/cdg[data].asm

	.data?

include libs/master.lib/clip[bss].asm
include libs/master.lib/fil[bss].asm
include libs/master.lib/js[bss].asm
include libs/master.lib/pal[bss].asm
include libs/master.lib/vs[bss].asm
include libs/master.lib/vsync[bss].asm
include libs/master.lib/mem[bss].asm
include libs/master.lib/superpa[bss].asm
include libs/master.lib/super_put_rect[bss].asm
include th03/formats/hfliplut[bss].asm
include th04/snd/interrupt[bss].asm
include libs/master.lib/bgm[bss].asm
include th05/op/piano[bss].asm
include th02/snd/load[bss].asm
include th05/formats/pi_put_masked[bss].asm
include th05/formats/pi_headers[bss].asm
include th04/hardware/input[bss].asm
include th04/formats/cdg[bss].asm
include libs/master.lib/pfint21[bss].asm
include th04/hardware/egcrect[bss].asm

	end
