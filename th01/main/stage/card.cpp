#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/digit.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grppsafx.h"
#include "th01/snd/mdrv2.h"
#include "th01/sprites/pellet.h"
#include "th01/main/debug.hpp"
#include "th01/main/hud/hud.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/bomb.hpp"
#include "th01/main/stage/item.hpp"
#include "th01/main/stage/card.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/stage/stages.hpp"

uint8_t card_flip_cycle = 0;

void cards_hittest(int stage_id)
{
	for(unsigned int i = 0; i < cards.count; i++) {
		struct {
			upixel_t y, x;
		} delta;

		delta.x = ((cards.left[i] - orb_cur_left) < 0)
			? ((cards.left[i] - orb_cur_left) * -1)
			: (cards.left[i] - orb_cur_left);

		delta.y = ((cards.top[i] - orb_cur_top) < 0)
			? ((cards.top[i] - orb_cur_top) * -1)
			: (cards.top[i] - orb_cur_top);

		if((
			(delta.x < STAGEOBJ_ORB_DISTANCE_X) &&
			(delta.y < STAGEOBJ_ORB_DISTANCE_Y) &&
			(cards.flag[i] == CARD_ALIVE)
		) || (
			(test_damage == true) && (cards.flag[i] == CARD_ALIVE)
		) || (
			(bomb_damaging == true) &&
			((bomb_frame % cards.count) == i) &&
			((irand() % 4) != 0) &&
			(cards.flag[i] == CARD_ALIVE)
		)) {
			cards.flag[i] = CARD_FLIPPING;
			cards_score[i] = ((((stage_id / 5) * 100) + 100) + (
				static_cast<unsigned long>(cardcombo_cur * cardcombo_cur) *
				(((rank == RANK_LUNATIC) * 15) + 20)
			));
			if(cards_score[i] > CARD_SCORE_CAP) {
				cards_score[i] = CARD_SCORE_CAP;
			}
			score += cards_score[i];
			cardcombo_cur++;
			if(cardcombo_max < cardcombo_cur) {
				cardcombo_max = cardcombo_cur;
			}
			hud_score_and_cardcombo_render();

			if(((card_flip_cycle++) % 10) == 0) {
				if(card_flip_cycle >= CARD_FLIP_CYCLE_MAX) {
					card_flip_cycle = 1;
					if(bomb_damaging) {
add_point_item:
						items_point_add(i);
					} else {
						items_bomb_add(i);
					}
				} else {
					goto add_point_item;
				}
			}
			mdrv2_se_play(2);
		}
	}
}

#include "th01/math/str_val.cpp"

static const unsigned int CARD_SCORE_CAP_DIGITS = digit_count(CARD_SCORE_CAP);
static const pixel_t CARD_SCORE_W = (CARD_SCORE_CAP_DIGITS * GLYPH_HALF_W);

// The score animation lags behind the card-flipping animation by this amount
// of frames.
static const int SCORE_CEL_DELAY_FRAMES = (CARD_FRAMES_PER_CEL / 2);

static const int KEYFRAME_SCORE_FIRST = (
	card_first_frame_of(CARD_CEL_EDGE) + SCORE_CEL_DELAY_FRAMES
);
static const int KEYFRAME_SCORE_MOVE_UP = (
	card_first_frame_of(CARD_CEL_BACK_HALF) + SCORE_CEL_DELAY_FRAMES
);
static const int KEYFRAME_FLIP_DONE = (
	card_first_frame_of(CARD_CEL_FLIPPED) + 1
);
static const int KEYFRAME_SCORE_DONE = (
	KEYFRAME_FLIP_DONE + SCORE_CEL_DELAY_FRAMES
);

void cards_score_render(void)
{
	pixel_t popup_y;
	pixel_t offset_left;
	enum {
		offset_top = ((STAGEOBJ_H / 2) - (GLYPH_H / 2)),
	};
	char str[CARD_SCORE_CAP_DIGITS + 1];

	for(int i = 0; i < cards.count; i++) {
		if(
			(cards_score[i] != 0) &&
			(cards.flip_frame[i] > (KEYFRAME_SCORE_FIRST - 1))
		) {
			if(cards.flip_frame[i] > (KEYFRAME_SCORE_MOVE_UP - 1)) {
				popup_y	= (cards.flip_frame[i] - (KEYFRAME_SCORE_MOVE_UP - 1));
			} else {
				popup_y = 0;
			}

			// cards_hittest() ensures that 100 is the minimum value.
			// ZUN bug: Should be >=. Can in fact be observed on stages 96-99
			// on non-Lunatic, and stages 321-324 on Lunatic.
			if(cards_score[i] > 10000) {
				offset_left = -GLYPH_HALF_W;
			} else if(cards_score[i] > 1000) {
				offset_left = 0;
			} else {
				if(cards_score[i] > 100) {
				}
				offset_left = +GLYPH_HALF_W;
			}

			if(popup_y != 0) {
				egc_copy_rect_1_to_0_16_word_w(
					(cards.left[i] + offset_left),
					(cards.top[i] + offset_top - (
						(popup_y > 0) ? (popup_y - 1) : 0
					)),
					CARD_SCORE_W,
					GLYPH_H
				);
			}

			if(cards.flip_frame[i] >= KEYFRAME_SCORE_DONE) {
				cards_score[i] = 0;
			} else {
				str_from_positive_int16(str, cards_score[i]);
				graph_putsa_fx(
					(cards.left[i] + offset_left),
					(cards.top[i] + offset_top - popup_y),
					(V_WHITE | FX_WEIGHT_BOLD),
					str
				);
			}
		}
	}
}

#define card_put_8(i) \
	stageobj_put_bg_and_obj_8( \
		cards.left[i], \
		cards.top[i], \
		CARD_ANIM[cards.hp[i]][cards.flip_frame[i] / CARD_FRAMES_PER_CEL], \
		i \
	);

void cards_update_and_render(void)
{
	int i;
	int cards_removed = 0;

	// ZUN bug: Why is this called first? The animated card sprites will
	// therefore overlap the score popup every [CARD_FRAMES_PER_CEL] frames,
	// leading to some minor flickering.
	cards_score_render();

	for(i = 0; i < cards.count; i++) {
		if(cards.flag[i] == CARD_FLIPPING) {
			if(
				(cards.flip_frame[i] < KEYFRAME_FLIP_DONE) &&
				((cards.flip_frame[i] % CARD_FRAMES_PER_CEL) == 0)
			) {
				graph_accesspage_func(1);	card_put_8(i);
				graph_accesspage_func(0);	card_put_8(i);
			}
			cards.flip_frame[i]++;
			if(cards.flip_frame[i] >= card_first_frame_of(CARD_CEL_FLIPPED)) {
				if(rank == RANK_LUNATIC) {
					pellet_group_t group;

					if(stage_num < (STAGES_PER_SCENE * 2)) {
						group = PG_1_AIMED;
					} else {
						group = PG_1_RANDOM_NARROW_AIMED;
					}

					if(cards.flip_frame[i] == KEYFRAME_FLIP_DONE) {
						Pellets.add_group(
							(cards.left[i] + (STAGEOBJ_W / 2) - (PELLET_W / 2)),
							(cards.top[i]  + (STAGEOBJ_H / 2) - (PELLET_H / 2)),
							group,
							to_sp(3.5f)
						);
					}
				}
				if(cards.flip_frame[i] >= card_first_frame_of(CARD_CELS)) {
					if(cards.hp[i] == 0) {
						cards.flag[i] = CARD_REMOVED;
						cards.flip_frame[i] = 0;
					} else {
						cards.flag[i] = CARD_ALIVE;
						cards.flip_frame[i] = 0;
						cards.hp[i]--;
					}
				}
			}
		}
		if(cards.flag[i] == CARD_REMOVED) {
			cards_removed++;
		}
	}
	if(cards_removed == cards.count) {
		stage_cleared = true;
		player_is_hit = true;
	}
}
