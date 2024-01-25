#pragma option -zCmain_03_TEXT

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/main/playfld.hpp"
#include "th02/main/hud/overlay.hpp"

void pascal near overlay_int_put(
	tram_x_t left, tram_y_t y, int digits, long val
)
{
	enum {
		DIGITS_MAX = 8,
	};

	int i;
	int gaiji = gb_0_; // ACTUAL TYPE: gaiji_th02_t
	long divisor = 10000000; // Must match DIGITS_MAX!
	long digit;
	bool past_leading_zeroes = false;

	for(i = DIGITS_MAX; i > digits; i--) {
		divisor /= 10;
	}
	for(i = 0; i < digits; i++) {
		digit = ((val / divisor) % 10);
		divisor /= 10;
		gaiji = (digit + gb_0_);
		if(digit != 0) {
			past_leading_zeroes = true;
		}
		if(i == (digits - 1)) {
			past_leading_zeroes = true;
		}
		if(past_leading_zeroes) {
			gaiji_putca((left + (i * GAIJI_TRAM_W)), y, gaiji, TX_WHITE);
		}
	}
}

void overlay_wipe(void)
{
	overlay_fill(TX_WHITE);
}
