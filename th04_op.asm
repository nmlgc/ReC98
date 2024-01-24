;
; +-------------------------------------------------------------------------+
; |   This file has been generated by The Interactive Disassembler (IDA)    |
; |        Copyright (c) 2009 by Hex-Rays, <support@hex-rays.com>           |
; +-------------------------------------------------------------------------+
;
; Input	MD5   :	492DA6ACEE8714C252630BCE0D3C12FD

; File Name   :	th04/OP.EXE
; Format      :	MS-DOS executable (EXE)
; Base Address:	0h Range: 0h-133E0h Loaded length: 11A40h
; Entry	Point :	0:0
; OS type	  :  MS	DOS
; Application type:  Executable	16bit

		.386
		.model use16 large _TEXT

BINARY = 'O'

include ReC98.inc
include th04/th04.inc
include th04/sprites/op_cdg.inc

op_01 group OP_SETUP_TEXT, op_01_TEXT

; ===========================================================================

_TEXT	segment	word public 'CODE' use16
	extern PALETTE_BLACK_IN:proc
	extern PALETTE_BLACK_OUT:proc
	extern FILE_CLOSE:proc
	extern FILE_CREATE:proc
	extern FILE_EXIST:proc
	extern FILE_READ:proc
	extern FILE_ROPEN:proc
	extern FILE_SEEK:proc
	extern FILE_WRITE:proc
	extern GRCG_BYTEBOXFILL_X:proc
	extern GRCG_SETCOLOR:proc
	extern GRAPH_CLEAR:proc
	extern GRAPH_COPY_PAGE:proc
	extern GRAPH_PI_FREE:proc
	extern PALETTE_SHOW:proc
	extern IRAND:proc
	extern SUPER_FREE:proc
	extern SUPER_ENTRY_BFNT:proc
	extern SUPER_PUT_RECT:proc
	extern SUPER_PUT:proc
	extern GRAPH_GAIJI_PUTS:proc
	extern GRAPH_GAIJI_PUTC:proc
_TEXT	ends

; ===========================================================================

; Segment type:	Pure code
OP_SETUP_TEXT segment byte public 'CODE' use16
		assume cs:op_01
		;org 0Ch
		assume es:nothing, ss:nothing, ds:_DATA, fs:nothing, gs:nothing

include th04/zunsoft.asm
OP_SETUP_TEXT ends

op_01_TEXT segment byte public 'CODE' use16
include th04/formats/scoredat_decode_both.asm
include th04/formats/scoredat_encode.asm
include th04/formats/scoredat_recreate.asm
include th04/formats/scoredat_load_both.asm

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_C79E	proc near

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6

		enter	4, 0
		push	si
		push	di
		mov	di, [bp+arg_2]
		mov	si, [bp+arg_0]
		mov	[bp+var_4], 16
		mov	bx, si
		shl	bx, 3
		mov	al, _hi_reimu.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		cmp	ax, 10
		jl	short loc_C7E0
		push	140
		push	di
		mov	bx, si
		shl	bx, 3
		mov	al, _hi_reimu.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		mov	bx, 10
		cwd
		idiv	bx
		push	ax
		call	super_put

loc_C7E0:
		mov	bx, si
		shl	bx, 3
		mov	al, _hi_marisa.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		cmp	ax, 10
		jl	short loc_C811
		push	448
		push	di
		mov	bx, si
		shl	bx, 3
		mov	al, _hi_marisa.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		mov	bx, 10
		cwd
		idiv	bx
		push	ax
		call	super_put

loc_C811:
		push	156
		push	di
		mov	bx, si
		shl	bx, 3
		mov	al, _hi_reimu.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		mov	bx, 10
		cwd
		idiv	bx
		push	dx
		call	super_put
		push	464
		push	di
		mov	bx, si
		shl	bx, 3
		mov	al, _hi_marisa.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		mov	bx, 10
		cwd
		idiv	bx
		push	dx
		call	super_put
		mov	[bp+var_2], 6
		jmp	short loc_C899
; ---------------------------------------------------------------------------

loc_C854:
		mov	ax, [bp+var_4]
		add	ax, 156
		push	ax
		push	di
		mov	bx, si
		shl	bx, 3
		add	bx, [bp+var_2]
		mov	al, _hi_reimu.score.g_score[bx]
		mov	ah, 0
		add	ax, -gb_0_
		push	ax
		call	super_put
		mov	ax, [bp+var_4]
		add	ax, 464
		push	ax
		push	di
		mov	bx, si
		shl	bx, 3
		add	bx, [bp+var_2]
		mov	al, _hi_marisa.score.g_score[bx]
		mov	ah, 0
		add	ax, -gb_0_
		push	ax
		call	super_put
		dec	[bp+var_2]
		add	[bp+var_4], 16

loc_C899:
		cmp	[bp+var_2], 0
		jge	short loc_C854
		pop	di
		pop	si
		leave
		retn	4
sub_C79E	endp

include th04/hiscore/hiscore_stage_put.asm

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_C8F5	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_0]
		or	si, si
		jnz	loc_C989
		push	(10 shl 16) or 98
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_reimu.score.g_name
		push	ds
		push	ax
		push	14
		call	graph_gaiji_puts
		push	(8 shl 16) or 96
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_reimu.score.g_name
		push	ds
		push	ax
		push	7
		call	graph_gaiji_puts
		push	(322 shl 16) or 98
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_marisa.score.g_name
		push	ds
		push	ax
		push	14
		call	graph_gaiji_puts
		push	(320 shl 16) or 96
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_marisa.score.g_name
		push	ds
		push	ax
		push	7
		call	graph_gaiji_puts
		push	600000h
		call	sub_C79E
		push	(292 shl 16) or 96
		mov	al, _hi_reimu.score.g_stage[si]
		mov	ah, 0
		push	ax
		call	hiscore_stage_put
		push	(600 shl 16) or 96

		; Hack (jmp	loc_CA0A)
		; No idea why TASM can't assemble this properly after
		; dropdown() was decompiled.
		db	0E9h, 81h, 00h
; ---------------------------------------------------------------------------

loc_C989:
		mov	ax, si
		shl	ax, 4
		add	ax, 112
		mov	di, ax
		push	10
		add	ax, 2
		push	ax
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_reimu.score.g_name
		push	ds
		push	ax
		push	14
		call	graph_gaiji_puts
		push	8
		push	di
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_reimu.score.g_name
		push	ds
		push	ax
		push	2
		call	graph_gaiji_puts
		push	322
		lea	ax, [di+2]
		push	ax
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_marisa.score.g_name
		push	ds
		push	ax
		push	14
		call	graph_gaiji_puts
		push	320
		push	di
		push	GAIJI_W
		mov	ax, si
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi_marisa.score.g_name
		push	ds
		push	ax
		push	2
		call	graph_gaiji_puts
		push	di
		push	si
		call	sub_C79E
		push	292
		push	di
		mov	al, _hi_reimu.score.g_stage[si]
		mov	ah, 0
		push	ax
		call	hiscore_stage_put
		push	600
		push	di

loc_CA0A:
		mov	al, _hi_marisa.score.g_stage[si]
		mov	ah, 0
		push	ax
		call	hiscore_stage_put
		pop	di
		pop	si
		pop	bp
		retn	2
sub_C8F5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _score_render
_score_render proc near
		push	bp
		mov	bp, sp
		push	si
		graph_accesspage 1
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		graph_accesspage 0
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		push	0
		call	sub_C8F5
		mov	si, 1
		jmp	short loc_CA5B
; ---------------------------------------------------------------------------

loc_CA56:
		push	si
		call	sub_C8F5
		inc	si

loc_CA5B:
		cmp	si, 9
		jl	short loc_CA56
		push	9
		call	sub_C8F5
		push	(496 shl 16) or 376
		mov	al, _rank
		mov	ah, 0
		add	ax, ax
		add	ax, 10
		push	ax
		call	super_put
		push	(560 shl 16) or 376
		mov	al, _rank
		mov	ah, 0
		add	ax, ax
		add	ax, 11
		push	ax
		call	super_put
		pop	si
		pop	bp
		retn
_score_render endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _regist_view_menu
_regist_view_menu proc near
		push	bp
		mov	bp, sp
		kajacall	KAJA_SONG_STOP
		call	snd_load pascal, ds, offset aName, SND_LOAD_SONG
		kajacall	KAJA_SONG_PLAY
		kajacall	KAJA_SONG_FADE, -128
		push	1
		call	palette_black_out
		les	bx, _resident
		assume es:nothing
		mov	al, es:[bx+resident_t.rank]
		mov	_rank, al
		call	_scoredat_load_both
		call	pi_load pascal, 0, ds, offset aHi01_pi

loc_CADA:
		call	_score_render
		push	1
		call	palette_black_in

loc_CAE4:
		call	far ptr	_input_reset_sense
		call	@frame_delay$qi pascal, 1
		test	_key_det.hi, high INPUT_OK
		jnz	short loc_CB58
		test	_key_det.lo, low INPUT_SHOT
		jnz	short loc_CB58
		test	_key_det.hi, high INPUT_CANCEL
		jnz	short loc_CB58
		test	_key_det.hi, high INPUT_OK
		jnz	short loc_CB58
		test	_key_det.lo, low INPUT_LEFT
		jz	short loc_CB36
		cmp	_rank, RANK_EASY
		jz	short loc_CB36
		dec	_rank
		mov	PaletteTone, 0
		call	far ptr	palette_show
		call	_scoredat_load_both
		call	_score_render
		push	1
		call	palette_black_in

loc_CB36:
		test	_key_det.lo, low INPUT_RIGHT
		jz	short loc_CAE4
		cmp	_rank, RANK_EXTRA
		jnb	short loc_CAE4
		inc	_rank
		mov	PaletteTone, 0
		call	far ptr	palette_show
		call	_scoredat_load_both
		jmp	short loc_CADA
; ---------------------------------------------------------------------------

loc_CB58:
		kajacall	KAJA_SONG_FADE, 1
		push	1
		call	palette_black_out
		freePISlotLarge	0
		graph_accesspage 1
		call	pi_load pascal, 0, ds, offset aOp1_pi_0
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		freePISlotLarge	0
		call	graph_copy_page pascal, 0
		push	1
		call	palette_black_in

loc_CBB3:
		call	far ptr	_input_reset_sense
		call	@frame_delay$qi pascal, 1
		cmp	_key_det, INPUT_NONE
		jnz	short loc_CBB3
		kajacall	KAJA_SONG_STOP
		call	snd_load pascal, ds, offset aOp_0, SND_LOAD_SONG
		kajacall	KAJA_SONG_PLAY
		pop	bp
		retn
_regist_view_menu endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _cleardata_and_regist_view_sprite
_cleardata_and_regist_view_sprite	proc near
		push	bp
		mov	bp, sp
		mov	_rank, RANK_EASY
		jmp	loc_CC6F
; ---------------------------------------------------------------------------

loc_CBEE:
		call	_scoredat_load_both
		or	al, al
		jnz	loc_CC78
		mov	al, _rank
		mov	ah, 0
		mov	dl, _hi_reimu.score.cleared
		mov	bx, ax
		mov	_cleared_with_reimu[bx], dl
		mov	al, _rank
		mov	ah, 0
		mov	dl, _hi_marisa.score.cleared
		mov	bx, ax
		mov	_cleared_with_marisa[bx], dl
		mov	al, _rank
		mov	ah, 0
		mov	bx, ax
		cmp	_cleared_with_reimu[bx], SCOREDAT_CLEARED_BOTH
		jbe	short loc_CC2F
		mov	al, _rank
		mov	ah, 0
		mov	bx, ax
		mov	_cleared_with_reimu[bx], 0

loc_CC2F:
		mov	al, _rank
		mov	ah, 0
		mov	bx, ax
		cmp	_cleared_with_marisa[bx], SCOREDAT_CLEARED_BOTH
		jbe	short loc_CC49
		mov	al, _rank
		mov	ah, 0
		mov	bx, ax
		mov	_cleared_with_marisa[bx], 0

loc_CC49:
		cmp	_rank, RANK_EASY
		jz	short loc_CC6B
		mov	al, _rank
		mov	ah, 0
		mov	bx, ax
		mov	al, _cleared_with_reimu[bx]
		mov	dl, _rank
		mov	dh, 0
		mov	bx, dx
		or	al, _cleared_with_marisa[bx]
		or	_extra_unlocked, al

loc_CC6B:
		inc	_rank

loc_CC6F:
		cmp	_rank, RANK_COUNT
		jb	loc_CBEE

loc_CC78:
		les	bx, _resident
		mov	al, es:[bx+resident_t.rank]
		mov	_rank, al
		call	super_entry_bfnt pascal, ds, offset aScnum_bft ; "scnum.bft"
		call	super_entry_bfnt pascal, ds, offset aHi_m_bft ; "hi_m.bft"
		pop	bp
		retn
_cleardata_and_regist_view_sprite	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _main_cdg_load
_main_cdg_load	proc near
		push	bp
		mov	bp, sp
		call	cdg_load_all pascal, CDG_NUMERAL, ds, offset aSft1_cd2
		call	cdg_load_all pascal, CDG_MAIN, ds, offset aSft2_cd2
		call	cdg_load_all pascal, CDG_CURSOR, ds, offset aCar_cd2
		call	cdg_load_all_noalpha pascal, 40, ds, offset aSl_cd2
		pop	bp
		retn
_main_cdg_load	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _main_cdg_free
_main_cdg_free	proc near
		push	bp
		mov	bp, sp
		call	cdg_free_all
		pop	bp
		retn
_main_cdg_free	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _op_animate
_op_animate	proc near

@@page		= byte ptr -4
var_3		= byte ptr -3
@@component		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	PaletteTone, 0
		call	far ptr	palette_show
		graph_accesspage 1
		call	grcg_setcolor pascal, (GC_RMW shl 16) + V_WHITE
		call	grcg_byteboxfill_x pascal, large 0, (((RES_X - 1) / 8) shl 16) or (RES_Y - 1)
		GRCG_OFF_CLOBBERING dx
		call	graph_copy_page pascal, 0
		call	pi_load pascal, 0, ds, offset aOp5b_pi
		call	pi_load pascal, 1, ds, offset aOp4b_pi
		call	pi_load pascal, 2, ds, offset aOp3b_pi
		call	pi_load pascal, 3, ds, offset aOp2b_pi
		call	pi_load pascal, 4, ds, offset aOp1b_pi
		call	pi_load pascal, 5, ds, offset aOp0b_pi
		call	pi_palette_apply pascal, 0
		push	4
		call	palette_black_in
		graph_showpage 0
		graph_accesspage 1
		xor	si, si
		mov	[bp+var_3], 0
		mov	di, 100
		mov	[bp+@@page], 0
		jmp	short loc_CDC4
; ---------------------------------------------------------------------------

loc_CD7A:
		mov	ax, si
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_CDB0
		cmp	[bp+var_3], 6
		jnb	short loc_CDB0
		pushd	38
		mov	al, [bp+var_3]
		mov	ah, 0
		push	ax
		call	pi_put_8
		inc	[bp+var_3]
		graph_accesspage [bp+@@page]
		mov	al, 1
		sub	al, [bp+@@page]
		mov	[bp+@@page], al
		graph_showpage al

loc_CDB0:
		mov	PaletteTone, di
		call	far ptr	palette_show
		add	di, 2
		call	@frame_delay$qi pascal, 1
		inc	si

loc_CDC4:
		cmp	si, 1Ch
		jl	short loc_CD7A
		mov	PaletteTone, 200
		call	far ptr	palette_show
		graph_showpage 0
		graph_accesspage al
		freePISlotLarge	0
		freePISlotLarge	1
		freePISlotLarge	2
		freePISlotLarge	3
		freePISlotLarge	4
		freePISlotLarge	5
		les	bx, _resident
		cmp	es:[bx+resident_t.demo_num], 0
		jnz	short loc_CE50
		call	snd_load pascal, ds, offset aOp_1, SND_LOAD_SONG
		kajacall	KAJA_SONG_PLAY

loc_CE50:
		graph_accesspage 1
		call	pi_load pascal, 0, ds, offset aOp1_pi_1
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		freePISlotLarge	0
		call	graph_copy_page pascal, 0
		xor	si, si
		jmp	short loc_CEAA
; ---------------------------------------------------------------------------

loc_CE8B:
		mov	bx, si
		imul	bx, size rgb_t
		mov	Palettes[bx].r, 255
		mov	bx, si
		imul	bx, size rgb_t
		mov	Palettes[bx].g, 255
		mov	bx, si
		imul	bx, size rgb_t
		mov	Palettes[bx].b, 255
		inc	si

loc_CEAA:
		cmp	si, COLOR_COUNT
		jl	short loc_CE8B
		call	far ptr	palette_show
		mov	PaletteTone, 100
		call	far ptr	palette_show
		xor	si, si
		mov	[bp+var_3], 240
		jmp	short loc_CEE8
; ---------------------------------------------------------------------------

loc_CEC7:
		mov	al, [bp+var_3]
		mov	Palettes[0 * size rgb_t].r, al
		mov	Palettes[0 * size rgb_t].g, al
		mov	Palettes[0 * size rgb_t].b, al
		call	far ptr	palette_show
		call	@frame_delay$qi pascal, 1
		inc	si
		mov	al, [bp+var_3]
		add	al, -16
		mov	[bp+var_3], al

loc_CEE8:
		cmp	si, 15
		jl	short loc_CEC7
		xor	si, si
		mov	[bp+var_3], 252
		jmp	short loc_CF4E
; ---------------------------------------------------------------------------

loc_CEF5:
		mov	di, 1
		jmp	short loc_CF34
; ---------------------------------------------------------------------------

loc_CEFA:
		mov	[bp+@@component], 0
		jmp	short loc_CF2D
; ---------------------------------------------------------------------------

loc_CF01:
		mov	bx, di
		imul	bx, size rgb_t
		add	bx, [bp+@@component]
		mov	al, _pi_headers._palette[bx]
		mov	bx, di
		imul	bx, size rgb_t
		add	bx, [bp+@@component]
		cmp	al, Palettes[bx].r
		jnb	short loc_CF2A
		mov	bx, di
		imul	bx, size rgb_t
		add	bx, [bp+@@component]
		mov	al, [bp+var_3]
		mov	Palettes[bx].r, al

loc_CF2A:
		inc	[bp+@@component]

loc_CF2D:
		cmp	[bp+@@component], size rgb_t
		jl	short loc_CF01
		inc	di

loc_CF34:
		cmp	di, COLOR_COUNT
		jl	short loc_CEFA
		call	far ptr	palette_show
		call	@frame_delay$qi pascal, 1
		inc	si
		mov	al, [bp+var_3]
		add	al, -4
		mov	[bp+var_3], al

loc_CF4E:
		cmp	si, 63
		jl	short loc_CEF5
		call	pi_palette_apply pascal, 0
		pop	di
		pop	si
		leave
		retn
_op_animate	endp

	_playchar_menu procdesc near
op_01_TEXT ends

; ===========================================================================

SHARED segment byte public 'CODE' use16
include th02/snd/snd.inc
	extern @FRAME_DELAY$QI:proc
	extern PI_PALETTE_APPLY:proc
	extern PI_PUT_8:proc
	extern PI_LOAD:proc
	extern @POLAR$QIII:proc
	extern SND_KAJA_INTERRUPT:proc
	extern SND_DELAY_UNTIL_MEASURE:proc
	extern SND_LOAD:proc
	extern _input_reset_sense:proc
	extern _input_sense:proc
	extern SND_SE_PLAY:proc
	extern _snd_se_update:proc
	extern _bgimage_snap:proc
	extern _bgimage_put:proc
	extern _bgimage_free:proc
	extern CDG_LOAD_ALL_NOALPHA:proc
	extern CDG_LOAD_ALL:proc
	extern CDG_FREE_ALL:proc
SHARED	ends

	.data

	; libs/master.lib/pal[data].asm
	extern PaletteTone:word

	; libs/master.lib/sin8[data].asm
	extern _SinTable8:word:256
	extern _CosTable8:word:256

include th04/zunsoft[data].asm

aGensou_scr	db 'GENSOU.SCR',0
aName		db 'name',0
aHi01_pi	db 'hi01.pi',0
aOp1_pi_0	db 'op1.pi',0
aOp_0		db 'op',0
aScnum_bft	db 'scnum.bft',0
aHi_m_bft	db 'hi_m.bft',0
		db    0
aSft1_cd2	db 'sft1.cd2',0
aSft2_cd2	db 'sft2.cd2',0
aCar_cd2	db 'car.cd2',0
aSl_cd2		db 'sl.cd2',0
aOp5b_pi	db 'op5b.pi',0
aOp4b_pi	db 'op4b.pi',0
aOp3b_pi	db 'op3b.pi',0
aOp2b_pi	db 'op2b.pi',0
aOp1b_pi	db 'op1b.pi',0
aOp0b_pi	db 'op0b.pi',0
aOp_1		db 'op',0
aOp1_pi_1	db 'op1.pi',0

	.data?

	extern _resident:dword

	; libs/master.lib/pal[bss].asm
	extern Palettes:byte:48

	; libs/master.lib/vs[bss].asm
	extern vsync_Count1:word

	; th02/formats/pi_slots[bss].asm
	extern _pi_buffers:dword
	extern _pi_headers:PiHeader

	; th02/hardware/input_sense[bss].asm
	extern _key_det:word

include th04/zunsoft[bss].asm
include th04/formats/scoredat_op[bss].asm
_rank	db ?
public _cleared_with, _extra_unlocked
_cleared_with label byte
_cleared_with_reimu 	db RANK_COUNT dup (?)
_cleared_with_marisa	db RANK_COUNT dup (?)
_extra_unlocked	db ?
		db 49 dup(?)

		end
