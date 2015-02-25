/* ReC98
 * -----
 * Include file for TH02
 */

#include "pc98.h"

// Formats
#define PI_SLOTS 6

extern void far *pi_slot_buffers[PI_SLOTS];
extern PiHeader pi_slot_headers[PI_SLOTS];

void pi_slot_load(int slot, const char *fn);
void pi_slot_palette_apply(int slot);
void pi_slot_put(int x, int y, int slot);

#define pi_load_put_free(slot, fn) \
	pi_slot_load(slot, (fn)); \
	pi_slot_palette_apply(slot); \
	pi_slot_put(0, 0, slot); \
	graph_pi_free(&pi_slot_headers[slot], pi_slot_buffers[slot]);

// Hardware
void graph_putsa_fx(int x, int y, int color, const char *str);

typedef enum {
	INPUT_UP = 0x1,
	INPUT_DOWN = 0x2,
	INPUT_LEFT = 0x4,
	INPUT_RIGHT = 0x8,
	INPUT_SHOT = 0x10,
	INPUT_BOMB = 0x20,
	INPUT_CANCEL = 0x40,
	INPUT_OK = 0x80,
	INPUT_Q = 0x100,
	INPUT_UP_LEFT = 0x1000,
	INPUT_UP_RIGHT = 0x2000,
	INPUT_DOWN_LEFT = 0x4000,
	INPUT_DOWN_RIGHT = 0x8000
} input_t;

extern input_t input;

void input_sense(void);
void pascal frame_delay(int frames);

// Sound
#include "libs\kaja\kaja.h"

extern char snd_midi_active;
extern char snd_midi_possible;

void snd_kaja_func(kaja_func_t func);

#define SND_LOAD_SONG (KAJA_GET_SONG_ADDRESS << 8)

void snd_load(const char *fn, int func);

void snd_se_reset(void);
void snd_se_play(unsigned char se);
void snd_se_update(void);

// Music Room
#define MUSIC_CMT_FILE "MUSIC.TXT"
#define MUSIC_CMT_LINE_LEN 42
#define MUSIC_CMT_LINE_COUNT 20

// Resident structure
typedef struct {
	char id[11];	// = "MIKOConfig"
	char stage;
	char debug;
	long score;
	int continues_used;
	char rem_bombs;
	char rem_lives;
	char rank;
	char start_power;
	char bgm_mode;
	char start_bombs;
	char start_lives;
	long frame;
	int unused_1;
	char unused_2;
	char op_main_retval;
	char perf;
	char unused_3;
	char shottype;
	char demo_num;
	int skill;
	int unused_4;
	long score_highest;
} mikoconfig_t;

extern mikoconfig_t *mikoconfig;

#define SHOTTYPE_COUNT 3
