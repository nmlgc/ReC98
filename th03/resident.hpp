#include "th03/playchar.hpp"
#include "th03/score.hpp"

enum key_mode_t {
	KM_KEY_KEY,
	KM_JOY_KEY,
	KM_KEY_JOY
};

enum vs_mode_t {
	VS_1P_CPU = 0,
	VS_1P_2P = 1,
	VS_CPU_CPU = 2,
};

enum game_mode_t {
	GM_NONE = 0,
	GM_STORY = 1,
	GM_DEMO = 0x7F,
	GM_VS = 0x80,
	GM_VS_1P_CPU = GM_VS + VS_1P_CPU,
	GM_VS_1P_2P = GM_VS + VS_1P_2P,
	GM_VS_CPU_CPU = GM_VS + VS_CPU_CPU,
};

#define STAGE_DECISIVE 6
#define STAGE_CHIYURI 7
#define STAGE_YUMEMI 8
#define STAGE_COUNT 9

// Won't enter [score_last[0]] into YUME.NEM, even if it's high enough for a
// place. Also used for just showing the high scores from the main menu.
#define STAGE_NONE -1
#define STAGE_ALL 99

#define CREDIT_LIVES 2

#define DEMO_COUNT 4

#define RES_ID "YUMEConfig"
struct resident_t {
	char id[sizeof(RES_ID)];
	unsigned char rank;
	PlaycharPalettedOptional playchar_paletted[PLAYER_COUNT];
	bool is_cpu[PLAYER_COUNT];
	long rand;
	int8_t unused_1;
	unsigned char bgm_mode;
	unsigned char key_mode;
	pid_t pid_winner;
	score_lebcd_t score_last[PLAYER_COUNT];
	unsigned char game_mode;
	PlaycharPalettedOptional story_opponents[STAGE_COUNT];
	int8_t unused_2;
	unsigned char story_stage;
	unsigned char story_lives;
	bool show_score_menu;
	unsigned char rem_credits;
	bool op_skip_animation;
	unsigned char skill;
	unsigned char demo_num;	// 0 = no demo active
	int8_t unused_3[198];
};

extern resident_t far *resident;
