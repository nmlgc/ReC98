GAME = 3
include defconv.inc

PLAYER_COUNT = 2

include th03/mem.inc
include th03/gaiji/gaiji.inc
include th03/math/randring.inc
include th03/hardware/input.inc
include th03/chars/chars.inc
include th03/formats/cfg.inc
include th02/score.inc

KM_KEY_KEY = 0
KM_JOY_KEY = 1
KM_KEY_JOY = 2

VS_1P_CPU = 0
VS_1P_2P = 1
VS_CPU_CPU = 2

GM_NONE = 0
GM_STORY = 1
GM_DEMO = 7Fh
GM_VS = 80h

STAGE_NONE = -1
STAGE_ALL = 99
STAGE_COUNT = 9

CREDIT_LIVES = 2

DEMO_COUNT = 4

resident_t	struc
	id	db 11 dup(?)
	rank	db ?
	RESIDENT_playchar_paletted	db PLAYER_COUNT dup(?)
	RESIDENT_is_cpu	db PLAYER_COUNT dup(?)
	rand	dd ?
		db ?
	bgm_mode	db ?
	key_mode	db ?
	pid_winner	db ?
	score_last	db PLAYER_COUNT dup(SCORE_DIGITS dup(?))
	game_mode	db ?
	story_opponents	db STAGE_COUNT dup (?)
		db ?
	story_stage	db ?
	story_lives	db ?
	show_score_menu	db ?
	rem_credits	db ?
	op_skip_animation	db ?
	skill	db ?
	demo_num	db ?
resident_t	ends
