#include "defconv.h"

extern char snd_interrupt_if_midi;
extern bool snd_midi_possible;
#if GAME <= 3
	typedef enum {
		SND_BGM_OFF,
		SND_BGM_FM,
		SND_BGM_MIDI
	} snd_bgm_mode_t;

	extern bool snd_active;
	extern bool snd_midi_active;
	extern bool snd_fm_possible;
#endif

int snd_pmd_resident(void);
#if GAME != 3
	int snd_mmd_resident(void);
#endif

int snd_determine_mode(void);
int16_t DEFCONV snd_kaja_interrupt(int16_t ax);
#define snd_kaja_func(func, param) snd_kaja_interrupt((func) << 8 | (param))

void snd_delay_until_volume(uint8_t volume);

#define SND_LOAD_SONG (kaja_func_t)(KAJA_GET_SONG_ADDRESS << 8)
#define SND_LOAD_SE (kaja_func_t)(PMD_GET_SE_ADDRESS << 8)

#if defined(PMD) && (GAME <= 3) /* requires kaja.h */
	// Loads a song in .M format ([func] = SND_LOAD_SONG) or a sound effect
	// bank in EFC format ([func] = SND_LOAD_SE) into the respective work
	// buffer of the sound driver. If MIDI is used, 'md' is appended to the
	// file name.
	void DEFCONV snd_load(const char *fn, kaja_func_t func);
#endif

void snd_se_reset(void);
void DEFCONV snd_se_play(int new_se);
void snd_se_update(void);

// Cancels any currently playing sound effect to play the given one.
#define snd_se_play_force(new_se) \
	snd_se_reset(); \
	snd_se_play(new_se); \
	snd_se_update();
