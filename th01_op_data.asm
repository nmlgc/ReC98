; Remaining non-literal data defined in segment #1 of TH01's OP.EXE

	.386
	.model use16 large

	.data

include pc98.inc
include th01/th01.inc
include th01/formats/cfg.inc

public _opts, _debug_mode
_opts	cfg_options_t <CFG_RANK_DEFAULT, CFG_BGM_MODE_DEFAULT, CFG_BOMBS_DEFAULT, CFG_LIVES_EXTRA_DEFAULT>
_debug_mode	db 0
public _menu_sel, _option_choice_max
public _input_left, _input_right, _input_ok, _input_shot, _input_cancel
public _menu_id, _quit, _unused_con_arg_0, _unused_con_arg_2, _unused_con_arg_1
public _free_resident_structure_on_title, _main_input_prev, _option_input_prev
_menu_sel	db 0
_input_left	db 0
_input_ok	db 0
_input_shot	db 0
_input_cancel	db 0
_menu_id	db 0
_input_right	db 0
_quit	db 0
_unused_con_arg_0	db 0
_unused_con_arg_2	db 0
_free_resident_structure_on_title	db 0
_unused_con_arg_1	dd 0
_main_input_prev	dw 2 dup (0)
_option_choice_max	db 3
_option_input_prev	dw 2 dup (0)
public _WHITELINES_DRAWN_AT
_WHITELINES_DRAWN_AT	db (RES_Y - 1) dup(0)

	end
