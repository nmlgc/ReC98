; Changed from their TH03 values.
INPUT_NONE       = 0
INPUT_UP         = 1
INPUT_DOWN       = 2
INPUT_LEFT       = 4
INPUT_RIGHT      = 8
INPUT_BOMB       = 10h
INPUT_SHOT       = 20h
INPUT_UP_LEFT    = 100h
INPUT_UP_RIGHT   = 200h
INPUT_DOWN_LEFT  = 400h
INPUT_DOWN_RIGHT = 800h
INPUT_CANCEL     = 1000h
INPUT_OK         = 2000h
INPUT_Q          = 4000h

INPUT_MOVEMENT   = \
	INPUT_UP or INPUT_DOWN or INPUT_LEFT or INPUT_RIGHT or \
	INPUT_UP_LEFT or INPUT_UP_RIGHT or INPUT_DOWN_LEFT or INPUT_DOWN_RIGHT

if GAME eq 5
input_reset_sense_interface	equ <_input_reset_sense_held>
else
input_reset_sense_interface	equ <_input_reset_sense>
endif

; move_ret_t
MOVE_INVALID = 0
MOVE_VALID = 1
MOVE_NOINPUT = 2
