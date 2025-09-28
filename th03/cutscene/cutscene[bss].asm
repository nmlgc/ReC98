NAME_LEN = 6
NAME_KANJI_LEN = (NAME_LEN / 2)

public _script, _fast_forward
_script	dd ?
_fast_forward	db ?
	evendata

public _cursor, _text_interval, _text_col, _text_fx
public _script_param_number_default
_cursor                     	Point <?>
_text_interval              	dw ?
_text_col                   	db ?
_text_fx                    	db ?
_script_param_number_default	dw ?
