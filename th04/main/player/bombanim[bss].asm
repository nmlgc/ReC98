BOMB_STAR_COUNT = 48
BOMB_STAR_W = 16
BOMB_STAR_H = 16

bomb_star_t struc
	BS_center	Point <?>
	BS_angle	db ?
	BS_speed	db ?
bomb_star_t ends

public _bomb_stars
_bomb_stars	bomb_star_t BOMB_STAR_COUNT dup (<?>)
	bomb_star_t <?>	; 1 additional unused one, for some reason?
