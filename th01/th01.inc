GAME = 1

RANK_NORMAL = 1 ; Temporary workaround...

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

SCENE_COUNT = 4

reiidenconfig_t struc ; (sizeof=0x4B)
	id db 13 dup(?)	; = "ReiidenConfig"
		db ?
	rank db ?
	bgm_mode db ?	; 0 = off, 1 = FM
	bombs db ?
	start_lives_extra db ?	; Add 2 for the actual number of lives
	end_flag db ?
	unused_1 db ?
	route db ?	; 0 = ñÇäE, 1 = ínçñ
	rem_lives db ?
	snd_need_init db ?
	unused_2 db ?
	debug_mode db ?
	bullet_speed dw ?
	rand  dd ?
	score dd ?
	continues_total dd ?
	continues_per_scene dw 4 dup(?)
	bonus_per_stage dd 4 dup(?)	; of the current scene
	stage dw ?
	hiscore dd ?
	score_highest dd ?	; among all continues
	p_value dw ?
reiidenconfig_t ends

; VRAM colors
; -----------
V_WHITE = 7
; -----------
