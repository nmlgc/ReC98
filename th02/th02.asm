GAME = 2
include defconv_c.inc
include th02/hardware/input.inc

kajacall	macro func, param := <0>
	call	_snd_kaja_interrupt pascal, (func shl 8) or (param and 0ffh)
endm

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
	perf db ?
	unused_3 db ?
	shottype db ?
	demo_num db ?
	skill dw ?
	unused_4 dw ?
	score_highest dd ?
mikoconfig_t	ends
