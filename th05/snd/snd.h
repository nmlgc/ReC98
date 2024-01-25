#include "th04/snd/snd.h"

// Gets the total number of measures that the active sound driver has spent
// playing the current BGM, or -1 if BGM has been disabled.
int snd_bgm_measure(void);
