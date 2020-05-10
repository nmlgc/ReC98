public _input_up, _input_down, _input_lr, _input_shot, _input_strike, _input_ok
public _input_bomb, _done, _paused, _input_mem_enter, _input_mem_leave
_input_lr	db 0
_input_mem_enter	db 0
_input_mem_leave	db 0
_input_shot	db 0
_done	db 0
_input_bomb	db 0
_paused	db 0
_input_ok	db 0
_input_strike	db 0
_input_up	db 0
_input_down	db 0

INPUT_RIGHT = 01h
INPUT_LEFT = 02h
BOMB_DOUBLETAP_WINDOW = 20
