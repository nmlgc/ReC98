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
