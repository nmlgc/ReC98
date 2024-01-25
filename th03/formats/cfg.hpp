#if GAME == 3
	#define CFG_FN "yume.cfg"
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
void near cfg_load(void);

// Loads just the [resident] pointer from the .CFG file, and returns its new
// value.
resident_t __seg* near cfg_load_resident_ptr(void);

static inline resident_t __seg* cfg_load_and_set_resident(
	cfg_t &cfg, const char *cfg_fn
) {
	file_ropen(cfg_fn);
	file_read(&cfg, sizeof(cfg));
	file_close();

	resident_t __seg *resident_seg = cfg.resident;
	resident = resident_seg;
	return resident_seg;
}

// Saves the current configuration values to the .CFG file, without changing
// its resident segment pointer.
void near cfg_save(void);

// Like cfg_save(), but resets the resident segment pointer to zero.
void near cfg_save_exit(void);
