GAME = 4

	.386
	.model use16 large _TEXT

include ReC98.inc

group_01 group MAINE_E_TEXT, CUTSCENE_TEXT, maine_01_TEXT

_TEXT segment word public 'CODE' use16
	assume cs:_TEXT
	assume es:nothing, ds:_DATA, fs:nothing, gs:nothing

include libs/master.lib/bfnt_entry_pat.asm
include libs/master.lib/bfnt_extend_header_skip.asm
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
include libs/master.lib/dos_filesize.asm
include libs/master.lib/dos_keyclear.asm
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
include libs/master.lib/file_size.asm
include libs/master.lib/file_write.asm
include libs/master.lib/dos_close.asm
include libs/master.lib/dos_ropen.asm
include libs/master.lib/grcg_byteboxfill_x.asm
include libs/master.lib/grcg_setcolor.asm
include libs/master.lib/gdc_outpw.asm
include libs/master.lib/get_machine_98.asm
include libs/master.lib/get_machine_at.asm
include libs/master.lib/get_machine_dosbox.asm
include libs/master.lib/check_machine_fmr.asm
include libs/master.lib/get_machine.asm
include libs/master.lib/gaiji_backup.asm
include libs/master.lib/gaiji_entry_bfnt.asm
include libs/master.lib/gaiji_putca.asm
include libs/master.lib/gaiji_putsa.asm
include libs/master.lib/gaiji_read.asm
include libs/master.lib/gaiji_write.asm
include libs/master.lib/graph_400line.asm
include libs/master.lib/graph_clear.asm
include libs/master.lib/graph_copy_page.asm
include libs/master.lib/graph_extmode.asm
include libs/master.lib/graph_hide.asm
include libs/master.lib/graph_pi_free.asm
include libs/master.lib/graph_pi_load_pack.asm
include libs/master.lib/graph_pack_put_8.asm
include libs/master.lib/graph_scrollup.asm
include libs/master.lib/graph_show.asm
include libs/master.lib/js_end.asm
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
include libs/master.lib/vsync.asm
include libs/master.lib/vsync_wait.asm
include libs/master.lib/palette_white_in.asm
include libs/master.lib/palette_white_out.asm
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
include libs/master.lib/pfint21.asm
		db 0
include libs/master.lib/js_start.asm
include th03/formats/pfopen.asm
include libs/master.lib/pf_str_ieq.asm
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
_TEXT ends

MAINE_E_TEXT segment byte public 'CODE' use16
MAINE_E_TEXT ends

CUTSCENE_TEXT segment byte public 'CODE' use16
CUTSCENE_TEXT ends

maine_01_TEXT segment byte public 'CODE' use16
maine_01_TEXT ends

	.data

include libs/master.lib/atrtcmod[data].asm
include libs/master.lib/bfnt_id[data].asm
include libs/master.lib/clip[data].asm
include libs/master.lib/fil[data].asm
include libs/master.lib/dos_ropen[data].asm
include libs/master.lib/get_machine_98[data].asm
include libs/master.lib/get_machine_at[data].asm
include libs/master.lib/gaiji_backup[data].asm
include libs/master.lib/gaiji_entry_bfnt[data].asm
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
include th02/formats/pfopen[data].asm
include libs/master.lib/bgm_timerhook[data].asm
include libs/master.lib/bgm[data].asm
include th04/snd/se_priority[data].asm
include th04/formats/cdg_put_plane[data].asm
include th04/snd/snd[data].asm
		db    0
include th04/snd/load[data].asm

	.data?

include libs/master.lib/clip[bss].asm
include libs/master.lib/fil[bss].asm
include libs/master.lib/js[bss].asm
include libs/master.lib/pal[bss].asm
include libs/master.lib/vs[bss].asm
include libs/master.lib/vsync[bss].asm
include libs/master.lib/mem[bss].asm
include libs/master.lib/superpa[bss].asm
include th01/hardware/vram_planes[bss].asm
include libs/master.lib/pfint21[bss].asm
include th02/formats/pi_slots[bss].asm
include th03/formats/hfliplut[bss].asm
include th04/snd/interrupt[bss].asm
include libs/master.lib/bgm[bss].asm

	end
