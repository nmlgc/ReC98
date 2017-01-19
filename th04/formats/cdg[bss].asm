; Global CDG data.

CDG_SLOT_COUNT = 64

; CDGHeader cdg_slots[CDG_SLOT_COUNT]
public _cdg_slots
_cdg_slots	CDGSlot CDG_SLOT_COUNT dup(<?>)
cdg_images_to_load db ?
	db ?	; word alignment
