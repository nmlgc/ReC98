#include "defconv.h"

extern char snd_interrupt_if_midi;
extern char snd_midi_possible;
#if GAME <= 3
	typedef enum {
		SND_BGM_OFF,
		SND_BGM_FM,
		SND_BGM_MIDI
	} snd_bgm_mode_t;

	extern char snd_active;
	extern unsigned char snd_midi_active;
	extern char snd_fm_possible;
#endif

int snd_pmd_resident(void);
#if GAME != 3
	int snd_mmd_resident(void);
#endif

int snd_determine_mode(void);
int16_t DEFCONV snd_kaja_interrupt(int16_t ax);
#define snd_kaja_func(func, param) snd_kaja_interrupt((func) << 8 | (param))

#define SND_LOAD_SONG (kaja_func_t)(KAJA_GET_SONG_ADDRESS << 8)
#define SND_LOAD_SE (kaja_func_t)(PMD_GET_SE_ADDRESS << 8)

#ifdef PMD /* requires kaja.h */
	void snd_load(const char *fn, kaja_func_t func);
#endif

void snd_se_reset(void);
void DEFCONV snd_se_play(int new_se);
void snd_se_update(void);
