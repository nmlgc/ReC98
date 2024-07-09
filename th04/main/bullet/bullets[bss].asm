pellet_render_t struc
	PRT_left label word
	PRB_vram_offset label word
		dw ?
	PRT_top label word
	PRB_sprite_offset label word
		dw ?
pellet_render_t ends

public _bullets, _pellets, _bullets16, _pellets_render
_bullets label bullet_t
_pellets	bullet_t PELLET_COUNT dup(<?>)
_bullets16	bullet_t BULLET16_COUNT dup(<?>)
_pellets_render	pellet_render_t PELLET_COUNT dup(<?>)
