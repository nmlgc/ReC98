; Scores and high scores are exclusively stored in little-endian BCD format
; internally. Points are added via adding regular integers to [score_delta],
; which is then taken "times 10" ([score_delta] += 1 → 10 more on-screen
; points).

SCORE_DIGITS = 8
; Also ignoring the last digit. (= 61,110 points)
SCORE_DELTA_FRAME_LIMIT = 6111

public _continues_used, _score_lebcd, _hiscore_lebcd
public _score_delta, _score_delta_frame

label _continues_used byte
_score_lebcd  	db	SCORE_DIGITS dup(?)
_hiscore_lebcd	db	SCORE_DIGITS dup(?)

if GAME eq 4
_score_unused	db	?
endif
_score_delta      	dd	?
; Amount of points transferred from [score_delta] to [score_lebcd] this frame.
_score_delta_frame	dd	?
