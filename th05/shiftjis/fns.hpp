#define BINARY_OP	"op"

// Packfile loaded during most of OP.EXE and MAINE.EXE, except for the Music
// Room
#define OP_AND_END_PF_FN	"���Y�k1.dat"

#define BGM_EXTRA_BOSS_FN	"st06b"

#define DEMO_EXTRA_PART_2_FN	"DEMO5.REC"

#define EYECATCH_FN	"eye.cdg"

#define FACESET_PLAYCHAR_FORMAT	"KaO0.cD2"
#define FACESET_REIMU_FN     	"KAO0.cd2"
#define FACESET_MARISA_FN    	"KAO1.cd2"
#define FACESET_MIMA_FN      	"KAO2.cd2"
#define FACESET_YUUKA_FN     	"KAO3.cd2"

#define main_cdg_load_faceset_playchar() { \
	switch(playchar) { \
		case PLAYCHAR_REIMU: \
			cdg_load_all(CDG_FACESET_PLAYCHAR, FACESET_REIMU_FN); \
			break; \
		case PLAYCHAR_MARISA: \
			cdg_load_all(CDG_FACESET_PLAYCHAR, FACESET_MARISA_FN); \
			break; \
		case PLAYCHAR_MIMA: \
			cdg_load_all(CDG_FACESET_PLAYCHAR, FACESET_MIMA_FN); \
			break; \
		case PLAYCHAR_YUUKA: \
			cdg_load_all(CDG_FACESET_PLAYCHAR, FACESET_YUUKA_FN); \
			break; \
	} \
}

#define FACESET_BOSS_FORMAT	"BsS0.cD2"

#define BOMB_BG_REIMU_FN 	"bb0.cdg"
#define BOMB_BG_MARISA_FN	"bb1.cdg"
#define BOMB_BG_MIMA_FN  	"bb2.cdg"
#define BOMB_BG_YUUKA_FN 	"bb3.cdg"

#define BOMB_SHAPE_FN      	"bomb0.bft"
#define BOMB_SHAPE_YUUKA_FN	"bomb3.bft"

#define main_pat_bomb_shape_load() { \
	if(playchar == PLAYCHAR_YUUKA) { \
		super_entry_bfnt(BOMB_SHAPE_YUUKA_FN); \
	} else { \
		super_entry_bfnt(BOMB_SHAPE_FN); \
	} \
}
