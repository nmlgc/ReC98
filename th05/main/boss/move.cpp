static const int TOWARDS_FRACTION = 16; // higher = slower

inline int towards(int val, int speed = 1) {
	return (val / (TOWARDS_FRACTION / speed));
}

bool pascal near boss_flystep_towards(subpixel_t target_x, subpixel_t target_y)
{
	int reached_dimensions = 0;
	subpixel_t dist;

	dist = (target_x - boss.pos.cur.x.v);
	/**/ if(towards(dist)    != 0) { boss.pos.cur.x.v += towards(dist); }
	else if(towards(dist, 4) != 0) { boss.pos.cur.x.v += towards(dist, 4); }
	else {
		boss.pos.cur.x.v = target_x;
		reached_dimensions++;
	}
	if(dist < 0) {
		boss.sprite = boss_sprite_left;
	} else {
		boss.sprite = boss_sprite_right;
	}

	dist = (target_y - boss.pos.cur.y.v);
	/**/ if(towards(dist)    != 0) { boss.pos.cur.y.v += towards(dist); }
	else if(towards(dist, 8) != 0) { boss.pos.cur.y.v += towards(dist, 8); }
	else {
		boss.pos.cur.y.v = target_y;
		reached_dimensions++;
	}

	if(reached_dimensions != 2) {
		return false;
	}
	boss.sprite = boss_sprite_stay;
	return true;
}
