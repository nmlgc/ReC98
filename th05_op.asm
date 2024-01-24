;
; +-------------------------------------------------------------------------+
; |   This file has been generated by The Interactive Disassembler (IDA)    |
; |        Copyright (c) 2009 by Hex-Rays, <support@hex-rays.com>           |
; +-------------------------------------------------------------------------+
;
; Input	MD5   :	F97D1B72F01476639E9D33E361F57330

; File Name   :	th05/OP.EXE
; Format      :	MS-DOS executable (EXE)
; Base Address:	0h Range: 0h-14240h Loaded length: 1280Ah
; Entry	Point :	0:0
; OS type	  :  MS	DOS
; Application type:  Executable	16bit

		.386
		.model use16 large _TEXT

BINARY = 'O'

include ReC98.inc
include th05/th05.inc
include th04/sprites/op_cdg.inc

op_01 group OP_SETUP_TEXT, op_01_TEXT, HI_VIEW_TEXT

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
	extern GRAPH_CLEAR:proc
	extern GRAPH_COPY_PAGE:proc
	extern PALETTE_SHOW:proc
	extern IRAND:proc
	extern HMEM_FREE:proc
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
		assume es:nothing, ss:nothing, ds:_DATA, fs:nothing, gs:nothing

include th04/zunsoft.asm
OP_SETUP_TEXT ends

op_01_TEXT segment byte public 'CODE' use16
include th04/formats/scoredat_decode_both.asm
include th04/formats/scoredat_encode.asm
include th05/formats/scoredat_recreate_op.asm
include th05/formats/scoredat_load_for.asm

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_CA1B	proc near

var_2		= word ptr -2
arg_0		= word ptr  4
@@y		= word ptr  6
arg_4		= word ptr  8

		enter	2, 0
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_0]
		mov	bx, di
		shl	bx, 3
		mov	al, _hi.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		cmp	ax, 10
		jl	short loc_CA5B
		lea	ax, [si-16]
		push	ax
		push	[bp+@@y]
		mov	bx, di
		shl	bx, 3
		mov	al, _hi.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		mov	bx, 10
		cwd
		idiv	bx
		push	ax
		call	super_put

loc_CA5B:
		push	si
		push	[bp+@@y]
		mov	bx, di
		shl	bx, 3
		mov	al, _hi.score.g_score[bx][SCORE_DIGITS - 1]
		mov	ah, 0
		add	ax, -gb_0_
		mov	bx, 10
		cwd
		idiv	bx
		push	dx
		call	super_put
		add	si, 16
		mov	[bp+var_2], 6
		jmp	short loc_CAA4
; ---------------------------------------------------------------------------

loc_CA83:
		push	si
		push	[bp+@@y]
		mov	bx, di
		shl	bx, 3
		add	bx, [bp+var_2]
		mov	al, _hi.score.g_score[bx]
		mov	ah, 0
		add	ax, -gb_0_
		push	ax
		call	super_put
		dec	[bp+var_2]
		add	si, 16

loc_CAA4:
		cmp	[bp+var_2], 0
		jge	short loc_CA83
		pop	di
		pop	si
		leave
		retn	6
sub_CA1B	endp

include th04/hiscore/hiscore_stage_put.asm

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_CB00	proc near

@@color		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6

		enter	2, 0
		push	si
		push	di
		cmp	[bp+arg_0], 0
		jnz	short loc_CB3A
		mov	bx, [bp+arg_2]
		cmp	bx, 3
		ja	short loc_CB33
		add	bx, bx
		jmp	cs:off_CBD4[bx]

loc_CB1B:
		mov	si, 8
		jmp	short loc_CB23
; ---------------------------------------------------------------------------

loc_CB20:
		mov	si, 328

loc_CB23:
		mov	di, 88
		jmp	short loc_CB33
; ---------------------------------------------------------------------------

loc_CB28:
		mov	si, 8
		jmp	short loc_CB30
; ---------------------------------------------------------------------------

loc_CB2D:
		mov	si, 328

loc_CB30:
		mov	di, 224

loc_CB33:
		mov	[bp+@@color], 7
		jmp	short loc_CB74
; ---------------------------------------------------------------------------

loc_CB3A:
		mov	bx, [bp+arg_2]
		cmp	bx, 3
		ja	short loc_CB6F
		add	bx, bx
		jmp	cs:off_CBCC[bx]

loc_CB49:
		mov	si, 8
		jmp	short loc_CB51
; ---------------------------------------------------------------------------

loc_CB4E:
		mov	si, 328

loc_CB51:
		mov	ax, [bp+arg_0]
		shl	ax, 4
		add	ax, 96
		jmp	short loc_CB6D
; ---------------------------------------------------------------------------

loc_CB5C:
		mov	si, 8
		jmp	short loc_CB64
; ---------------------------------------------------------------------------

loc_CB61:
		mov	si, 328

loc_CB64:
		mov	ax, [bp+arg_0]
		shl	ax, 4
		add	ax, 232

loc_CB6D:
		mov	di, ax

loc_CB6F:
		mov	[bp+@@color], 2

loc_CB74:
		lea	ax, [si+2]
		push	ax
		lea	ax, [di+2]
		push	ax
		push	GAIJI_W
		mov	ax, [bp+arg_0]
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi.score.g_name
		push	ds
		push	ax
		push	14
		call	graph_gaiji_puts
		push	si
		push	di
		push	GAIJI_W
		mov	ax, [bp+arg_0]
		imul	ax, (SCOREDAT_NAME_LEN + 1)
		add	ax, offset _hi.score.g_name
		push	ds
		push	ax
		push	[bp+@@color]
		call	graph_gaiji_puts
		lea	ax, [si+150]
		call	sub_CA1B pascal, ax, di, [bp+arg_0]
		lea	ax, [si+286]
		push	ax
		push	di
		mov	bx, [bp+arg_0]
		mov	al, _hi.score.g_stage[bx]
		mov	ah, 0
		push	ax
		call	hiscore_stage_put
		pop	di
		pop	si
		leave
		retn	4
sub_CB00	endp

; ---------------------------------------------------------------------------
off_CBCC	dw offset loc_CB49
		dw offset loc_CB4E
		dw offset loc_CB5C
		dw offset loc_CB61
off_CBD4	dw offset loc_CB1B
		dw offset loc_CB20
		dw offset loc_CB28
		dw offset loc_CB2D

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public _score_render
_score_render proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		graph_accesspage 1
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		graph_accesspage 0
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		xor	si, si
		jmp	short loc_CC27
; ---------------------------------------------------------------------------

loc_CC13:
		call	scoredat_load_for pascal, si
		xor	di, di
		jmp	short loc_CC21
; ---------------------------------------------------------------------------

loc_CC1B:
		push	si
		push	di
		call	sub_CB00
		inc	di

loc_CC21:
		cmp	di, 5
		jl	short loc_CC1B
		inc	si

loc_CC27:
		cmp	si, 4
		jl	short loc_CC13
		push	(496 shl 16) or 376
		mov	al, _rank
		mov	ah, 0
		add	ax, ax
		add	ax, 20
		push	ax
		call	super_put
		push	(560 shl 16) or 376
		mov	al, _rank
		mov	ah, 0
		add	ax, ax
		add	ax, 21
		push	ax
		call	super_put
		pop	di
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
		mov	al, es:[bx+resident_t.rank]
		mov	_rank, al
		call	pi_load pascal, 0, ds, offset aHi01_pi

loc_CC9F:
		call	_score_render
		call	palette_black_in pascal, 1

loc_CCA9:
		call	_input_reset_sense_held
		call	@frame_delay$qi pascal, 1
		test	_key_det.hi, high INPUT_OK
		jnz	short loc_CD17
		test	_key_det.lo, low INPUT_SHOT
		jnz	short loc_CD17
		test	_key_det.hi, high INPUT_CANCEL
		jnz	short loc_CD17
		test	_key_det.hi, high INPUT_OK
		jnz	short loc_CD17
		test	_key_det.lo, low INPUT_LEFT
		jz	short loc_CCF8
		cmp	_rank, RANK_EASY
		jz	short loc_CCF8
		dec	_rank
		mov	PaletteTone, 0
		call	far ptr	palette_show
		call	_score_render
		call	palette_black_in pascal, 1

loc_CCF8:
		test	_key_det.lo, low INPUT_RIGHT
		jz	short loc_CCA9
		cmp	_rank, RANK_EXTRA
		jnb	short loc_CCA9
		inc	_rank
		mov	PaletteTone, 0
		call	far ptr	palette_show
		jmp	short loc_CC9F
; ---------------------------------------------------------------------------

loc_CD17:
		kajacall	KAJA_SONG_FADE, 1
		call	palette_black_out pascal, 1
		call	pi_free pascal, 0
		graph_accesspage 1
		call	pi_load pascal, 0, ds, offset aOp1_pi_1
		call	pi_palette_apply pascal, 0
		call	pi_put_8 pascal, large 0, 0
		call	pi_free pascal, 0
		call	graph_copy_page pascal, 0
		call	palette_black_in pascal, 1

loc_CD64:
		call	_input_reset_sense_held
		call	@frame_delay$qi pascal, 1
		cmp	_key_det, INPUT_NONE
		jnz	short loc_CD64
		kajacall	KAJA_SONG_STOP
		call	snd_load pascal, ds, offset aOp_1, SND_LOAD_SONG
		kajacall	KAJA_SONG_PLAY
		pop	bp
		retn
_regist_view_menu endp
op_01_TEXT ends

HI_VIEW_TEXT segment byte public 'CODE' use16
	_cleardata_and_regist_view_sprite procdesc near
HI_VIEW_TEXT ends

; ===========================================================================

SHARED segment byte public 'CODE' use16
include th02/snd/snd.inc
	extern SND_SE_PLAY:proc
	extern _snd_se_update:proc
	extern _bgimage_snap:proc
	extern _bgimage_put:proc
	extern _bgimage_free:proc
	extern @POLAR$QIII:proc
	extern SND_LOAD:proc
	extern SND_KAJA_INTERRUPT:proc
	extern PI_LOAD:proc
	extern PI_PUT_8:proc
	extern PI_PALETTE_APPLY:proc
	extern PI_FREE:proc
	extern _input_reset_sense_held:proc
	extern SND_DELAY_UNTIL_MEASURE:proc
	extern @FRAME_DELAY$QI:proc
SHARED	ends

	.data

	; libs/master.lib/pal[data].asm
	extern PaletteTone:word

	; libs/master.lib/sin8[data].asm
	extern _SinTable8:word:256
	extern _CosTable8:word:256

include th04/zunsoft[data].asm
include th05/formats/scoredat_load_for[data].asm
aName		db 'name',0
aHi01_pi	db 'hi01.pi',0
aOp1_pi_1	db 'op1.pi',0
aOp_1		db 'op',0

	.data?

	extern _resident:dword

	; libs/master.lib/pal[bss].asm
	extern Palettes:byte:48

	; libs/master.lib/vs[bss].asm
	extern vsync_Count1:word

	; th02/hardware/input_sense[bss].asm
	extern _key_det:word

include th04/zunsoft[bss].asm
	extern _hi:scoredat_section_t
	extern _hi2:scoredat_section_t
	extern _rank:byte

		end
