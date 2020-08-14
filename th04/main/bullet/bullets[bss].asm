pellet_render_t struc
	PRT_left label word
	PRB_vram_offset label word
		dw ?
	PRT_top label word
	PRB_sprite_offset label word
		dw ?
pellet_render_t ends

if GAME eq 5
	PELLET_COUNT = 180
	BULLET16_COUNT = 220
else
	PELLET_COUNT = 240
	BULLET16_COUNT = 200
endif

BULLET_COUNT = (PELLET_COUNT + BULLET16_COUNT)

public _bullets, _pellets, _bullets16, _pellets_render
_bullets label bullet_t
_pellets	bullet_t PELLET_COUNT dup(<?>)
_bullets16	bullet_t BULLET16_COUNT dup(<?>)
_pellets_render	pellet_render_t PELLET_COUNT dup(<?>)
