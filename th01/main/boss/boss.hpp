/// Generic state variables
/// -----------------------
/// Really just freely usable memory shared between all bosses.

extern int boss_hp;
extern int boss_phase_frame;
extern int8_t boss_phase;
/// -----------------------

// No-op function for callbacks.
void pascal boss_nop(void);

static const int BOSS_HIT_INVINCIBILITY_FRAMES = 40;

// Processes collisions between the Orb and a boss, and the resulting
// invincibility of the latter… yeah, that's about the best summary for this
// function that does way too many things:
// • It also handles collisions between *player shots* and the given hitbox,
//   regardless of invincibility.
// • The hit testing against the Orb must be done before, with the result
//   being passed in [colliding_with_orb]. That parameter is what mainly
//   triggers the collision response of adding the [hit_score], decrementing
//   [hp], bouncing off the Orb in the opposite direction, calling
//   [hit_callback], and rendering the invincibility flashing effect.
// • The caller is still responsible to increment [invincibility_frame]. This
//   function only reads from it or resets it to 0.
// • [is_invincible] is always updated from this function, though.
// • Therefore, it only indirectly returns whether the boss was hit this
//   frame, via ([is_invincible] == true) && ([invincibility_frame] == 0).
//   (That fact makes [is_invincible] not quite as redundant as it might seem.)
void boss_hit_update_and_render(
	int &invincibility_frame,
	bool16 &is_invincible,
	int &hp,
	const unsigned char invincibility_flash_colors[],
	unsigned char invincibility_flash_colors_count,
	int hit_score,
	farfunc_t_far hit_callback,
	bool colliding_with_orb,
	screen_x_t hitbox_left,
	screen_y_t hitbox_top,
	pixel_t hitbox_w,
	pixel_t hitbox_h
);

// Individual bosses
// -----------------

// Makai
void sariel_load_and_entrance(int8_t unused);

// Jigoku
void konngara_load_and_entrance(int8_t unused);
void konngara_init(void);
void konngara_main(void);
void konngara_free(void);
// -----------------
