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

	#ifdef __cplusplus
	static inline bool snd_bgm_active() {
		return snd_active;
	}

	static inline bool snd_se_active() {
		return snd_fm_possible;
	}

	// MODDERS: Just use [new_se] directly.
	static inline int16_t snd_get_param(int16_t &param) {
		return param;
	}
	#endif

	#define snd_bgm_is_fm() \
		(snd_midi_active != true)
#endif

// Purely returns whether the PMD driver is resident at its interrupt. The
// check for an actual installed FM sound source is done by
// snd_determine_mode().
bool16 snd_pmd_resident(void);
#if (GAME != 3)
	// Returns whether the MMD driver is resident at its interrupt. If it is,
	// ≤TH03 sets [snd_midi_active] to true.
	bool16 snd_mmd_resident(void);
#endif

// Checks whether an FM sound source is active, and sets [snd_fm_possible]
// and [snd_active]. In the absence of an FM source, [snd_active] is set to
// [snd_midi_active]. Returns the new value of [snd_active].
bool16 snd_determine_mode(void);

// Calls the interrupt handler of the installed sound driver with AX = [ax],
// if any. If BGM is disabled, the return value is undefined.
int16_t DEFCONV snd_kaja_interrupt(int16_t ax);

// Blocks until the active sound driver reports the given [volume] via
// KAJA_GET_VOLUME. The behavior is undefined if no sound driver is active.
void snd_delay_until_volume(uint8_t volume);

#if (GAME == 2)
	#define SND_FALLBACK_DELAY_FRAMES 100

	// Blocks until the active sound driver has played back the current BGM for
	// the *total* given number of full measures. Does *not* correspond to a
	// specific measure of the song; a [measure] within the looping section
	// would still only be hit once, during the first loop.
	// If no sound driver is active, the delay is replaced with
	// frame_delay([SND_FALLBACK_DELAY_FRAMES]).
	// ZUN landmine: Neither PMD nor MMD reset the internal measure when
	// stopping playback. If no BGM is playing and the previous one hasn't been
	// played back for at least the given number of [measures], the function
	// will deadlock.
	void snd_delay_until_measure(int measure);
#endif

#if defined(PMD) /* requires kaja.h */
	#define snd_kaja_func(func, param) ( \
		snd_kaja_interrupt(((func) << 8) + (param)) \
	)
	#if defined(__cplusplus) && (GAME <= 4)
		static inline uint16_t snd_load_size() {
			// ZUN landmine: Should rather retrieve the maximum data size for
			// song or sound effect data via PMD_GET_BUFFER_SIZES, instead of
			// hardcoding a random maximum and risking overflowing PMD's data
			// buffer.
			// (Unfortunately, MMD lacks a similar function...)
			// MODDERS: When implementing this properly, rearrange the call
			// sites to make sure that AX isn't destroyed.
			return 0x5000;
		}
	#endif

	typedef enum {
		SND_LOAD_SONG = (KAJA_GET_SONG_ADDRESS << 8),
		SND_LOAD_SE = (PMD_GET_SE_ADDRESS << 8),
	} snd_load_func_t;

	#if (GAME <= 3) && defined(MASTER_HPP)
		// Loads a song in .M format ([func] == SND_LOAD_SONG) or a sound
		// effect bank in EFC format ([func] == SND_LOAD_SE) into the
		// respective work buffer of the sound driver. If MIDI is used, 'md'
		// is appended to the file name.
		// [fn] still needs to be null-terminated, despite its fixed length.
		void snd_load(const char fn[PF_FN_LEN], snd_load_func_t func);
	#endif
#endif

void snd_se_reset(void);
void DEFCONV snd_se_play(int new_se);
void snd_se_update(void);

// Cancels any currently playing sound effect to play the given one.
#define snd_se_play_force(new_se) { \
	snd_se_reset(); \
	snd_se_play(new_se); \
	snd_se_update(); \
}
