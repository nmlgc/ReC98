#define EYECATCH_FN_FORMAT	"eye0.cdg"

#define FACESET_REIMU_FN 	"KAO0.cd2"
#define FACESET_MARISA_FN	"KAO1.cd2"

#define main_cdg_load_faceset_playchar() { \
	if(playchar == PLAYCHAR_REIMU) { \
		cdg_load_all(CDG_FACESET_PLAYCHAR, FACESET_REIMU_FN); \
	} else { \
		cdg_load_all(CDG_FACESET_PLAYCHAR, FACESET_MARISA_FN); \
	} \
}

#define BOSS_BB_MUGETSU_FN 	"st06.bb"
#define BOSS_BB_GENGETSU_FN	"st06b.bb"

#define BOMB_BG_FORMAT	"BB0.CDG"

#define BOSS_BG_MUGETSU_FN 	"st06bk.cdg"
#define BOSS_BG_GENGETSU_FN	"st06bk2.cdg"
