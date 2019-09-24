include th02/player/player.inc
PLAYER_OPTION_W = 16
PLAYER_OPTION_H = 16

MISS_ANIM_FRAMES = 32
MISS_ANIM_FLASH_AT = 28
MISS_ANIM_EXPLODE_UNTIL = 31

MISS_EXPLOSION_COUNT = 8
MISS_EXPLOSION_W = 48
MISS_EXPLOSION_H = 48
MISS_EXPLOSION_RADIUS_VELOCITY = (7 shl 4)
MISS_EXPLOSION_ANGLE_VELOCITY = 8

MISS_EXPLOSION_CLIP macro clip_label
	cmp	_drawpoint.y, ((PLAYFIELD_TOP - (MISS_EXPLOSION_H / 2)) shl 4)
	jl	short clip_label
	; Yes, the next two are incorrect
	cmp	_drawpoint.y, ((PLAYFIELD_BOTTOM - 8) shl 4)
	jge	short clip_label
	cmp	_drawpoint.x, ((PLAYFIELD_LEFT - 40) shl 4)
	jl	short clip_label
	cmp	_drawpoint.x, ((PLAYFIELD_RIGHT - (MISS_EXPLOSION_W / 2)) shl 4)
	jge	short clip_label
endm

MISS_INVINCIBILITY_FRAMES = 192
