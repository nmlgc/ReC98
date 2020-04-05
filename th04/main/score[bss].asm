; Scores and high scores are exclusively stored in little-endian BCD format
; internally. Points are added via adding regular integers to [score_delta],
; which is then taken "times 10" ([score_delta] += 1 → 10 more on-screen
; points).

public _CONTINUES_USED, _SCORE_LEBCD, _HISCORE_LEBCD
public _SCORE_DELTA, _SCORE_DELTA_FRAME

label _continues_used byte
_score_lebcd  	db	SCORE_DIGITS dup(?)
_hiscore_lebcd	db	SCORE_DIGITS dup(?)

if GAME eq 4
public _SCORE_UNUSED
_score_unused	db	?
endif
_score_delta      	dd	?
; Amount of points transferred from [score_delta] to [score_lebcd] this frame.
_score_delta_frame	dd	?
