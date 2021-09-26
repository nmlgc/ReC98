#include "th01/hardware/input.hpp"
#include "th01/sprites/pellet.h"
#include "th01/math/subpixel.hpp"
#include "th01/main/bullet/pellet.hpp"

static const unsigned int CARD_SCORE_CAP_DIGITS = digit_count(CARD_SCORE_CAP);
static const pixel_t CARD_SCORE_W = (CARD_SCORE_CAP_DIGITS * GLYPH_HALF_W);

static const int FRAME_SCORE_FIRST = (
	card_first_frame_of(CARD_CEL_EDGE) + (CARD_FRAMES_PER_CEL / 3)
);
static const int FRAME_SCORE_MOVE_UP = (
	card_first_frame_of(CARD_CEL_BACK_HALF) + (CARD_FRAMES_PER_CEL / 3)
);
static const int FRAME_ANIM_DONE = (card_first_frame_of(CARD_CEL_FLIPPED) + 1);

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
			(cards_score[i] != 0) && (cards.flip_frames[i] > FRAME_SCORE_FIRST)
		) {
			if(cards.flip_frames[i] > FRAME_SCORE_MOVE_UP) {
				popup_y	= (cards.flip_frames[i] - FRAME_SCORE_MOVE_UP);
			} else {
				popup_y = 0;
			}

			// cards_hittest() ensures that 100 is the minimum value.
			// ZUN bug: Should be >=.
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

			if(cards.flip_frames[i] >= (
				FRAME_ANIM_DONE + (CARD_FRAMES_PER_CEL / 2)
			)) {
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
	stageobj_put_8( \
		cards.left[i], \
		cards.top[i], \
		CARD_ANIM[cards.hp[i]][cards.flip_frames[i] / CARD_FRAMES_PER_CEL], \
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
				(cards.flip_frames[i] < FRAME_ANIM_DONE) &&
				((cards.flip_frames[i] % CARD_FRAMES_PER_CEL) == 0)
			) {
				graph_accesspage_func(1);	card_put_8(i);
				graph_accesspage_func(0);	card_put_8(i);
			}
			cards.flip_frames[i]++;
			if(cards.flip_frames[i] >= card_first_frame_of(CARD_CEL_FLIPPED)) {
				if(rank == RANK_LUNATIC) {
					pellet_group_t group;

					if(stage_num < 10) {
						group = PG_1_AIMED;
					} else {
						group = PG_1_RANDOM_NARROW_AIMED;
					}

					if(cards.flip_frames[i] == FRAME_ANIM_DONE) {
						Pellets.add_group(
							(cards.left[i] + (STAGEOBJ_W / 2) - (PELLET_W / 2)),
							(cards.top[i] + (STAGEOBJ_H / 2) - (PELLET_H / 2)),
							group,
							to_sp(3.5f)
						);
					}
				}
				if(cards.flip_frames[i] >= card_first_frame_of(CARD_CELS)) {
					if(cards.hp[i] == 0) {
						cards.flag[i] = CARD_REMOVED;
						cards.flip_frames[i] = 0;
					} else {
						cards.flag[i] = CARD_ALIVE;
						cards.flip_frames[i] = 0;
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
		done = true;
	}
}
