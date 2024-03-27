#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th02/score.h"
#include "th02/v_colors.hpp"
#include "th02/formats/end.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/score_p.hpp"

// State
// -----

shiftjis_t end_text[100][END_LINE_SIZE];
// -----

void pascal near end_load(const char *fn)
{
	file_ropen(fn);

	// ZUN landmine: No check to ensure that the size is ≤ sizeof(end_text).
	// Dynamic allocation would have made more sense...
	size_t size = file_size();
	file_read(end_text, size);

	file_close();
}

void pascal near verdict_value_score_put(
	screen_x_t left, screen_y_t top, score_t score
)
{
	#define on_digit(i, gaiji) { \
		graph_gaiji_putc((left + (GAIJI_W * i)), top, gaiji, V_WHITE); \
	}
	gaiji_score_put(score, on_digit, false);
	#undef on_digit
}
