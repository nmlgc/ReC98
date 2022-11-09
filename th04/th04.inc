GAME = 4
include th04/chars.inc
include th04/mem.inc
include th04/shared.inc
include th04/gaiji/gaiji.inc
include th02/v_colors.inc

resident_t struc
	id	db 11 dup(?)
	rem_lives	db ?
	credit_lives	db ?
	rem_bombs	db ?
	credit_bombs	db ?
	rank	db ?
	bgm_mode	db ?
	stage	db ?
	playchar_ascii	db ?
	stage_ascii	db ?
	rand	dd ?
	se_mode	db ?
	shottype	db ?
	debug_mode	db ?	; `debug` would clash with master.lib's `debug` macro
		dw ?
	score_last	db SCORE_DIGITS dup(?)
	end_type_ascii	db ?
	std_frames	dw ?
	items_spawned	dw ?
	items_collected	dw ?
	point_items_collected	dw ?
	max_valued_point_items_collected	dw ?
	end_sequence	db ?
	miss_count	db ?
	bombs_used	db ?
		db ?
	enemies_gone	dw ?
	enemies_killed	dw ?
	graze	dw ?
	cfg_lives	db ?
	cfg_bombs	db ?
	demo_stage	db ?
		db ?
	demo_num	db ?
		db ?
	slow_frames	dd ?
	frames	dd ?
	zunsoft_shown	db ?
	turbo_mode	db ?
		db 54 dup(?)
resident_t ends

playchar_speed_aligned = 4 shl 4
playchar_speed_diagonal = 3 shl 4

BOMB_INVINCIBILITY_FRAMES = 255
