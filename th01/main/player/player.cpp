#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/math/dir.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/main/entity.hpp"
#include "th01/main/hud/hud.hpp"
#include "th01/main/player/anim.hpp"
#include "th01/main/player/bomb.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/shot.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/bullet/pellet_s.hpp"
#include "th01/main/stage/timer.hpp"

/// Durations
/// ---------

static const int DASH_FRAMES_PER_CEL = 4;
static const int DASH_FRAMES = (DASH_FRAMES_PER_CEL * DASH_CELS);
static const int SLIDE_FRAMES = 12;
#define SWING_FRAMES_PER_CEL 3
#define SWING_FRAMES 23
#define SHOTCOMBO_FRAMES_PER_CEL 6
#define SHOTCOMBO_FRAMES 19

/// (Flip kicks are more complicated than that.)
/// ---------

/// .BOS sprite IDs
/// ---------------

#define SWING_CELS 8
#define FLIPKICK_CELS 6
#define SHOTCOMBO_CELS 4
static const int SLIDE_CELS = 2;

// miko_ac.bos
enum player_48x48_cel_t {
	C_SWING = 0,
	C_SWING_last = (C_SWING + SWING_CELS - 1),

	C_L_FLIPKICK,
	C_L_FLIPKICK_last = (C_L_FLIPKICK + FLIPKICK_CELS - 1),
	C_R_FLIPKICK,
	C_R_FLIPKICK_last = (C_R_FLIPKICK + FLIPKICK_CELS - 1),

	C_L_SHOTCOMBO,
	C_L_SHOTCOMBO_last = (C_L_SHOTCOMBO + SHOTCOMBO_CELS - 1),
	C_R_SHOTCOMBO,
	C_R_SHOTCOMBO_last = (C_R_SHOTCOMBO + SHOTCOMBO_CELS - 1),

	_player_48x48_cel_t_FORCE_INT16 = 0x7FFF
};

// miko_ac2.bos
enum player_48x32_cel_t {
	C_L_SLIDE,
	C_L_SLIDE_last = (C_L_SLIDE + SLIDE_CELS - 1),
	C_R_SLIDE,
	C_R_SLIDE_last = (C_R_SLIDE + SLIDE_CELS - 1),
	C_L_SLIDEKICK,
	C_R_SLIDEKICK,

	_player_48x32_cel_t_FORCE_INT16 = 0x7FFF
};
/// ---------------

/// Types
/// -----

enum mode_t {
	// Standing still or dashing left or right. Can switch into M_SHOOT
	// or M_SWING_OR_SLIDE.
	M_REGULAR = 0,

	// Regular shot while standing still or dashing. Quickly switches back
	// into M_REGULAR.
	M_SHOOT = 1,

	// Stationary swing, or sliding left or right. Not interruptible, but can
	// launch into a special attack combo in the end.
	M_SWING_OR_SLIDE = 2,

	// First, second, and third special attacks in a potential combo.
	M_SPECIAL_FIRST = 3,
	M_SPECIAL_SECOND = 4,
	M_SPECIAL_THIRD = 5,
};

enum submode_direction_t {
	SD_STATIONARY = INPUT_NONE,
	SD_LEFT = INPUT_LEFT,
	SD_RIGHT = INPUT_RIGHT,
	SD_NO_ORB_REPEL_THEN_STATIONARY_BUG = INPUT_LEFT_RIGHT,
};

enum submode_special_t {
	SS_FLIPKICK_MOVING = 0,
	SS_FLIPKICK_STATIONARY = 2,
	SS_SLIDEKICK = 4,
	SS_SHOTCOMBO = 6,

	_submode_special_t_FORCE_INT16 = 0x7FFF
};

union submode_t {
	int8_t initial; // useless

	// During M_REGULAR, M_SHOOT, and M_SWING_OR_SLIDE. submode_direction_t.
	int8_t direction;

	// During M_SPECIAL_*. (submode_special_t | x_direction_t).
	int8_t special;

	#define submode_special_is_flipkick(submode, dir) ( \
		(submode.special == (SS_FLIPKICK_STATIONARY | dir)) || \
		(submode.special == (SS_FLIPKICK_MOVING | dir)) \
	)

	// Starts or continues a special combo, based on the currently held
	// direction. [same] and [other] are input_lr_t.
	void special_combo(x_direction_t dir, uint8_t same, uint8_t other) {
		special =
			(input_lr == other) ? (SS_FLIPKICK_STATIONARY | dir) :
			(input_lr ==  same) ? (SS_SLIDEKICK | dir) :
			/*  no direction  */  (SS_FLIPKICK_MOVING | dir);
	}
};

struct ModeFrame {
	int8_t v;

	// Should make sure to actually calculate a result within DASH_CELS...
	// Only doesn't result in a bug because the original code only happens
	// to call it with [v] == 0 or [v] == 1.
	main_ptn_id_t to_dash_cel(main_ptn_id_t base) const {
		return static_cast<main_ptn_id_t>(base + (v & 3));
	}
	// And these also just shouldn't exist.
	int8_t to_dash_cel_int8(main_ptn_id_t base) const {
		return static_cast<main_ptn_id_t>(base + (v & 3));
	}
	int8_t to_dash_cel_2(main_ptn_id_t base) const {
		return static_cast<main_ptn_id_t>(base + (v % 3));
	}

	player_48x48_cel_t to_swing_cel(int8_t frame_offset) const {
		#if (SWING_FRAMES >= (SWING_CELS * SWING_FRAMES_PER_CEL))
			#error Original code assumes a shot combo to take no more than 23 frames
		#endif
		return static_cast<player_48x48_cel_t>(C_SWING + (
			((v + frame_offset) >= SWING_FRAMES)
				? (C_SWING_last * SWING_FRAMES_PER_CEL)
				: (v + frame_offset)
		) / SWING_FRAMES_PER_CEL);
	}

	player_48x48_cel_t to_flipkick_cel(
		int8_t frame_offset, player_48x48_cel_t base
	) const {
		// That's quite a roundabout way of saying "show the first cel for
		// 10 frames, and the remaining ones for 4"...
		return static_cast<player_48x48_cel_t>(
			((v + frame_offset) < 4)
				? base
				: (((v + frame_offset - 7) / 4) + base)
		);
	}

	player_48x48_cel_t to_shotcombo_cel(
		int8_t frame_offset, player_48x48_cel_t base
	) const {
		#if (SHOTCOMBO_FRAMES >= (SHOTCOMBO_CELS * SHOTCOMBO_FRAMES_PER_CEL))
			#error Original code assumes a shot combo to take no more than 23 frames
		#endif
		return static_cast<player_48x48_cel_t>(
			((v + frame_offset) / SHOTCOMBO_FRAMES_PER_CEL) + base
		);
	}

	player_48x32_cel_t to_slide_cel_cur(player_48x32_cel_t base) const {
		return static_cast<player_48x32_cel_t>(base + (v % SLIDE_CELS));
	}

	player_48x32_cel_t to_slide_cel_prev(player_48x32_cel_t base) const {
		return static_cast<player_48x32_cel_t>(base +
			((SLIDE_CELS - 1) - (v % SLIDE_CELS))
		);
	}
};
/// -----

/// Shared state
/// ------------

// Seems pointless, as it's only `true` in modes where the Orb is repelled,
// which only execute a branch of orb_player_hittest() that doesn't check this
// flag to begin with. Except that some of them actually do, on the initial
// frames where the (attack frame-based) friction parameter is still 0.
// So it's actually a *workaround* for the fact that the one parameter to
// orb_player_hittest() bundles both the "repel/no repel" flag and the repel
// friction.
extern bool player_invincible_against_orb;
/// ------------

/// Helper functions
/// ----------------

// The most useless operation in here
inline submode_direction_t input_lr_sanitized() {
	return static_cast<submode_direction_t>(input_lr % INPUT_LEFT_RIGHT);
}

inline void player_shots_add_centered(pixel_t distance_x_from_center = 0) {
	Shots.add(
		(player_left + (PLAYER_W / 4) + distance_x_from_center), player_top
	);
}

inline screen_y_t player_48_left_for(screen_x_t regular_left) {
	return (regular_left - ((48 - PLAYER_W) / 2));
}

inline screen_y_t player_48x48_top(void) {
	return (PLAYFIELD_BOTTOM - 48);
}

// Movement
// --------
// MODDERS: Just use the regular player_move_and_clamp().

#define move_and_clamp_left(delta) \
	player_left -= delta; \
	if(player_left < PLAYER_LEFT_MIN) { \
		player_left = PLAYER_LEFT_MIN; \
	}

#define move_and_clamp_left_2(delta) \
	player_left -= delta; \
	if(player_left <= PLAYER_LEFT_MIN) { \
		player_left = PLAYER_LEFT_MIN; \
	}

#define move_and_clamp_right(delta) \
	player_left += delta; \
	if(player_left >= PLAYER_LEFT_MAX) { \
		player_left = PLAYER_LEFT_MAX; \
	}
// --------

// Rendering
// ---------

inline void player_unput(const int8_t& cel) {
	ptn_unput_8(player_left, player_top, cel);
}

#define player_48x48_unput(cel) \
	player_48x48.unput_8( \
		player_48_left_for(player_left), player_48x48_top(), cel \
	);

inline void player_48x48_put(const player_48x48_cel_t& cel) {
	player_48x48.put_0_8(
		player_48_left_for(player_left), player_48x48_top(), cel
	);
}

#define player_48x48_unput_and_put(prev_left, prev_cel, cur_cel) \
	player_48x48.unput_and_put_overlapped_8( \
		player_48_left_for(player_left), player_48x48_top(), \
		player_48_left_for(prev_left),   player_48x48_top(), \
		cur_cel, \
		prev_cel \
	);

#define player_48x32_unput(cel) \
	player_48x32.unput_8(player_48_left_for(player_left), player_top, cel);

#define player_48x32_put(cel) \
	player_48x32.put_0_8(player_48_left_for(player_left), player_top, cel);

#define player_48x32_unput_and_put(prev_left, prev_cel, cur_cel) \
	player_48x32.unput_and_put_overlapped_8( \
		player_48_left_for(player_left), player_top, \
		player_48_left_for(prev_left),   player_top, \
		cur_cel, \
		prev_cel \
	);
// ---------

#define slide_unput_update_render( \
	mode_frame, combo_enabled, move_func, cel_base \
) { \
	/* screen_x_t */ prev_left = player_left; \
	move_func(6); \
	player_48x32_unput_and_put( \
		prev_left, \
		mode_frame.to_slide_cel_prev(cel_base), \
		mode_frame.to_slide_cel_cur(cel_base) \
	); \
	if((mode_frame.v >= 5) && !input_strike && !input_shot) { \
		combo_enabled = true; \
	} \
}

inline void slide_stop(
	int8_t& mode,
	submode_t& submode,
	ModeFrame& mode_frame,
	player_48x32_cel_t cel_base
) {
	mode = M_REGULAR;
	player_48x32_unput(mode_frame.to_slide_cel_cur(cel_base));
	submode.direction = SD_NO_ORB_REPEL_THEN_STATIONARY_BUG;
	mode_frame.v = 0;
	player_sliding = false;
}

#define special_start(combo_enabled, deflect_if_true) { \
	if(deflect_if_true) { \
		player_deflecting = true; \
	} \
	mdrv2_se_play(11); \
	combo_enabled = false; \
}

#define special_start_strike(mode, submode, combo_enabled, dir) { \
	submode.special_combo( \
		dir, \
		(dir == X_RIGHT) ? INPUT_RIGHT : INPUT_LEFT, \
		(dir == X_RIGHT) ? INPUT_LEFT : INPUT_RIGHT \
	); \
	mode = M_SPECIAL_FIRST; \
	special_start(combo_enabled, (submode.special < SS_SLIDEKICK)); \
}

inline void special_start_shot(
	int8_t& mode, submode_t& submode, int8_t& combo_enabled, x_direction_t dir
) {
	submode.special = (SS_SHOTCOMBO | dir);
	mode = M_SPECIAL_FIRST;
	special_start(combo_enabled, true);
}
/// ----------------

void player_unput_update_render(bool16 do_not_reset_player_state)
{
	#define swing_deflection_frames	player_swing_deflection_frames

	enum bomb_state_t {
		BS_NONE = 0,
		BS_START = 2,
		BS_ACTIVE = 3,

		_bomb_state_t_FORCE_INT16 = 0x7FFF
	};

	static struct {
		int8_t v;

		main_ptn_id_t to_cel(main_ptn_id_t base) const {
			return static_cast<main_ptn_id_t>(
				((v % DASH_FRAMES) < DASH_FRAMES_PER_CEL) ? base : (base + 1)
			);
		}
		// Shouldn't exist.
		int8_t to_cel_int8(main_ptn_id_t base) const {
			return (
				((v % DASH_FRAMES) < DASH_FRAMES_PER_CEL) ? base : (base + 1)
			);
		}
	} dash_cycle = { 0 };

	// Garbage in M_REGULAR, valid in all other [mode]s.
	static ModeFrame mode_frame = { 0 };

	static int8_t mode = M_REGULAR; // mode_t
	static x_direction_t dash_direction = X_LEFT;
	static int8_t bomb_state = BS_NONE; // ACTUAL TYPE: bomb_state_t
	static bool bombing = false; // ZUN bloat: Already covered by bomb_state_t
	static int8_t combo_enabled = false; // ACTUAL TYPE: bool
	extern int8_t swing_deflection_frames;
	static submode_t submode;
	static int8_t ptn_id_prev; // ACTUAL TYPE: main_ptn_id_t

	int prev;
	player_48x48_cel_t cel_prev;
	union {
		main_ptn_id_t new_ptn;
		player_48x48_cel_t new_48x48;
		player_48x32_cel_t new_48x32;
	} cel;
	bool16 bomb_done;
	int special_duration;

	// YOU'VE ALREADY GOT A VARIABLE FOR THIS
	#define prev_cel_48x48	static_cast<player_48x48_cel_t>(prev)

	#define prev_left     	static_cast<screen_x_t>(prev)

	if(do_not_reset_player_state == false) {
		dash_cycle.v = 0;
		mode_frame.v = 0;
		mode = M_REGULAR;
		submode.initial = -1;
		dash_direction = X_LEFT;
		bomb_state = BS_NONE;
		bomb_damaging = false;
		player_sliding = false;
		player_deflecting = false;
		ptn_id_prev = PTN_MIKO_L;
		swing_deflection_frames =
			(rank ==    RANK_EASY) ? 15 :
			(rank ==  RANK_NORMAL) ? 12 :
			(rank ==    RANK_HARD) ? 10 :
			(rank == RANK_LUNATIC) ?  8 : /* ??? */ 12 /* ??? */;
		bombing = false;
		combo_enabled = false;
		input_bomb = false;
		player_invincible_against_orb = false;
		return;
	}

	dash_cycle.v++;
	dash_cycle.v &= (DASH_FRAMES - 1);
	if(((rem_bombs != 0) || bombing) && (bomb_state >= BS_START)) {
		if(bomb_state == BS_START) {
			bomb_frames = 0;
			bomb_state = BS_ACTIVE;
			player_deflecting = true;
			bombing = true;
			rem_bombs--;
			hud_bombs_put(rem_bombs + 1);
		}
		orb_player_hittest(1);
		bomb_done = bomb_update_and_render(bomb_frames);
		bomb_state = (bomb_done == false) ? BS_ACTIVE : BS_NONE;
		if(bomb_done) {
			bombing = false;
			input_bomb = false;
			player_put(PTN_MIKO_L);
			ptn_id_prev = PTN_MIKO_L;
		} else if(bomb_frames > 60) {
			player_put(PTN_MIKO_L_CAST);
		}
		input_shot = false;
		input_strike = false;
		mode = M_REGULAR;
		if(bomb_state == BS_NONE) {
			player_deflecting = false;
		}
	} else if(
		// Yes, not `< M_SPECIAL_FIRST`.
		(input_bomb == true) && (mode != M_SPECIAL_FIRST) && (rem_bombs != 0)
	) {
		bomb_state = BS_START;
		input_bomb = false;
		pellet_speed_raise(0.025f);
	} else if(mode == M_REGULAR) {
		switch(input_lr) {
		default:
			// ZUN bug: Why!? This only introduces a potential case for Reimu
			// to not be rendered, especially since we *will* come here with
			// invalid [submode.direction] values. Just search for
			// SD_NO_ORB_REPEL_THEN_STATIONARY_BUG.
			if(submode.direction == SD_STATIONARY) {
				if(dash_direction != X_RIGHT) {
					cel.new_ptn = PTN_MIKO_L;
				} else {
					cel.new_ptn = PTN_MIKO_R;
				}
				if(ptn_id_prev != cel.new_ptn) {
					player_unput(ptn_id_prev);
				}
				player_put(cel.new_ptn);
				ptn_id_prev = cel.new_ptn;
			}
			// This at least makes sure that the aforementioned glitch only
			// lasts for a single frame.
			submode.direction = SD_STATIONARY;
			break;
		case INPUT_RIGHT:
			dash_direction = X_RIGHT;
			player_unput(ptn_id_prev);
			move_and_clamp_right(4);
			player_put(dash_cycle.to_cel(PTN_MIKO_R_DASH));
			ptn_id_prev = dash_cycle.to_cel_int8(PTN_MIKO_R_DASH);
			submode.direction = SD_RIGHT;
			break;
		case INPUT_LEFT:
			dash_direction = X_LEFT;
			player_unput(ptn_id_prev);
			move_and_clamp_left_2(4);
			player_put(dash_cycle.to_cel(PTN_MIKO_L_DASH));
			ptn_id_prev = dash_cycle.to_cel_int8(PTN_MIKO_L_DASH);
			submode.direction = SD_LEFT;
			break;
		}

		if(input_shot == true) {
			player_unput(ptn_id_prev);
			mode = M_SHOOT;
			mode_frame.v = 0;
			submode.direction = static_cast<submode_direction_t>(input_lr);
			if(submode.direction == INPUT_LEFT_RIGHT) {
				submode.direction = SD_STATIONARY;
			}
			if(submode.direction == SD_STATIONARY) {
				if(dash_direction != X_RIGHT) {
					cel.new_ptn = PTN_MIKO_L_CAST;
				} else {
					cel.new_ptn = PTN_MIKO_R_CAST;
				}
				player_put(cel.new_ptn);
				ptn_id_prev = cel.new_ptn;
			} else if(submode.direction == SD_RIGHT) {
				player_put(PTN_MIKO_R_DASH_SHOOT);
				ptn_id_prev = PTN_MIKO_R_DASH_SHOOT;
			} else if(submode.direction == SD_LEFT) {
				player_put(PTN_MIKO_L_DASH_SHOOT);
				ptn_id_prev = PTN_MIKO_L_DASH_SHOOT;
			}
		}
		if(input_strike == true) {
			player_unput(ptn_id_prev);
			if((input_lr == INPUT_NONE) || (input_lr == INPUT_LEFT_RIGHT)) {
				mode_frame.v = 0;
				mode = M_SWING_OR_SLIDE;
				submode.direction = SD_STATIONARY;
				player_deflecting = true;
				// ZUN bug: No blit call for the rest of the function,
				// leaving Reimu invisible for one frame.
			} else {
				mdrv2_se_play(11);
				mode_frame.v = 0;
				mode = M_SWING_OR_SLIDE;
				submode.direction = input_lr_sanitized();
				player_sliding = true;
				combo_enabled = false;
				player_48x32_put(
					(submode.direction == SD_RIGHT)
						? C_R_SLIDE_last
						: C_L_SLIDE_last
				);
			}
			player_invincible_against_orb = true;
		}
	} else if(mode == M_SHOOT) {
		if(submode.direction == SD_STATIONARY) {
			if(mode_frame.v == 0) {
				player_shots_add_centered();
			} else if(mode_frame.v >= 2) {
				bomb_frames = 0;
				mode = M_REGULAR;
				input_shot = false;
				submode.direction = SD_NO_ORB_REPEL_THEN_STATIONARY_BUG;
			}
		} else if(submode.direction == SD_RIGHT) {
			dash_direction = X_RIGHT;
			player_unput(ptn_id_prev);
			move_and_clamp_right(4);
			player_put(mode_frame.to_dash_cel(PTN_MIKO_R_DASH_SHOOT));
			ptn_id_prev = mode_frame.to_dash_cel_2(PTN_MIKO_R_DASH_SHOOT);
			if(mode_frame.v >= 1) {
				player_shots_add_centered();
				bomb_frames = 0;
				input_shot = false;
				mode = M_REGULAR;
			}
		} else if(submode.direction == SD_LEFT) {
			dash_direction = X_LEFT;
			player_unput(ptn_id_prev);
			move_and_clamp_left(4);
			player_put(mode_frame.to_dash_cel(PTN_MIKO_L_DASH_SHOOT));
			ptn_id_prev = mode_frame.to_dash_cel_int8(PTN_MIKO_L_DASH_SHOOT);
			if(mode_frame.v >= 1) {
				player_shots_add_centered();
				bomb_frames = 0;
				input_shot = false;
				mode = M_REGULAR;
			}
		}
		mode_frame.v++;
	} else if(mode == M_SWING_OR_SLIDE) {
		if(submode.direction == SD_STATIONARY) {
			if(mode_frame.v < 1) {
				// ZUN bug: No blit call for the rest of the function,
				// leaving Reimu invisible during the first frame.
				submode.direction = input_lr_sanitized();
				if(submode.direction != SD_STATIONARY) {
					if(submode.direction == INPUT_LEFT_RIGHT) {
						submode.direction = SD_STATIONARY;
					}
					mode_frame.v = 0;
					player_deflecting = false;
					mdrv2_se_play(11);
					player_sliding = true;
				}
			} else {
				// ZUN bug: Actually, also for the second and third frame!
				if((mode_frame.v % SWING_FRAMES_PER_CEL) == 0) {
					cel.new_48x48 = mode_frame.to_swing_cel(+1);
					prev_cel_48x48 = static_cast<player_48x48_cel_t>(
						cel.new_48x48 - 1
					);
					player_48x48_unput_and_put(
						player_left, prev_cel_48x48, cel.new_48x48
					);
				}
				if(mode_frame.v == swing_deflection_frames) {
					player_deflecting = false;
				}
				if(mode_frame.v >= SWING_FRAMES) {
					mode = M_REGULAR;

					// ZUN bug: No blit call for the rest of the function,
					// leaving Reimu invisible for one frame.
					player_48x48_unput(mode_frame.to_swing_cel(0));

					// ZUN bug: Actually, make that two frames.
					submode.direction = SD_NO_ORB_REPEL_THEN_STATIONARY_BUG;

					mode_frame.v = 0;
					input_strike = false;
					bomb_frames = 0;
					player_invincible_against_orb = false;
				}
			}
		} else if(submode.direction == SD_RIGHT) {
			slide_unput_update_render(
				mode_frame, combo_enabled, move_and_clamp_right, C_R_SLIDE
			);
			if(mode_frame.v >= SLIDE_FRAMES) {
				slide_stop(mode, submode, mode_frame, C_R_SLIDE);
				if((combo_enabled == true) && (input_strike == true)) {
					special_start_strike(mode, submode, combo_enabled, X_RIGHT);
					return;
				} else if((combo_enabled == true) && (input_shot == true)) {
					special_start_shot(mode, submode, combo_enabled, X_RIGHT);
					return;
				}
				input_strike = false;
				bomb_frames = 0;
				combo_enabled = false; // ZUN bloat: Redundant, see below
				player_invincible_against_orb = false;
			}
		} else if(submode.direction == SD_LEFT) {
			slide_unput_update_render(
				mode_frame, combo_enabled, move_and_clamp_left, C_L_SLIDE
			);
			if(mode_frame.v >= SLIDE_FRAMES) {
				slide_stop(mode, submode, mode_frame, C_L_SLIDE);
				if((combo_enabled == true) && (input_strike == true)) {
					special_start_strike(mode, submode, combo_enabled, X_LEFT);
					return;
				} else if((combo_enabled == true) && (input_shot == true)) {
					special_start_shot(mode, submode, combo_enabled, X_LEFT);
					return;
				}
				input_strike = false;
				bomb_frames = 0;
				// No `[combo_enabled] = false` here? Turns out it doesn't
				// matter: We're back to M_REGULAR anyway, and [combo_enabled]
				// is already set to `false` at the beginning of a slide.
				player_invincible_against_orb = false;
			}
		}
		mode_frame.v++;

		// Expressing this test as != SD_NO_ORB_REPEL_THEN_STATIONARY_BUG would
		// make more sense. (It does *not* grant one frame of invincibility
		// against the Orb, as regular player/Orb collision handling is still
		// done outside this function.)
		if((submode.direction == SD_STATIONARY)) {
			if(mode_frame.v < 21) {
				orb_player_hittest(mode_frame.v);
			}
		} else {
			if(submode.direction == SD_RIGHT) {
				orb_player_hittest(OR_3_X_4_RIGHT);
			}
			if(submode.direction == SD_LEFT) {
				orb_player_hittest(OR_3_X_4_LEFT);
			}
		}
	} else if(
		(mode == M_SPECIAL_FIRST) ||
		(mode == M_SPECIAL_SECOND) ||
		(mode == M_SPECIAL_THIRD)
	) {
		// Unput/update/render
		switch(submode.special) {
		case (SS_FLIPKICK_STATIONARY | X_RIGHT):
			prev_cel_48x48 = mode_frame.to_flipkick_cel(-1, C_R_FLIPKICK);
			cel.new_48x48 = mode_frame.to_flipkick_cel(0, C_R_FLIPKICK);
			if(prev_cel_48x48 != cel.new_48x48) {
				player_48x48_unput_and_put(
					player_left, prev_cel_48x48, cel.new_48x48
				);
			} else {
				player_48x48_put(cel.new_48x48);
			}
			break;
		case (SS_FLIPKICK_STATIONARY | X_LEFT):
			prev_cel_48x48 = mode_frame.to_flipkick_cel(-1, C_L_FLIPKICK);
			cel.new_48x48 = mode_frame.to_flipkick_cel(0, C_L_FLIPKICK);
			if(prev_cel_48x48 != cel.new_48x48) {
				player_48x48_unput_and_put(
					player_left, prev_cel_48x48, cel.new_48x48
				);
			} else {
				player_48x48_put(cel.new_48x48);
			}
			break;

		case (SS_FLIPKICK_MOVING | X_RIGHT):
			cel_prev = mode_frame.to_flipkick_cel(-1, C_R_FLIPKICK);
			cel.new_48x48 = mode_frame.to_flipkick_cel(0, C_R_FLIPKICK);
			// MODDERS: Just use [player_left], and remove the `+8` below.
			prev_left = player_48_left_for(player_left);
			player_move_and_clamp(2);
			player_48x48_unput_and_put(prev_left+8, cel_prev, cel.new_48x48);
			break;
		case (SS_FLIPKICK_MOVING | X_LEFT):
			cel_prev = mode_frame.to_flipkick_cel(-1, C_L_FLIPKICK);
			cel.new_48x48 = mode_frame.to_flipkick_cel(0, C_L_FLIPKICK);
			// MODDERS: Just use [player_left], and remove the `+ 8` below.
			prev_left = player_48_left_for(player_left);
			player_move_and_clamp(-2);
			player_48x48_unput_and_put(prev_left+8, cel_prev, cel.new_48x48);
			break;

		case (SS_SLIDEKICK | X_RIGHT):
			// Still needed for the subsequent unblitting on the final frame...
			cel.new_48x32 = C_R_SLIDEKICK;

			prev_left = player_left;
			player_move_and_clamp(6);
			player_48x32_unput_and_put(prev_left, C_R_SLIDEKICK, C_R_SLIDEKICK);
			break;
		case (SS_SLIDEKICK | X_LEFT):
			// Still needed for the subsequent unblitting on the final frame...
			cel.new_48x32 = C_L_SLIDEKICK;

			prev_left = player_left;
			player_move_and_clamp(-6);
			player_48x32_unput_and_put(prev_left, C_L_SLIDEKICK, C_L_SLIDEKICK);
			break;

		case (SS_SHOTCOMBO | X_RIGHT):
			cel_prev = mode_frame.to_shotcombo_cel(-1, C_R_SHOTCOMBO);
			cel.new_48x48 = mode_frame.to_shotcombo_cel(0, C_R_SHOTCOMBO);
			player_48x48_unput_and_put(player_left, cel_prev, cel.new_48x48);
			break;
		case (SS_SHOTCOMBO | X_LEFT):
			cel_prev = mode_frame.to_shotcombo_cel(-1, C_L_SHOTCOMBO);
			cel.new_48x48 = mode_frame.to_shotcombo_cel(0, C_L_SHOTCOMBO);
			player_48x48_unput_and_put(player_left, cel_prev, cel.new_48x48);
			break;
		}
		switch(submode.special) {
		case (SS_FLIPKICK_MOVING | X_RIGHT):
		case (SS_FLIPKICK_MOVING | X_LEFT):
		case (SS_FLIPKICK_STATIONARY | X_RIGHT):
		case (SS_FLIPKICK_STATIONARY | X_LEFT):
			if(mode_frame.v == 20) {
				player_deflecting = false;
			}
			if((mode_frame.v >= 20) && !input_strike && !input_shot)  {
				combo_enabled = true;
			}
			special_duration = 28;
			break;
		case (SS_SLIDEKICK | X_RIGHT):
		case (SS_SLIDEKICK | X_LEFT):
			special_duration = 13;
			break;
		case (SS_SHOTCOMBO | X_RIGHT):
		case (SS_SHOTCOMBO | X_LEFT):
			if(mode_frame.v ==  1) { player_shots_add_centered( -8); }
			if(mode_frame.v ==  4) { player_shots_add_centered( +8); }
			if(mode_frame.v ==  7) { player_shots_add_centered(  0); }
			if(mode_frame.v == 10) { player_shots_add_centered(-16); }
			if(mode_frame.v == 13) { player_shots_add_centered(  0); }
			if(mode_frame.v == 16) { player_shots_add_centered(+16); }
			if(mode_frame.v == 19) { player_shots_add_centered(  0); }
			if(mode_frame.v == 4) {
				player_deflecting = false;
			}
			special_duration = SHOTCOMBO_FRAMES;
		}

		mode_frame.v++;
		if(mode_frame.v > special_duration) {
			// Special attack is done

			// We're not *actually* about to lose the information on which
			// special attack it was (see the ZUN bug at the end of this
			// branch), but the code pretends to do anyway, and unblits the
			// sprite while it "has" this information. Relies on the cel ID
			// variable being set by the rendering code above... which raises
			// the question of why ZUN didn't just *not* render that sprite on
			// this last frame.
			// ZUN bug: The code should render the regular Reimu sprite
			// afterwards, but doesn't. Therefore, Reimu won't be visible on
			// screen during the last frame of a special attack. :zunpet:
			switch(submode.special) {
			case (SS_FLIPKICK_MOVING | X_RIGHT):
			case (SS_FLIPKICK_MOVING | X_LEFT):
			case (SS_FLIPKICK_STATIONARY | X_RIGHT):
			case (SS_FLIPKICK_STATIONARY | X_LEFT):
			case (SS_SHOTCOMBO | X_RIGHT):
			case (SS_SHOTCOMBO | X_LEFT):
				player_48x48_unput(cel.new_48x48);
				break;
			case (SS_SLIDEKICK | X_RIGHT):
			case (SS_SLIDEKICK | X_LEFT):
				player_48x32_unput(cel.new_48x32);
				break;
			}

			bomb_frames = 0;
			mode_frame.v = 0;
			player_sliding = false;
			player_deflecting = false;
			if(mode < M_SPECIAL_THIRD) {
				// Combo continuation
				if((combo_enabled == true) && (input_strike == true)) {
					if(submode_special_is_flipkick(submode, X_LEFT)) {
						submode.special_combo(X_LEFT, INPUT_LEFT, INPUT_RIGHT);
					} else if(submode_special_is_flipkick(submode, X_RIGHT)) {
						submode.special_combo(X_RIGHT, INPUT_RIGHT, INPUT_LEFT);
					}
					mode++;
					special_start(
						combo_enabled, (submode.special < SS_SLIDEKICK)
					);
					return;
				} else if((combo_enabled == true) && (input_shot == true)) {
					if(submode_special_is_flipkick(submode, X_LEFT)) {
						submode.special = (SS_SHOTCOMBO | X_LEFT);
					} else if(submode_special_is_flipkick(submode, X_RIGHT)) {
						submode.special = (SS_SHOTCOMBO | X_RIGHT);
					}
					mode++;
					player_deflecting = true;
					mdrv2_se_play(11);
					combo_enabled = false;
					return;
				}
			}
			player_invincible_against_orb = false;
			mode = M_REGULAR;
			// ZUN bug: [submode.direction] should really have been initialized
			// here as well. Since it's not, the next call to this function
			// will interpret the current special attack as a direction.
		} else {
			// Special attack still going on. Check for orb collision
			switch(submode.special) {
			case (SS_FLIPKICK_MOVING | X_RIGHT):
			case (SS_FLIPKICK_MOVING | X_LEFT):
			case (SS_FLIPKICK_STATIONARY | X_RIGHT):
			case (SS_FLIPKICK_STATIONARY | X_LEFT):
				orb_player_hittest(mode_frame.v / 2);
				break;
			case (SS_SLIDEKICK | X_RIGHT):
				orb_player_hittest(OR_3_X_8_RIGHT);
				break;
			case (SS_SLIDEKICK | X_LEFT):
				orb_player_hittest(OR_3_X_8_LEFT);
				break;
			case (SS_SHOTCOMBO | X_RIGHT):
			case (SS_SHOTCOMBO | X_LEFT):
				if(mode_frame.v < 16) {
					orb_player_hittest(mode_frame.v);
				}
				break;
			}
		}
	}

	#undef prev_left
	#undef prev_cel_48x48
}

template <class T> inline T delta_abs(const T p1, const T p2) {
	return ((p1 - p2) < 0) ? ((p1 - p2) * -1) : (p1 - p2);
}

#define orb_hits_player(hitbox_w, hitbox_h) ( \
	(delta_abs(orb_cur_left, player_left) < hitbox_w) && \
	(delta_abs(orb_cur_top,  player_top)  < hitbox_h) \
)

#define player_in_repel_range() \
	orb_hits_player((PLAYER_W + (ORB_W / 4)), PLAYER_H)

void orb_player_hittest(int repel_friction)
{
	if(repel_friction == OR_NONE) {
		if(
			!player_invincible &&
			!player_invincible_against_orb &&
			orb_hits_player((PLAYER_W - (ORB_W / 4)), (PLAYER_H - (ORB_H / 2)))
		) {
			player_is_hit = true;
		}
	} else if(repel_friction < OR_3_X_UNCHANGED) {
		if(!player_in_repel_range()) {
			return;
		}
		if((player_left - orb_cur_left) > 0) {
			orb_velocity_x = OVX_4_LEFT;
		} else if((player_left - orb_cur_left) == 0) {
			orb_velocity_x = OVX_0;
			if((rand() % 8) == 0) {
				orb_velocity_x = OVX_4_LEFT;
			}
			// ZUN quirk: Shouldn't this be OVX_4_RIGHT, maybe?
			if((rand() % 8) == 4) {
				orb_velocity_x = OVX_4_LEFT;
			}
		} else {
			orb_velocity_x = OVX_4_RIGHT;
		}
		orb_force_new(((repel_friction / 2) + ORB_FORCE_REPEL), OF_IMMEDIATE);
	} else if(player_in_repel_range()) {
		if(repel_friction == OR_3_X_4_LEFT) {
			orb_velocity_x = OVX_4_LEFT;
		} else if(repel_friction == OR_3_X_4_RIGHT) {
			orb_velocity_x = OVX_4_RIGHT;
		} else if(repel_friction == OR_3_X_8_RIGHT) {
			orb_velocity_x = OVX_8_RIGHT;
		} else if(repel_friction == OR_3_X_8_LEFT) {
			orb_velocity_x = OVX_8_LEFT;
		}
		orb_force_new(-10.0, OF_IMMEDIATE);
	}
}

#define miss_effect_put(left, frame) \
	ptn_put_8(left, player_top, (PTN_MISS_EFFECT + (frame % MISS_EFFECT_CELS)))

void player_miss_animate_and_update(void)
{
	int frame;
	screen_x_t effect_left;
	screen_x_t moveout_target_right;
	screen_x_t moveout_target_left;
	int prev_bombs;

	// Miss sprite and shake
	// ---------------------

	// ZUN bug: This should have been the 48×48 unblitting call that's done
	// after the shake. It's easily possible to get hit during an 48×48
	// animation, which will end up leaving the extra pixels on screen during
	// the next 16 frames.
	ptn_sloppy_unput_16(player_left, player_top);

	player_miss_put();

	for(frame = 0; frame < 16; frame++) {
		z_vsync_wait_and_scrollup(RES_Y - ((frame % 2) * 8));
		frame_delay(2);
	}
	z_vsync_wait_and_scrollup(0);
	// ---------------------

	egc_copy_rect_1_to_0_16(
		player_48_left_for(player_left), player_48x48_top(), 48, 48
	);

	Shots.unput_and_reset();
	Pellets.decay();
	player_reset();

	// Effect
	// ------
	enum {
		MOVEOUT_FRAMES = 10,
		MOVEIN_FRAMES = 20,
		FRAMES = (MOVEOUT_FRAMES + MOVEIN_FRAMES),

		MOVEOUT_DISTANCE_X = (PLAYFIELD_W / 4),
		MOVEOUT_DISTANCE_PER_FRAME_X = (MOVEOUT_DISTANCE_X / MOVEOUT_FRAMES),
	};

	moveout_target_right = (player_left + MOVEOUT_DISTANCE_X);
	if(moveout_target_right >= PLAYER_LEFT_MAX) {
		moveout_target_right = PLAYER_LEFT_MAX;
	}
	moveout_target_left = (player_left - MOVEOUT_DISTANCE_X);
	if(moveout_target_left < PLAYER_LEFT_MIN) {
		moveout_target_left = PLAYER_LEFT_MIN;
	}

	effect_left = player_left;
	for(frame = 0; frame < FRAMES; frame++) {
		ptn_sloppy_unput_16(player_left, player_top);
		ptn_sloppy_unput_16(effect_left, player_top);

		player_left += (frame < MOVEOUT_FRAMES)
			? +MOVEOUT_DISTANCE_PER_FRAME_X
			: ((PLAYER_LEFT_START - moveout_target_right) / MOVEIN_FRAMES);
		effect_left += (frame < MOVEOUT_FRAMES)
			? -MOVEOUT_DISTANCE_PER_FRAME_X
			: ((PLAYER_LEFT_START - moveout_target_left) / MOVEIN_FRAMES);

		if(player_left >= PLAYER_LEFT_MAX) {
			player_left = PLAYER_LEFT_MAX;
		}
		if(effect_left < PLAYER_LEFT_MIN) {
			effect_left = PLAYER_LEFT_MIN;
		}

		// We might have accidentally unblitted it earlier, after all.
		orb_put_default();

		miss_effect_put(player_left, frame);
		miss_effect_put(effect_left, frame);
		frame_delay((frame < 6) ? 1 : (((FRAMES - frame) / 10) + 1));
	}

	ptn_sloppy_unput_16(player_left, player_top);
	ptn_sloppy_unput_16(effect_left, player_top);
	// ------

	hud_lives_put(rem_lives + 1);

	prev_bombs = rem_bombs;
	rem_bombs = (bombs_extra_per_life_lost + rem_bombs);
	if(rem_bombs > BOMBS_MAX) {
		rem_bombs = BOMBS_MAX;
	} else {
		hud_bombs_put(prev_bombs);
	}
	timer_extend_and_put();
	pellet_speed_lower(0.0f, -0.05f);
}

// Global state that is defined here for some reason
// -------------------------------------------------

Palette4 boss_post_defeat_palette;
// -------------------------------------------------
