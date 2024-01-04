#include "th02/shiftjis/bgm.hpp"
#include "th03/shiftjis/bgm.hpp"
#include "th04/shiftjis/bgm.hpp"
#include "th05/shiftjis/bgm.hpp"

static const unsigned int GAME_COUNT = 5;
static const unsigned int TRACKS_MAX = 30;

// Corresponds to 36 Shift-JIS code units.
static const pixel_t TRACKLIST_W = 288;

const shiftjis_t* LABEL_UP     = "             ------ ▲ ------       ";
const shiftjis_t* LABEL_DOWN   = "             ------ ▼ ------       ";

// ZUN bug: TH03's list is the only one that correctly aligns this label.
#define LABEL_QUIT "タイトルに戻る"

// ZUN bloat
const shiftjis_t* LABEL_UNUSED = "             ----------------       ";

const shiftjis_t* LABEL_GAME[GAME_COUNT] = {
	"   第１弾　東方靈異伝  Arrange ver  ",
	"   第２弾　東方封魔録  Special MIX  ",
	"   第３弾　東方夢時空  Special MIX  ",
	"   第４弾　東方幻想郷  Special MIX  ",
	"   第５弾　東方怪綺談 MysticSquare  ",
};

const shiftjis_t* MUSIC_CHOICES[GAME_COUNT][TRACKS_MAX] = {{
	// Only 7 of the 14 tracks have identical strings in TH01:
	// * 永遠の巫女
	// * 東方怪奇談
	// * 天使伝説
	// * Oriental Magician
	// * 破邪の小太刀
	// * 魔鏡
	// * アイリス
	// And even those are differently spaced and centered in that game. Reusing
	// their strings would just make both arrays harder to read, and would make
	// it impossible to see the center alignment.
	"No.1           A Sacred Lot         ",
	"No.2            永遠の巫女          ",
	"No.3    The Positive and Negative   ",
	"No.4   Highly Responsive to Prayers ",
	"No.5            東方怪奇談          ",
	"No.6             天使伝説           ",
	"No.7        Oriental Magician       ",
	"No.8           破邪の小太刀         ",
	"No.9               魔鏡             ",
	"No.10       the Legend of KAGE      ",
	"No.11    いざ、倒れ逝くその時まで   ",
	"No.12      Civilization of Magic    ",
	"No.13            星幽天使           ",
	"No.14            アイリス           ",
	"            " LABEL_QUIT "          ",
}, {
	"No.1      " TH02_01 "  ",
	"No.2      " TH02_02 "  ",
	"No.3      " TH02_03 "  ",
	"No.4      " TH02_04 "  ",
	"No.5      " TH02_05 "  ",
	"No.6      " TH02_06 "  ",
	"No.7      " TH02_07 "  ",
	"No.8      " TH02_08 "  ",

	// ZUN bug: This track presents the only alignment inconsistency between
	// the original game and the TH05 Music Room. This particular track wasn't
	// correctly centered in TH02, and this only slightly moves the title to
	// the position it was intended to be.
	// Given ZUN's track record when it comes to these inconsistencies, it's a
	// miracle that all other TH05 strings remained identical, down to even the
	// precise mixture of fullwidth and halfwidth spaces...
	"No.9     " TH02_09 "   ",

	"No.10     " TH02_10 "  ",
	"No.11     " TH02_11 "  ",
	"No.12     " TH02_12 "  ",
	"No.13     " TH02_13 "  ",
	"No.14     " TH02_14 "  ",
	"No.15     " TH02_15 "  ",
	"未使用.1         博麗神社境内       ",
	"未使用.2         　陽落ちて  　     ",
	"未使用.3         　封魔終演  　     ",
	"            " LABEL_QUIT "          ",
}, {
	"No.1     " TH03_01 "  ",
	"No.2     " TH03_02 "  ",
	"No.3     " TH03_03 "  ",
	"No.4     " TH03_04 "  ",
	"No.5     " TH03_05 "  ",
	"No.6     " TH03_06 "  ",
	"No.7     " TH03_07 "  ",
	"No.8     " TH03_08 "  ",
	"No.9     " TH03_09 "  ",
	"No.10    " TH03_10 "  ",
	"No.11    " TH03_11 "  ",
	"No.12    " TH03_12 "  ",
	"No.13    " TH03_13 "  ",
	"No.14    " TH03_14 "  ",
	"No.15    " TH03_15 "  ",
	"No.16    " TH03_16 "  ",
	"No.17    " TH03_17 "  ",
	"No.18    " TH03_18 "  ",
	"No.19    " TH03_19 "  ",
	"No.20            勝利デモ           ",
	"No.21         ゲームオーバー        ",
	"未使用.1          時の風            ",
	"未使用.2     スターボウドリーム     ",
	"未使用.3       Phantasmagoria       ",
	"              " LABEL_QUIT "        ",
}, {
	"No.1   " TH04_01 " ",
	"No.2   " TH04_02 " ",
	"No.3   " TH04_03 " ",
	"No.4   " TH04_04 " ",
	"No.5   " TH04_05 " ",
	"No.6   " TH04_06 " ",
	"No.7   " TH04_07 " ",
	"No.8   " TH04_08 " ",
	"No.9   " TH04_09 " ",
	"No.10  " TH04_10 " ",
	"No.11  " TH04_11 " ",
	"No.12  " TH04_12 " ",
	"No.13  " TH04_13 " ",
	"No.14  " TH04_14 " ",
	"No.15  " TH04_15 " ",
	"No.16  " TH04_16 " ",
	"No.17  " TH04_17 " ",
	"No.18  " TH04_18 " ",
	"No.19  " TH04_19 " ",
	"No.20  " TH04_20 " ",
	"No.21  " TH04_21 " ",
	"No.22  " TH04_22 " ",
	"未使用.1        Lotus Road          ",
	"未使用.2       Dreamy pilot         ",
	"未使用.3      Incomplete Plot       ",
	"未使用.4        Border Land         ",
	"未使用.5   Magic Shop of Raspberry  ",
	"未使用.6       Crescent Dream       ",
	"            " LABEL_QUIT "          ",
}, {
	"No.1  " TH05_01,
	"No.2  " TH05_02,
	"No.3  " TH05_03,
	"No.4  " TH05_04,
	"No.5  " TH05_05,
	"No.6  " TH05_06,
	"No.7  " TH05_07,
	"No.8  " TH05_08,
	"No.9  " TH05_09,
	"No.10 " TH05_10,
	"No.11 " TH05_11,
	"No.12 " TH05_12,
	"No.13 " TH05_13,
	"No.14 " TH05_14,
	"No.15 " TH05_15,
	"No.16 " TH05_16,
	"No.17 " TH05_17,
	"No.18 " TH05_18,
	"No.19 " TH05_19,
	"No.20 " TH05_20,
	"No.21 " TH05_21,
	"No.22 " TH05_22,
	"No.23 " TH05_23,
	"            " LABEL_QUIT "          ",
}};

const char* MUSIC_FILES[GAME_COUNT][TRACKS_MAX] = {{
	"r_00",
	"r_01",
	"r_02",
	"r_03",
	"r_04",
	"r_05",
	"r_06",
	"r_07",
	"r_08",
	"r_09",
	"r_10",
	"r_11",
	"r_12",
	"r_13",
}, {
	"h_op",
	"h_st00",
	"h_st00b",
	"h_st01",
	"h_st01b",
	"h_st02",
	"h_st02b",
	"h_st03",
	"h_st03b",
	"h_st04",
	"h_st04b",
	"h_st05",
	"h_st05b",
	"h_end",
	"h_staff",
	"h_ng00",
	"h_ng01",
	"h_ng02",
}, {
	"y_op",
	"y_select",
	"y_00mm",
	"y_01mm",
	"y_02mm",
	"y_03mm",
	"y_04mm",
	"y_05mm",
	"y_06mm",
	"y_dec",
	"y_07mm",
	"y_08mm",
	"y_demo1",
	"y_demo2",
	"y_demo3",
	"y_demo4",
	"y_demo5",
	"y_ed",
	"y_score",
	"y_win",
	"y_over",
	"y_ng00",
	"y_ng01",
	"y_ng02",
}, {
	"g_op",
	"g_st00",
	"g_st10",
	"g_st00b",
	"g_st01",
	"g_st01b",
	"g_st02",
	"g_st02b",
	"g_st03",
	"g_st03c",
	"g_st03b",
	"g_st04",
	"g_st04b",
	"g_st05",
	"g_st05b",
	"g_st06",
	"g_st06b",
	"g_st06c",
	"g_end1",
	"g_end2",
	"g_staff",
	"g_name",
	"g_ng00",
	"g_ng01",
	"g_ng02",
	"g_ng03",
	"g_ng04",
	"g_ng05",
}, {
	"op",
	"st00",
	"st00b",
	"st01",
	"st01b",
	"st02",
	"st02b",
	"st03",
	"st03b",
	"st03c",
	"st03d",
	"st04",
	"st04b",
	"st05",
	"st05b",
	"st06",
	"st06b",
	"ed00",
	"ed01",
	"ed02",
	"staff",
	"exed",
	"name",
}};
