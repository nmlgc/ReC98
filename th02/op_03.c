/* ReC98
 * -----
 * Code segment #3 of TH02's OP.EXE
 */

#include "th02\th02.h"
#include "th02/formats/pi.h"

void title_flash(void)
{
	int page = 1;
	int frame;

	snd_se_reset();
	snd_se_play(6);
	snd_se_update();
	for(frame = 0; frame < 18; frame++) {
		graph_showpage(page);
		page = 1 - page;

		if(frame == 0) {
			pi_slot_put(0, 0, 0);
		} else if(frame == 5) {
			pi_slot_put(0, 0, 1);
		} else if(frame == 10) {
			pi_slot_put(0, 0, 2);
		}

		if(frame % 3 == 0) {
			palette_settone(150);
		} else if(frame % 3 == 1) {
			palette_settone(100);
		}
		frame_delay(1);
	}
	graph_showpage(0);
	graph_pi_free(&pi_slot_headers[0], pi_slot_buffers[0]);
	graph_pi_free(&pi_slot_headers[1], pi_slot_buffers[1]);
	graph_pi_free(&pi_slot_headers[2], pi_slot_buffers[2]);
}
