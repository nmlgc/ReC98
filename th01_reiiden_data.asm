; Remaining non-literal data defined in segment #1 of TH01's REIIDEN.EXE

	.386
	.model use16 large

include pc98.inc
include th01/th01.inc
include th01/formats/cfg.inc

	.data

; Not *really* a cfg_options_t, since you'd expect that structure to contain
; the immutable contents of REIIDEN.CFG. However, [bombs] is in fact the
; *current* bomb count, and the .CFG value is saved to [credit_bombs]...
public _rank, _bgm_mode, _bombs, _lives_extra, _stage_num
public _bgm_change_blocked
_rank	db CFG_RANK_DEFAULT
_bgm_mode	db CFG_BGM_MODE_DEFAULT
_bombs	db CFG_BOMBS_DEFAULT
_lives_extra	db CFG_LIVES_EXTRA_DEFAULT
_stage_num	db 0
_bgm_change_blocked	db 0
	db 0
public _RANKS, _first_stage_in_scene, _timer_initialized
_RANKS label dword
	dd aEasy		; "EASY"
	dd aNormal		; "NORMAL"
	dd aHard		; "HARD"
	dd aLunatic		; "LUNATIC"
_timer_initialized	db 0
	db 0
_first_stage_in_scene	db 1
	db 0

public _input_up, _input_down, _input_lr, _input_shot, _input_strike, _input_ok
public _input_bomb, _player_is_hit, _paused, _input_mem_enter, _input_mem_leave
_input_lr	db 0
_input_mem_enter	db 0
_input_mem_leave	db 0
_input_shot	db 0
_player_is_hit	db 0
_input_bomb	db 0
_paused	db 0
_input_ok	db 0
_input_strike	db 0
_input_up	db 0
_input_down	db 0
	db 0
public _player_deflecting, _bomb_damaging, _player_sliding
_player_deflecting	db 0
_bomb_damaging	db 0
_player_sliding	db 0
public _score, _score_bonus, _bomb_frames, _continues_total, _mode_test
_score	dd 0
_score_bonus	dd 0
_bomb_frames	dd 0
_continues_total	dd 0
	dw 0
_mode_test	dw 0
public _bomb_doubletap_frames, _bomb_doubletap_frames_unused, _test_damage
public _unused_5, _player_invincible, _orb_velocity_x, _lives, _stage_cleared
public _orb_rotation_frame
_bomb_doubletap_frames	dw 0
_bomb_doubletap_frames_unused	dw 0
_test_damage	dw 0
_unused_5	dw 0
	dw 0
_player_invincible	dw 0
	dw 0
_orb_velocity_x	dw 0
_orb_rotation_frame	dw 0
_lives	dw 4
_stage_cleared	dw 0
public _cardcombo_cur, _orb_in_portal, _cardcombo_max, _extend_next
public _unnecessary_copy_of_the_initial_
_cardcombo_cur	dw 0
_orb_in_portal	dw 0
_cardcombo_max	dw 0
_extend_next	dw 1
_unnecessary_copy_of_the_initial_	dw 1
public _orb_prev_left, _orb_prev_top, _orb_frames_outside_portal
public _orb_velocity_y, _orb_force
_orb_prev_left	dw ORB_LEFT_START
_orb_prev_top 	dw  ORB_TOP_START
_orb_frames_outside_portal	dw 0
_orb_velocity_y	dq 0.0
_orb_force	dq 0.0
public _ptn_slot_stg, _bomb_palette_flash_peak_
_ptn_slot_stg	db 0
label _bomb_palette_flash_peak_ byte
	db 0Fh, 0Fh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Fh, 0Fh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 0Dh, 0Dh, 0Fh
	db 06h, 06h, 0Fh
public _PLAYER_GAMEOVER_EFFECT_CLIPPED, _boss_id
_PLAYER_GAMEOVER_EFFECT_CLIPPED	dw 5 dup (0)
_boss_id	db 0
aEasy	db 'EASY',0
aNormal	db 'NORMAL',0
aHard	db 'HARD',0
aLunatic	db 'LUNATIC'

	end
