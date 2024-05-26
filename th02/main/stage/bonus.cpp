#include "shiftjis.hpp"
#include "th02/resident.hpp"
#include "th02/hardware/input.hpp"
#include "th02/snd/snd.h"
#include "th02/core/globals.hpp"
#include "th02/main/playperf.hpp"
#include "th02/main/score.hpp"
#include "th02/main/stage/bonus.hpp"
#include "th02/main/boss/bosses.hpp"
#include "th02/shiftjis/bonus.hpp"

static const int VALUE_DIGITS = 5;

// Coordinates
// -----------

static const tram_cell_amount_t PADDING = 2;

static const tram_x_t LABEL_LEFT = (PLAYFIELD_TRAM_LEFT + 4);
static const tram_x_t VALUE_LEFT = (LABEL_LEFT + BONUS_LABEL_TRAM_W + PADDING);
static const tram_cell_amount_t VALUE_TRAM_W = (VALUE_DIGITS * GAIJI_TRAM_W);
// -----------

struct hack {
	char x[6]; // ACTUAL TYPE: gaiji_th02_t
};

inline void bonus_title_put(const struct hack& title) {
	// ZUN bloat: Not `static`, gets needlessly copied into a local variable.
	const struct hack gBONUS = title;

	overlay_wipe();

	palette_settone(62);
	gaiji_putsa(
		// ZUN bug: Not *quite* centered.
		(PLAYFIELD_TRAM_CENTER_X - (((sizeof(title) - 1) / 2) * 2)),

		4,
		gBONUS.x,
		TX_WHITE
	);
}

// ZUN bloat: Both values should be `score_t` or *at least* unsigned to avoid
// readers having to double-check why this won't overflow with the values
// passed to this function. (It won't because [val_x10] never exceeds 32,767,
// and only 1/10th of that value gets added to [total].)
void pascal near bonus_row_put_and_add(
	tram_y_t y, const shiftjis_t *label, int& sum, int val_x10
)
{
	text_putsa(LABEL_LEFT, y, label, TX_WHITE);
	overlay_uint_put(VALUE_LEFT, y, VALUE_DIGITS, val_x10);

	#define val val_x10 // ZUN bloat
	val = val_x10;
	val /= 10;
	sum += val;
	#undef val
}

inline void bonus_multiply_add_put_and_delay(
	score_t& bonus_total, int bonus_total_digits, const int& sum
) {
	enum {
		POINT_ITEM_DIGITS = 3,
		Y = 18,

		POINT_LABEL_LEFT = (LABEL_LEFT - 2),
		POINT_ITEMS_LEFT = (
			POINT_LABEL_LEFT + (sizeof(BONUS_POINT) - 1) + PADDING
		),
		TIMES_LEFT = (
			POINT_ITEMS_LEFT + (POINT_ITEM_DIGITS * GAIJI_TRAM_W) + PADDING
		),
		SUM_LEFT = (TIMES_LEFT + (sizeof(BONUS_TIMES) - 1) + PADDING),
		EQUALS_LEFT = (SUM_LEFT + (VALUE_DIGITS * GAIJI_TRAM_W) + PADDING),
	};

	text_putsa(POINT_LABEL_LEFT, Y, BONUS_POINT, TX_WHITE);
	overlay_uint_put(
		POINT_ITEMS_LEFT, Y, POINT_ITEM_DIGITS, point_items_collected
	);
	text_putsa(TIMES_LEFT, Y, BONUS_TIMES, TX_WHITE);

	bonus_total = sum;
	bonus_total *= 10;
	overlay_uint_put(SUM_LEFT, Y, VALUE_DIGITS, bonus_total);
	text_putsa(EQUALS_LEFT, Y, BONUS_EQUALS, TX_WHITE);

	bonus_total *= point_items_collected;
	overlay_uint_put(
		// Right-aligning even the 7-digit value of the Extra Stage was more
		// important than ensuring padding after the ＝?
		(PLAYFIELD_TRAM_RIGHT - PADDING - (bonus_total_digits * GAIJI_TRAM_W)),

		Y,
		bonus_total_digits,
		bonus_total
	);

	bonus_total /= 10;
	score_delta += bonus_total;

	snd_se_reset();

	// Not a quirk because the game either
	// • immediately moves to the next stage and calls score_reset() before
	//   rendering the next game frame (for regular stages), or
	// • launches MAINE.EXE soon afterward (for the Extra Stage).
	score_grant_current_delta_as_bonus();

	snd_se_update();

	// ZUN bloat: Has no effect, and isn't read before the next call to
	// input_reset_sense().
	key_det = INPUT_UP;

	key_delay();
}

void near stage_clear_bonus_animate(void)
{
	int val;
	score_t bonus_total;
	int sum = 0;

	extern struct hack gBONUS_0;
	bonus_title_put(gBONUS_0);

	bonus_row_put_and_add(6, BONUS_RANK, sum, (rank * 2000));
	bonus_row_put_and_add(8, BONUS_PLAYPERF, sum, ((playperf + 16) * 200));

	val = (2500 - (stage_bombs_used * 500));
	if(val < 0) {
		val = 0;
	}
	bonus_row_put_and_add(10, BONUS_BOMBS, sum, val);

	val = (3000 - (stage_miss_count * 1000));
	if(val < 0) {
		val = 0;
	}
	bonus_row_put_and_add(12, BONUS_LIVES, sum, val);
	bonus_row_put_and_add(
		14, BONUS_START_BOMBS, sum, ((4 - resident->start_bombs) *  800)
	);
	bonus_row_put_and_add(
		16, BONUS_START_LIVES, sum, ((4 - resident->start_lives) * 1000)
	);

	// The maximum possible sum (divided by 10) is 1910...
	if(sum > 25600) {
		sum = 25600;
	}

	bonus_multiply_add_put_and_delay(bonus_total, 6, sum);
}

void near stage_extra_clear_bonus_animate(void)
{
	int val;
	score_t bonus_total;
	int sum = 0;

	extern struct hack gBONUS_1;
	bonus_title_put(gBONUS_1);

	bonus_row_put_and_add(6, BONUS_EXTRA_CLEAR, sum, 10000);

	val = (20000 - (stage_miss_count * 4000));
	if(val < 0) {
		val = 0;
	}
	bonus_row_put_and_add(8, BONUS_EXTRA_LIVES, sum, val);

	val = (20000 - (stage_bombs_used * 4000));
	if(val < 0) {
		val = 0;
	}
	bonus_row_put_and_add(10, BONUS_EXTRA_BOMBS, sum, val);

	val = (20000 - sigma_frames);
	if(val < 0) {
		val = 0;
	}
	val /= 10;
	val *= 10;
	bonus_row_put_and_add(12, BONUS_EXTRA_SIGMA_FRAMES, sum, val);

	bonus_multiply_add_put_and_delay(bonus_total, 7, sum);
}
