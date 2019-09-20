GAME = 1

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
