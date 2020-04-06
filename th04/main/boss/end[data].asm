public _BOSS_ITEM_DROPS
label _BOSS_ITEM_DROPS byte
		db  IT_POWER, IT_POWER, IT_BIGPOWER, IT_POWER, IT_POWER
	if GAME eq 4
		db  IT_POWER, IT_POWER,    IT_POWER, IT_POWER, IT_POWER
	endif
	db  IT_POINT, IT_POINT,    IT_POINT, IT_POINT, IT_POINT

public _boss_phase_timed_out
_boss_phase_timed_out	db 0
