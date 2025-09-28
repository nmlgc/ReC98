include th02/hardware/input.inc
include th02/math/randring.inc
include th02/gaiji/gaiji.inc
include th02/score.inc
include th02/v_colors.inc

kajacall	macro func, param := <0>
	call	_snd_kaja_interrupt pascal, (func shl 8) or (param and 0ffh)
endm

SHOTTYPE_COUNT = 3

mikoconfig_t	struc
	id db 10 dup(?)	; = "MIKOConfig"
		db ?
	stage db ?
	debug_flag db ?
		db ?
	score dd ?
	continues_used dw ?
	rem_bombs db ?
	rem_lives db ?
	rank db ?
	start_power db ?
	bgm_mode db ?
	start_bombs db ?
	start_lives db ?
		db ?
	frame dd ?
	unused_1 dw ?
	unused_2 db ?
	main_retval db ?
	reduce_effects db ?
	unused_3 db ?
	shottype db ?
	demo_num db ?
	skill dw ?
	unused_4 dw ?
	score_highest dd ?
mikoconfig_t	ends

; Player
; ------
CONTINUE_INVINCIBILITY_FRAMES = 200
; ------

; Bosses
; ------
BOSS_DEFEAT_INVINCIBILITY_FRAMES = 200
; ------
