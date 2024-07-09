#pragma option -2 // ZUN bloat
#pragma codestring "\x00"

#include "th02/hardware/frmdelay.h"
#include "th02/formats/pi.h"
#include "th02/snd/snd.h"

#include "th02/snd/data.c"
#include "th02/snd/se_data.c"

void title_flash(void)
{
	int page = 1;
	int frame;

	snd_se_play_force(6);
	for(frame = 0; frame < 18; frame++) {
		graph_showpage(page);
		page = 1 - page;

		if(frame == 0) {
			pi_put_8(0, 0, 0);
		} else if(frame == 5) {
			pi_put_8(0, 0, 1);
		} else if(frame == 10) {
			pi_put_8(0, 0, 2);
		}

		if(frame % 3 == 0) {
			palette_settone(150);
		} else if(frame % 3 == 1) {
			palette_settone(100);
		}
		frame_delay(1);
	}
	graph_showpage(0);
	pi_free(0);
	pi_free(1);
	pi_free(2);
}
