static const unsigned int MIDBOSS_BONUS_UNIT_VALUE = 1280;

typedef struct {
	PlayfieldMotion pos;
	unsigned int frames_until;
	int hp;
	unsigned char sprite;
	unsigned char phase;
	int phase_frame;
	// Treated as a bool in TH04
	unsigned char damage_this_frame;
	unsigned char angle;
} midboss_stuff_t;

extern midboss_stuff_t midboss;

// Prevents stage enemies from being spawned if `true`.
extern bool midboss_active;

// Grants a score bonus of [units * MIDBOSS_BONUS_UNIT_VALUE], rendered as one
// new point number popup per unit around the midboss sprite.
void pascal near midboss_score_bonus(unsigned int units);

// Callbacks
extern  farfunc_t_near midboss_update_func;
extern nearfunc_t_near midboss_render_func;

void midboss_reset(void);

// Updates the defeat animation during PHASE_EXPLODE_BIG, and resets the boss
// during any other phase. TH04's version also takes ownership of
// [midboss.phase_frame], incrementing it every frame.
void near midboss_defeat_update(void);

#define MIDBOSS_DEC(stage) \
	void pascal  far midboss##stage##_update(void); \
	void pascal near midboss##stage##_render(void);

// "midbosses" unfortunately has 9 characters and therefore won't work as a
// 8.3 filename. However, since these have no names anyway, we can just
// declare all of them here.
MIDBOSS_DEC(1);
MIDBOSS_DEC(2);
MIDBOSS_DEC(3);
MIDBOSS_DEC(4);
MIDBOSS_DEC(5);
MIDBOSS_DEC(x);
