GAME = 1

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
	mode db ?	; 0 = regular, 1 = test, 3 = debug
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

; Text
; ----
FX_CLEAR_BG 	= 200h
FX_UNDERLINE	= 400h
FX_REVERSE  	= 800h
; ----

; Player
; ------
MISS_INVINCIBILITY_FRAMES = 150
; ------

; Bombs
; -----
BOMB_INVINCIBILITY_FRAMES_AFTER = 100
; -----
