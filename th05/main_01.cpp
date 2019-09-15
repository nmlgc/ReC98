/* ReC98
 * -----
 * Code segment #1 of TH05's MAIN.EXE
 */

extern "C" {
#include "th05/th05.hpp"

void pascal  far nullsub_1(void);
void pascal near nullfunc_near(void);

void pascal near playfield_fillm_32_0_320_192(void);
void pascal near playfield_fillm_0_0_384_192__2(void);
void pascal near playfield_fillm_0_205_384_163(void);
void pascal near playfield_fillm_64_56_256_256(void);
void pascal near playfield_fillm_0_0_384_192__1(void);
void pascal near playfield_fillm_0_104_384_192(void);

char boss_phase_timed_out = 0;

void pascal near boss_reset(void);

#include "th05/stage/setup.cpp"

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void)
{
	while(score_delta > 0) {
		score_update_and_render();
	}
}

}
