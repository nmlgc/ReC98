// Generic state variables
// -----------------------
// Really just freely usable memory shared between all bosses.

extern int boss_hp;
extern int boss_phase_frame;
extern int8_t boss_phase;
// -----------------------

static const int BOSS_HIT_INVINCIBILITY_FRAMES = 40;

// Processes collisions between the Orb and a boss, and the resulting
// invincibility of the latter… yeah, that's about the best summary for this
// function that does way too many things on the one hand, yet still leaves the
// caller to do way too much itself:
//
// • If a player shot hitbox is given, it also handles collisions between
//   player shots, regardless of invincibility. At the right and bottom edges,
//   the coordinates of that hitbox correspond to the top-left edge of the shot
//   sprite; use the shot_hitbox_t() macro to express their width and height in
//   a more visually correct way.
//
// • The hit testing against the Orb must be done before, with the result
//   being passed in [colliding_with_orb]. That parameter is what mainly
//   triggers the collision response of adding the [hit_score], decrementing
//   [hp], bouncing off the Orb in the opposite direction, and rendering the
//   invincibility flashing effect.
//
// • The caller is still responsible to increment [invincibility_frame]. This
//   function only reads from it or resets it to 0 once it reaches
//   BOSS_HIT_INVINCIBILITY_FRAMES.
//
// • [is_invincible] is always updated from this function, though.
//
// • Therefore, it only indirectly returns whether the boss was hit this
//   frame, via ([is_invincible] == true) && ([invincibility_frame] == 0).
//   (That fact makes [is_invincible] not quite as redundant as it might seem.)
//
// • Once [invincibility_frame] reaches BOSS_HIT_INVINCIBILITY_FRAMES, this
//   function resets the hardware palette to the [boss_palette] to end the
//   flash effect, as you would expect. However, this final reset actually
//   happens *regardless* of whether [is_invincible] is `true`, which can
//   definitely be classified as a bug. Refer to the bug explanation in the
//   function definition for more detail.
void boss_hit_update_and_render(
	int &invincibility_frame,
	bool16 &is_invincible,
	int &hp,
	const unsigned char invincibility_flash_colors[],
	unsigned char invincibility_flash_colors_count,
	int hit_score,
	bool colliding_with_orb,
	screen_x_t shot_hitbox_left = 0,
	screen_y_t shot_hitbox_top = 0,
	pixel_t shot_hitbox_w_minus_shot_w = 0,
	pixel_t shot_hitbox_h_minus_shot_h = 0
);

// Individual bosses
// -----------------

enum boss_id_t {
	BID_NONE,
	BID_SINGYOKU,
	BID_YUUGENMAGAN,
	BID_MIMA,
	BID_KIKURI,
	BID_ELIS,
	BID_SARIEL,
	BID_KONNGARA,

	_boss_id_t_FORCE_INT16 = 0x7FFF
};

static const pixel_t SINGYOKU_W = 96;
// Actually required publicly, as singyoku_defeat_animate_and_select_route()
// is part of the regular boss defeat translation unit.
static const pixel_t SINGYOKU_H = 96;

void singyoku_load(void);
void singyoku_main(void);
void singyoku_free(void);

// Makai
void yuugenmagan_load(void);
void yuugenmagan_main(void);
void yuugenmagan_free(void);

void elis_load(void);
void elis_main(void);
void elis_free(void);

void sariel_entrance(int8_t unused);
void sariel_load_and_init(void);
void sariel_main(void);
void sariel_free(void);

// Jigoku
void mima_load(void);
void mima_main(void);
void mima_free(void);

void kikuri_load(void);
void kikuri_main(void);
void kikuri_free(void);

void konngara_load_and_entrance(int8_t unused);
void konngara_init(void);
void konngara_main(void);
void konngara_free(void);
// -----------------
