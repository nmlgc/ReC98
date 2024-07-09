#include "th02/snd/snd.h"

#ifdef __cplusplus
extern "C" {
#endif

// Replaces the hardcoded no-BGM delay from the TH02 one with a customizable
// one, while fixing none of the issues from the TH02 version.
void pascal snd_delay_until_measure(int measure, unsigned int frames_if_no_bgm);

#ifdef __cplusplus
}
#endif
