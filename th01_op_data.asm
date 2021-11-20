; Remaining non-literal data defined in segment #1 of TH01's OP.EXE

	.386
	.model use16 large

	.data

include pc98.inc
include th01/th01.inc
include th01/formats/cfg.inc

public _opts, _mode
_opts	cfg_options_t <CFG_RANK_DEFAULT, CFG_BGM_MODE_DEFAULT, CFG_BOMBS_DEFAULT, CFG_LIVES_EXTRA_DEFAULT>
_mode	db 0
public _menu_sel, _option_rows
public _input_left, _input_right, _input_ok, _input_shot, _input_cancel
public byte_1232A, byte_1232C, byte_1232D, byte_1232E, _quit_flag, dword_12330
public _main_input_prev, _option_input_prev
_menu_sel	db 0
_input_left	db 0
_input_ok	db 0
_input_shot	db 0
_input_cancel	db 0
byte_1232A	db 0
_input_right	db 0
byte_1232C	db 0
byte_1232D	db 0
byte_1232E	db 0
_quit_flag	db 0
dword_12330	dd 0
_main_input_prev	dw 2 dup (0)
_option_rows	db 3
_option_input_prev	dw 2 dup (0)
public _WHITELINES_DRAWN_AT
_WHITELINES_DRAWN_AT	db (RES_Y - 1) dup(0)

	end
