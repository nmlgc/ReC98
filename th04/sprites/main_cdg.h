#define FACESET_PLAYCHAR_COUNT 6
#if (GAME == 5)
	#define FACESET_BOSS_COUNT 6

	#define EYECATCH_W 288
	#define EYECATCH_H 130

	#define BOMB_BG_W_MAX ((PLAYFIELD_W / 6) * 5)
	#define BOMB_BG_H_MAX PLAYFIELD_H
#else
	#define FACESET_BOSS_COUNT 4

	#define EYECATCH_W 384
	#define EYECATCH_H 176

	#define BOMB_BG_W_MAX PLAYFIELD_W
	#define BOMB_BG_H_MAX (PLAYFIELD_H - 94)
#endif

#define FACE_W 128
#define FACE_H 128

// CDG slots for TH04's and TH05's MAIN.EXE.
typedef enum {
	CDG_BG_PLAYCHAR_BOMB = 0,

	CDG_PER_STAGE,
	CDG_FACESET_PLAYCHAR,
	CDG_FACESET_PLAYCHAR_last = (CDG_FACESET_PLAYCHAR + (FACESET_PLAYCHAR_COUNT - 1)),
	CDG_FACESET_BOSS,
	CDG_FACESET_BOSS_last = (CDG_FACESET_BOSS + (FACESET_BOSS_COUNT - 1)),

	// The original TH05 implementation of ems_preload_boss_faceset() requires
	// this slot to stay empty. Can be deleted after clamping the amount of
	// face images written to the EMS cache area.
	CDG_FACESET_BOSS_sentinel,

	CDG_BG_BOSS = 16,
	CDG_BG_2,	// Second background slot
	CDG_PER_STAGE_last = 30,

	CDG_EYECATCH,
	CDG_COUNT
} main_cdg_slot_t;
