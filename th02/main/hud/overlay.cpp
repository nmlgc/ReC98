#pragma option -zCmain_03_TEXT

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/score.h"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/score_p.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/hud/overlay.hpp"

void pascal near overlay_uint_put(
	tram_x_t left, tram_y_t y, int digits, long val
)
{
	#define on_digit(i, gaiji) { \
		gaiji_putca((left + (i * GAIJI_TRAM_W)), y, gaiji, TX_WHITE); \
	}
	gaiji_score_put_digits(val, digits, on_digit);
	#undef on_digit
}

void overlay_wipe(void)
{
	overlay_fill(TX_WHITE);
}

#include "th02/main/stage/bonus.cpp"
