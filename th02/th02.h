/* ReC98
 * -----
 * Include file for TH02
 */

#include "ReC98.h"
#include "th01\ranks.h"

// Formats
// -------
typedef struct {
	char magic[4]; // = "MPTN"
	char count;
	char unused;
} mptn_header_t;

#define MPTN_SIZE (8 * 16)

extern char mptn_show_palette_on_load;
extern unsigned char mptn_count;
extern int *mptn_buffer;
extern char mptn_palette[16 * 3];

int pascal mptn_load(const char *fn);
void pascal mptn_palette_show(void);
void pascal mptn_free(void);

// "東方封魔.録" in Shift-JIS
#define PF_FN "\x93\x8C\x95\xFB\x95\x95\x96\x82\x2E\x98\x5E"
#define PF_KEY 0x12
// -------

// Hardware
// -------
#define graph_clear_both() \
	graph_accesspage(1);	graph_clear(); \
	graph_accesspage(0);	graph_clear(); \
	graph_accesspage(0);	graph_showpage(0);

#include "th01/hardware/grppsafx.h"

void pascal graph_copy_rect_1_to_0(int x, int y, int w, int h);
// -------

// Gaiji characters
// ----------------
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

	// Unused 32x16 rank sprites
	gs_EA, gs_SY, // "Ea", "sy"
	gs_NOR, gs_MAL, // "Nor, "mal"
	gs_HA, gs_RD, // "Ha, "rd"
	gs_LUN, gs_ATIC, // "Lun", "atic"

	gs_ALL, // "All"
} gaiji_symbols_t;
// ----------------

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

extern input_t key_det; /* ZUN symbol [MAGNet2010] */

void input_sense(void);

void pascal frame_delay(int frames);
void pascal frame_delay_2(int frames);

void key_delay(void);

// Sound
// -----
typedef enum {
	SND_BGM_OFF,
	SND_BGM_FM,
	SND_BGM_MIDI
} snd_bgm_mode_t;

#include "libs\kaja\kaja.h"

extern char snd_active;
extern char snd_interrupt_if_midi;
extern unsigned char snd_midi_active;
extern char snd_midi_possible;
extern char snd_fm_possible;

int snd_pmd_resident(void);
int snd_mmd_resident(void);

int snd_determine_mode(void);
int16_t snd_kaja_interrupt(int16_t ax);
#define snd_kaja_func(func, param) snd_kaja_interrupt((func) << 8 | (param))

#define SND_LOAD_SONG (KAJA_GET_SONG_ADDRESS << 8)
#define SND_LOAD_SE (PMD_GET_SE_ADDRESS << 8)

void snd_load(const char *fn, kaja_func_t func);

void snd_se_reset(void);
void snd_se_play(int new_se);
void snd_se_update(void);
// -----

// Music Room
#define MUSIC_CMT_FILE "MUSIC.TXT"
#define MUSIC_CMT_LINE_LEN 42
#define MUSIC_CMT_LINE_COUNT 20

// Configuration file
// ------------------
#define CFG_FN "huuma.cfg"
#pragma option -a1
typedef struct {
	int8_t rank;
	int8_t bgm_mode;
	int8_t bombs;
	int8_t lives;
	int8_t perf;
} huuma_options_t;

typedef struct {
	huuma_options_t opts;
	void __seg *resident_sgm;
	int8_t debug;
} huuma_cfg_t;
#pragma option -a.
// ------------------

// Resident structure
// ------------------
#define RES_ID "MIKOConfig"
typedef struct {
	char id[11];	// = RES_ID
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
	unsigned char op_main_retval;
	unsigned char perf;
	char unused_3;
	char shottype;
	char demo_num;
	int skill;
	int unused_4;
	long score_highest;
} resident_t;

extern resident_t *resident;
extern char unused_op_2_3; // Maybe debug mode?
extern char rank;
extern char lives;
extern char bombs;
// ------------------

#define SHOTTYPE_COUNT 3

// Highscores
// ----------
#define SCOREDAT_PLACES 10
#define SCOREDAT_NAME_LEN 6 /* excluding the terminating 0 */
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
	int16_t cleared;

	int32_t points[SCOREDAT_PLACES];
	int32_t points_sum;
	unsigned char g_name[SCOREDAT_PLACES][SCOREDAT_NAME_LEN + 1];
	unsigned char g_name_first_sum;
	unsigned char stage[SCOREDAT_PLACES];
	unsigned char stage_sum;
	struct date date[SCOREDAT_PLACES];
	unsigned char shottype[SCOREDAT_PLACES];
} scoredat_t;

typedef struct {
	scoredat_t score;
	int32_t score_sum; // Sum of all bytes in [score], pre-encraption
} scoredat_section_t;

extern char cleared_game_with[SHOTTYPE_COUNT];
extern char cleared_extra_with[SHOTTYPE_COUNT];

int pascal scoredat_cleared_load(void);
// ----------

// Debugging
// ---------
// Calls ZUN's interrupt vector set up in ZUNINIT.COM to display an error
// message.
typedef enum {
	ERROR_FILE_NOT_FOUND = 2,
	ERROR_OUT_OF_MEMORY = 3,
	ERROR_MISSING_DRIVER = 4,
	ERROR_SCOREDAT_CORRUPT = 5
} zun_error_t;

void pascal zun_error(zun_error_t err);
// ---------
