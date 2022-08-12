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
public _rank, _bgm_mode, _bombs, _lives_extra, _stage_num, byte_34A35
_rank	db CFG_RANK_DEFAULT
_bgm_mode	db CFG_BGM_MODE_DEFAULT
_bombs	db CFG_BOMBS_DEFAULT
_lives_extra	db CFG_LIVES_EXTRA_DEFAULT
_stage_num	db 0
byte_34A35	db 0
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
public _bomb_doubletap_frames, word_34A70, _test_damage, word_34A74
public _player_invincible, _orb_velocity_x, _lives, _stage_cleared, _orb_rotation_frame
_bomb_doubletap_frames	dw 0
word_34A70	dw 0
_test_damage	dw 0
word_34A74	dw 0
	dw 0
_player_invincible	dw 0
	dw 0
_orb_velocity_x	dw 0
_orb_rotation_frame	dw 0
_lives	dw 4
_stage_cleared	dw 0
public _cardcombo_cur, _orb_in_portal, _cardcombo_max, word_34A8A, word_34A8C
_cardcombo_cur	dw 0
_orb_in_portal	dw 0
_cardcombo_max	dw 0
word_34A8A	dw 1
word_34A8C	dw 1
public _orb_prev_left, _orb_prev_top, _orb_frames_outside_portal
public _orb_velocity_y, _orb_force
_orb_prev_left	dw ORB_LEFT_START
_orb_prev_top 	dw  ORB_TOP_START
_orb_frames_outside_portal	dw 0
_orb_velocity_y	dq 0.0
_orb_force	dq 0.0
public _ptn_slot_stg_has_reduced_sprites, _bomb_palette_flash_peak_
_ptn_slot_stg_has_reduced_sprites	db 0
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
public byte_34AD5, byte_34ADF
byte_34AD5	db 10 dup (0)
byte_34ADF	db 0
aEasy	db 'EASY',0
aNormal	db 'NORMAL',0
aHard	db 'HARD',0
aLunatic	db 'LUNATIC'

	end
