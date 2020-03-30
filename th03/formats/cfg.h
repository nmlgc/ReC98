#if GAME == 3
# define CFG_FN "yume.cfg"
	typedef struct {
		uint8_t bgm_mode;
		uint8_t key_mode;
		uint8_t rank;
		int16_t unused;
	} cfg_options_t;
#endif

#include "th02/formats/cfg.h"

// Loads the [resident] pointer from the .CFG file, initializes the rest of
// the structure (in TH03 and TH04), and clamps the life, bomb, and BGM/SE
// mode fields to their respective ranges (in TH04 and TH05).
void near pascal cfg_load(void);

// Loads just the [resident] pointer from the .CFG file, and returns its new
// value.
resident_t __seg* near pascal cfg_load_resident(void);

// Saves the .CFG file, without changing its resident segment pointer.
void near pascal cfg_save(void);

// Like cfg_save(), but resets the resident segment pointer to zero.
void near pascal cfg_save_exit(void);
