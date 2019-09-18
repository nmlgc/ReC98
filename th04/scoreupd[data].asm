public _FIVE_DIGIT_POWERS_OF_10
_FIVE_DIGIT_POWERS_OF_10	dw 10000, 1000, 100, 10, 1

if GAME eq 4
; Temporary BCD conversion buffer. TH05 just uses _hud_gaiji_row instead.
public _TEMP_LEBCD
_temp_lebcd	db	SCORE_DIGITS dup(0)
endif
