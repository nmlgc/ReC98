include th03/common.inc
include th03/math/randring.inc
include th03/hardware/input.inc
include th03/chars.inc
include th02/score.inc
include th02/v_colors.inc

SND_BGM_OFF = 0
SND_BGM_FM = 1
SND_BGM_MIDI = 2

KM_KEY_KEY = 0
KM_JOY_KEY = 1
KM_KEY_JOY = 2

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
	op_animation_fast	db ?
	skill	db ?
	demo_num	db ?
resident_t	ends
