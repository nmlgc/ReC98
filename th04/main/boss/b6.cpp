// These indicate the state of the last completed animation, and are only used
// to decide whether to trigger a transition to a different state via one of
// the _anim_* functions.
enum yuuka6_sprite_state_t {
	VANISHED = 0,
	PARASOL_BACK_OPEN = 1,
	PARASOL_BACK_CLOSED = 2,
	PARASOL_FORWARD = 3,
	PARASOL_LEFT = 4,
	PARASOL_SHIELD = 8,
};

extern int yuuka6_anim_frame;
extern yuuka6_sprite_state_t yuuka6_sprite_state;

// Call these once per frame to run the indicated sprite animation. All of
// these return true once the animation is finished.
bool near yuuka6_anim_parasol_back_close(void)
;
bool near yuuka6_anim_parasol_back_open(void)
;
bool near yuuka6_anim_parasol_back_pull_forward(void)
;
bool near yuuka6_anim_parasol_back_pull_left(void)
;
bool near yuuka6_anim_parasol_left_spin_back(void)
;
bool near yuuka6_anim_vanish(void)
;
bool near yuuka6_anim_appear(void)
;
bool near yuuka6_anim_parasol_shield(void)
;

void pascal near yuuka6_phase_next(
	explosion_type_t explosion_type, int next_end_hp
);
