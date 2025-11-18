enum fireball_variant_t {
	FV_BLUE = 0,
	FV_RED = 1,

	_fireball_variant_t_FORCE_UINT8 = 0xFF
};

// Spawns a fireball at [efe_p.efe]'s current position and playfield, aimed at
// a random position at the top of the other playfield.
void fireballs_add(void);

void fireballs_update(void);
