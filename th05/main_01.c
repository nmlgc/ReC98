/* ReC98
 * -----
 * Code segment #1 of TH05's MAIN.EXE
 */

#include "th05/th05.h"

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void)
{
	while(score_delta > 0) {
		score_update_and_render();
	}
}
