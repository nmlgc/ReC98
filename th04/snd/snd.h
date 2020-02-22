#include "th02/snd/snd.h"

typedef enum {
	SND_BGM_OFF = 0,
	SND_BGM_FM26 = 1,
	SND_BGM_FM86 = 2,
	SND_BGM_MODE_COUNT = 3,
	SND_BGM_MIDI = 3, // unsupported
} snd_bgm_mode_t;

typedef enum {
	SND_SE_OFF = 0,
	SND_SE_FM = 1,
	SND_SE_BEEP = 2,
	SND_SE_MODE_COUNT = 3,
} snd_se_mode_t;

extern unsigned char snd_se_mode;
extern unsigned char snd_bgm_mode;

// Checks the requested BGM and SE modes against the available hardware and
// sets [snd_se_mode] and [snd_bgm_mode] accordingly. Returns [snd_bgm_mode].
unsigned char pascal snd_determine_modes(int req_bgm_mode, int req_se_mode);
