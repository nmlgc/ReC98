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
// • If a player shot hitbox is given, it also handles collisions between
//   player shots, regardless of invincibility. At the right and bottom edges,
//   the coordinates of that hitbox correspond to the top-left edge of the shot
//   sprite; use the shot_hitbox_t() macro to express their width and height in
//   a more visually correct way.
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
// Once the flash effect is done, the entire palette is reset to the
// [boss_palette].
void boss_hit_update_and_render(
	int &invincibility_frame,
	bool16 &is_invincible,
	int &hp,
	const unsigned char invincibility_flash_colors[],
	unsigned char invincibility_flash_colors_count,
	int hit_score,
	farfunc_t_far hit_callback,
	bool colliding_with_orb,
	screen_x_t shot_hitbox_left = 0,
	screen_y_t shot_hitbox_top = 0,
	pixel_t shot_hitbox_w_minus_shot_w = 0,
	pixel_t shot_hitbox_h_minus_shot_h = 0
);

// Palette to fade to after the white boss defeat flash.
extern Palette4 boss_post_defeat_palette;

// Individual bosses
// -----------------

static const pixel_t SINGYOKU_W = 96;
// Actually required publically, as singyoku_defeat_animate_and_select_route()
// is part of the regular boss defeat translation unit.
static const pixel_t SINGYOKU_H = 96;

void singyoku_load(void);
void singyoku_main(void);
void singyoku_free(void);

// Makai
void yuugenmagan_load(void);

void elis_load(void);
void elis_main(void);
void elis_free(void);

void sariel_entrance(int8_t unused);
void sariel_load_and_init(void);

// Jigoku
void mima_load(void);
void mima_free(void);

void kikuri_load(void);
void kikuri_free(void);

void konngara_load_and_entrance(int8_t unused);
void konngara_init(void);
void konngara_main(void);
void konngara_free(void);
// -----------------
