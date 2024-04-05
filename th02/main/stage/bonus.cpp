#include "shiftjis.hpp"
#include "th02/shiftjis/bonus.hpp"

static const int VALUE_DIGITS = 5;

// Coordinates
// -----------

static const tram_cell_amount_t PADDING = 2;

static const tram_x_t LABEL_LEFT = (PLAYFIELD_TRAM_LEFT + 4);
static const tram_x_t VALUE_LEFT = (LABEL_LEFT + BONUS_LABEL_TRAM_W + PADDING);
// -----------

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
