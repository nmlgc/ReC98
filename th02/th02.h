/* ReC98
 * -----
 * Include file for TH02
 */

#include "ReC98.h"
#include "th01\ranks.h"

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

// Gaiji characters
/* ZUN messed up and swapped M and N in MIKOFT.BFT for both regular and bold
 * fonts. Therefore, other code shouldn't really use the straightforward
 * solution of just adding char literals to a defined start offset, as it may
 * suggest that this also works for M and N (which it doesn't). So...
 */
typedef enum {
	GB_DIGITS = 160,
	gb_0_ = GB_DIGITS,
	gb_1_,
	gb_2_,
	gb_3_,
	gb_4_,
	gb_5_,
	gb_6_,
	gb_7_,
	gb_8_,
	gb_9_,

	GB_LETTERS = 105,
	gb_A_ = GB_LETTERS + 'A',
	gb_B_,
	gb_C_,
	gb_D_,
	gb_E_,
	gb_F_,
	gb_G_,
	gb_H_,
	gb_I_,
	gb_J_,
	gb_K_,
	gb_L_,
	gb_M_ = GB_LETTERS + 'N',
	gb_N_ = GB_LETTERS + 'M',
	gb_O_ = GB_LETTERS + 'O',
	gb_P_,
	gb_Q_,
	gb_R_,
	gb_S_,
	gb_T_,
	gb_U_,
	gb_V_,
	gb_W_,
	gb_X_,
	gb_Y_,
	gb_Z_,

	gb_SP = 207,
} gaiji_bold_t;

typedef enum {
	gs_YINYANG = 2, // ☯
	gs_BOMB, // ◉? ⦿? 🎯? 🖸? Or simply 💣?
	gs_BULLET = 218, // •
	gs_PERIOD, // .
	gs_EXCLAMATION, // !
	gs_QUESTION, // ?
	gs_ELLIPSIS, // …
	gs_COPYRIGHT, // ©
	gs_HEART, // 🎔
	gs_SKULL, // 💀
	gs_GHOST, // 👻
	gs_SIDDHAM_HAM, // Siddhaṃ seed syllable HĀṂ (I don't even)
	gs_SPACE, // ␠
	gs_ARROW_LEFT, // ←
	gs_ARROW_RIGHT, // →
	gs_END, // "End"
	gs_ALL = 240 // "All"
} gaiji_symbols_t;

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
void pascal frame_delay_2(int frames);

// Sound
#include "libs\kaja\kaja.h"

extern char snd_midi_active;
extern char snd_midi_possible;

int snd_kaja_func(kaja_func_t func);

#define SND_LOAD_SONG (KAJA_GET_SONG_ADDRESS << 8)

void snd_load(const char *fn, kaja_func_t func);

void snd_se_reset(void);
void snd_se_play(int new_se);
void snd_se_update(void);

// Music Room
#define MUSIC_CMT_FILE "MUSIC.TXT"
#define MUSIC_CMT_LINE_LEN 42
#define MUSIC_CMT_LINE_COUNT 20

// Configuration file
#pragma option -a1
typedef struct {
	char rank;
	char music;
	char bombs;
	char lives;
	char perf;
	int resident_sgm;
	char debug;
} huuma_cfg_t;
#pragma option -a2

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
} resident_t;

extern resident_t *mikoconfig;

#define SHOTTYPE_COUNT 3

// Highscores
#define SCORE_PLACES 10
#define SCORE_NAME_LEN 6 /* excluding the terminating 0 */
#define EXTRA_CLEAR_FLAGS {1, 2, 4}
#define GAME_CLEAR_CONSTANTS {318, 118, 218}
#define STAGE_ALL 127

typedef struct {
	/* For ranks (and therefore, structure instances) #0, #1 and #2 (Easy,
	 * Normal and Hard), this is either GAME_CLEAR_CONSTANTS[rank] or 0,
	 * and indicates whether the main 5 stages have been cleared with the
	 * *shot type* associated with the rank's index, in any difficulty.
	 * Yes, ZUN uses a field in a rank-specific structure to store a
	 * shot type-specific value.
	 *
	 * For rank #3, this is instead interpreted as a bit field using the
	 * EXTRA_CLEAR_FLAGS to indicate whether the Extra Stage has been
	 * cleared with the respective shot type.
	 * Yes, ZUN stores what is technically information about the Extra
	 * rank in the structure of the Lunatic rank.
	 *
	 * For rank #4, this field is unused.
	 */
	int cleared;

	long points[SCORE_PLACES];
	long points_sum;
	unsigned char g_name[SCORE_PLACES][SCORE_NAME_LEN + 1];
	unsigned char g_name_first_sum;
	unsigned char stage[SCORE_PLACES];
	unsigned char stage_sum;
	struct date date[SCORE_PLACES];
	unsigned char shottype[SCORE_PLACES];
} score_t;

typedef struct {
	score_t score;
	long score_sum; // Sum of all bytes in score, pre-encraption
} score_file_t;

extern char cleared_game_with[SHOTTYPE_COUNT];
extern char cleared_extra_with[SHOTTYPE_COUNT];
