WEIGHT_NORMAL = 0
WEIGHT_HEAVY = 1
WEIGHT_BOLD = 2
WEIGHT_BLACK = 3
WEIGHT_COUNT = 4

if (GAME eq 1)
	FX_CLEAR_BG  = 200h
	FX_UNDERLINE = 400h
	FX_REVERSE   = 800h
endif

if (GAME le 3)
	FX_WEIGHT_NORMAL = (WEIGHT_NORMAL shl 4)
	FX_WEIGHT_HEAVY =  (WEIGHT_HEAVY shl 4)
	FX_WEIGHT_BOLD =   (WEIGHT_BOLD shl 4)
	FX_WEIGHT_BLACK =  (WEIGHT_BLACK shl 4)
endif
