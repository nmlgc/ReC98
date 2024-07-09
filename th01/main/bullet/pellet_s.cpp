void pellet_speed_lower(pellet_speed_t max, pellet_speed_t negative_delta)
{
	if(resident->pellet_speed > max) {
		resident->pellet_speed = max;
	} else {
		resident->pellet_speed += negative_delta;
	}
	if(resident->pellet_speed < PELLET_SPEED_LOWER_MIN) {
		resident->pellet_speed = PELLET_SPEED_LOWER_MIN;
	}
}

void pellet_speed_raise(pellet_speed_t delta)
{
	resident->pellet_speed += delta;
	if(resident->pellet_speed > PELLET_SPEED_RAISE_MAX) {
		resident->pellet_speed = PELLET_SPEED_RAISE_MAX;
	}
}
