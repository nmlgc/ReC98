// Bosses
// ------
static const pixel_t BOSS_W = 64;
static const pixel_t BOSS_H = 64;
static const int BOSS_DEFEAT_INVINCIBILITY_FRAMES = 255;
#if (GAME == 5)
	static const unsigned long BOSS_BONUS_UNIT_VALUE = 1000;
#else
	static const unsigned int BOSS_BONUS_UNIT_VALUE = 1280;
#endif

static const pixel_t BOSS_HITBOX_DEFAULT_W = ((BOSS_W / 2) - (BOSS_W / 8));
static const pixel_t BOSS_HITBOX_DEFAULT_H = ((BOSS_W / 2) - (BOSS_W / 8));

// 16 bytes of globally additional state that bosses can use freely?
// Architecturally, that's a step back even compared to TH01.
extern unsigned char boss_statebyte[16];

struct boss_stuff_t {
	PlayfieldMotion pos;
	int hp;
	unsigned char sprite;
	unsigned char phase;
	int phase_frame;
	unsigned char damage_this_frame;
	unsigned char mode;
	// Used for both movement and bullet angles.
	unsigned char angle;
	union {
		// Most common interpretation during regular phases.
		unsigned char patterns_seen;

		// Hardcoded interpretation during the defeat phases.
		bool defeat_bonus;
	} phase_state;
	int phase_end_hp;
};

extern boss_stuff_t boss;
extern SPPoint boss_hitbox_radius;
extern bool boss_phase_timed_out;

void near boss_reset(void);

// Grants a score bonus of [units * BOSS_BONUS_UNIT_VALUE], rendered as one new
// point number popup per unit around the boss sprite.
void pascal near boss_score_bonus(unsigned int units);

// Callbacks. *_func() functions are "activated" by setting the regular
// function once the boss battle starts.
extern  farfunc_t_near boss_update;
extern nearfunc_t_near boss_fg_render;

// Also responsible to set [bg_render_bombing_func] to the
// [boss_bg_render_func]!
extern  farfunc_t_near boss_update_func;

extern nearfunc_t_near boss_bg_render_func;
extern nearfunc_t_near boss_fg_render_func;

// Does not include the *_bg_render() function, as this one always goes into a
// fixed, defined segment. With more decompilation progress, this will be true
// for these two functions as well, making this macro ultimately redundant.
#define BOSS_DEC(name) \
	void pascal  far name##_update(void); \
	void pascal near name##_fg_render(void);

// Collision detection
// -------------------

// Processes any collision of player shots (and, in TH05, the player itself)
// within a box with the given radius around the current position of the boss.
// Returns the total amount of damage dealt to it this frame, and plays the
// given sound effect if that amount is nonzero.
int pascal near boss_hittest_shots_damage(
	subpixel_t radius_x, subpixel_t radius_y, int se_on_hit
);

// Calls boss_hittest_shots_damage() with the boss hitbox radius and regular
// hit sound effect, and subtracts the result from the current boss HP.
// Returns `true` if that subtraction ended the current boss phase.
//
// TH04's version also takes ownership of [boss.phase_frame], incrementing it
// on every call.
bool near boss_hittest_shots(void);

// Calls boss_hittest_shots_damage() with the boss hitbox radius and
// invincibility sound effect, and does nothing with the returned damage.
//
// TH04's version also takes ownership of [boss.phase_frame], incrementing it
// on every call.
void near boss_hittest_shots_invincible(void);
// ------

// Explosions
// ----------

enum explosion_type_t {
	ET_NONE = -1,
	ET_CIRCLE = 0,
	ET_NW_SE = 1,
	ET_SW_NE = 2,
	ET_HORIZONTAL = 3,
	ET_VERTICAL = 4,

	_explosion_type_t_FORCE_INT16 = 0x7FFF
};

void pascal near boss_explode_small(explosion_type_t type);
#if (GAME == 5)
	void near boss_explode_big_circle(void);

	// Wrapper for easy compatibility with TH04 code.
	inline void boss_explode_big(explosion_type_t type) {
		boss_explode_big_circle();
	}
#else
	void pascal near boss_explode_big(explosion_type_t type);
#endif

void near explosions_small_update_and_render(void);
void near explosions_big_update_and_render(void);

void explosions_small_reset(void);
// ----------

void near boss_items_drop();

// Shows a small explosion with the given type, clears any bullets if the
// current phase wasn't timed out, and starts the next regular non-defeat
// phase, which will end upon reaching the given amount of HP. Does *not* reset
// [boss.phase_frame]!
void pascal near boss_phase_next(
	explosion_type_t explosion_type, int next_end_hp
);

// Defeat sequence
// ---------------

#ifdef OVERLAY_FADE_CELS
	enum boss_defeat_frames_t {
		// Small explosion phase
		BDF_SMALL_1 = 1,
		BDF_SMALL_2 = 16,
		BDF_BIG = 32,

		// Big explosion phase. And yes, the (hardcoded) amount of frames to
		// spend in this one dependes on the (hardcoded) length of the overlay
		// fade animation, which in turn depends on its (hardcoded) amount of
		// gaiji cels.
		BDF_DIALOG = (GAME == 5),
		BDF_FADEOUT = 416,
		BDF_NEXT_STAGE = (BDF_FADEOUT + OVERLAY_FADE_DURATION),
	};
#endif

// A dumb helper function…
#if (GAME == 5)
	inline void boss_phase_explode_big() {
		boss.phase++; // = PHASE_BOSS_EXPLODE_BIG
	}
#else
	inline void boss_phase_explode_big() {
		boss.phase = PHASE_EXPLODE_BIG;
	}
#endif

// …to abstract away the TH04/TH05 difference in *this* dumb helper function.
#define boss_defeat_explode_big(type, bonus_units) { \
	boss_explode_big(type); \
	boss_phase_explode_big(); \
	bullet_zap.active = boss.phase_state.defeat_bonus; \
	if(boss.phase_state.defeat_bonus) { \
		boss_score_bonus(bonus_units); \
	} \
	boss.sprite = PAT_ENEMY_KILL; \
	boss.phase_frame = 0; \
}

// Runs a frame of the boss defeat sequence.
//
// TH04 specialties:
// • Initializes Gengetsu at the end of the last defeat phase during the first
//   time it's shown on the Extra stage,
// • Takes ownership of [boss.phase_frame], incrementing it on every call.
//
// TH05 specialties:
// • Grants the given amount of score [bonus_units] during BDF_BIG if
//   [boss.phase_state.defeat_bonus] is `true`.
#if (GAME == 5)
	void pascal near boss_defeat_update(unsigned int bonus_units);
#else
	void near boss_defeat_update(void);
#endif
// ---------------
