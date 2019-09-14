/* ReC98
 * -----
 * Types shared between TH04 and TH05
 */

/// Score
/// -----
extern unsigned long score_delta;

void pascal near score_update_and_render(void);

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void);
/// -----
