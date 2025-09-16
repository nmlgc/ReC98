include th05/chars.inc
include th04/shared.inc
include th04/gaiji/gaiji.inc
include th02/v_colors.inc

resident_t	struc
	id	db 10 dup(?)
	zunsoft_shown	db ?
		db ?
	RESIDENT_unknown	db ?
	credit_lives	db ?
	credit_bombs	db ?
	cfg_lives	db ?
	cfg_bombs	db ?
	rank	db ?
	bgm_mode	db ?
	stage	db ?
	playchar	db ?
	se_mode	db ?
	turbo_mode	db ?
	debug_mode	db ?	; `debug` would clash with master.lib's `debug` macro
	debug_stage	db ?
	debug_power	db ?
	end_sequence	db ?
	miss_count	db ?
	bombs_used	db ?
	demo_stage	db ?
		db ?
	demo_num	db  ?
	score_last	db SCORE_DIGITS dup (?)
	rand	dd ?
	std_frames	dw ?
	items_spawned	dw ?
	items_collected	dw ?
	point_items_collected	dw ?
	max_valued_point_items_collected	dw ?
	enemies_gone	dw ?
	enemies_killed	dw ?
	graze	dw ?
	slow_frames	dd ?
	frames	dd ?
	score_highest	db SCORE_DIGITS dup (?)
	stage_score	db MAIN_STAGE_COUNT dup(SCORE_DIGITS dup (?))
		dd	?
resident_t ends

; Shot cycle bitflags
SC_1X = 08h ; Triggered 1× per cycle
SC_2X = 02h ; Triggered 2× per cycle
SC_3X = 01h ; Triggered 3× per cycle
SC_6X = 04h ; Triggered 6× per cycle

POINT_ITEMS_MAX = 999
