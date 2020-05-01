public _gStage_1, _gFINAL_STAGE, _gEXTRA_STAGE
_gStage_1	db 0BCh, 0BDh, 0AAh, 0B0h, 0AEh, 2, 0A1h, 0
_gFINAL_STAGE	db 0AFh, 0B2h, 0B7h, 0AAh, 0B5h, 2, 0BCh, 0BDh,	0AAh, 0B0h, 0AEh, 0
_gEXTRA_STAGE	db 0AEh, 0C1h, 0BDh, 0BBh, 0AAh, 2, 0BCh, 0BDh,	0AAh, 0B0h, 0AEh, 0
gpHISCORE_ENTRY	db 40h,	41h, 42h, 43h, 44h, 45h, 46h, 47h, 0
gpEXTEND	db 48h,	49h, 4Ah, 4Bh, 4Ch, 0
gpBONUS		db 58h,	59h, 5Ah, 5Bh, 0
gpFULL_POWERUP	db 50h,	51h, 52h, 53h, 54h, 55h, 56h, 57h, 0
if GAME eq 5
gpDREAMBONUS_MAX db 65h, 66h, 67h, 68h,	69h, 6Ah, 6Bh, 6Ch, 6Dh, 6Eh, 0
endif
	align 2

public _POPUP_STRINGS
_POPUP_STRINGS	label dword
	dd gpHISCORE_ENTRY
	dd gpEXTEND
	dd gpBONUS
	dd gpFULL_POWERUP
if GAME eq 5
	dd gpDREAMBONUS_MAX
endif

public _popup_dissolve_sprite
_popup_dissolve_sprite	db 0
	evendata
