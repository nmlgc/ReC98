/* ReC98
 * -----
 * Code segment #1 of TH05's MAIN.EXE
 */

extern "C" {
#include "th05/th05.hpp"

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void)
{
	while(score_delta > 0) {
		score_update_and_render();
	}
}

}
