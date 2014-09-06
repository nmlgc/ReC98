ifdef MASTERMOD
	SUPERWAV_ARRAY_SIZE equ 96
else
	SUPERWAV_ARRAY_SIZE equ 64
endif
wave_address	dw	SUPERWAV_ARRAY_SIZE dup (?)
wave_shift	dw	SUPERWAV_ARRAY_SIZE dup (?)
wave_mask	dw	SUPERWAV_ARRAY_SIZE dup (?)
superwav_count	db	?
