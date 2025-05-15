#include "x86real.h"

static const unsigned char SE_NONE = 0xFF;

extern unsigned char snd_se_playing;
extern unsigned char snd_se_priorities[];
extern unsigned char snd_se_priority_frames[];
extern unsigned char snd_se_frame;

inline uint16_t snd_load_size() {
	// ZUN landmine: Should rather retrieve the maximum data size for song or
	// sound effect data via PMD_GET_BUFFER_SIZES, instead of hardcoding a
	// random maximum and risking overflowing PMD's data buffer.
	// (Unfortunately, MMD lacks a similar function...)
	// MODDERS: When implementing this properly, rearrange the call sites to
	// make sure that AX isn't destroyed.
	return ((GAME == 5) ? 0xFFFF : 0x5000);
}
