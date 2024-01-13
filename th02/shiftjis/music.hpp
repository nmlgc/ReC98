#include "th02/shiftjis/bgm.hpp"
#include "th02/shiftjis/fns.hpp"

// ZUN quirk: TH02 first lists all 5 stage themes of the main game, followed by
// all 5 boss themes.
const shiftjis_t* MUSIC_CHOICES[] = {
	"NO.1    " TH02_01,
	"NO.2    " TH02_02,
	"NO.3    " TH02_04,
	"NO.4    " TH02_06,
	"NO.5    " TH02_08,
	"NO.6    " TH02_10,
	"NO.7    " TH02_03,
	"NO.8    " TH02_05,
	"NO.9    " TH02_07,
	"NO.10   " TH02_09,
	"NO.11   " TH02_11,
	"NO.12   " TH02_14,
	"NO.13   " TH02_15,
	"NO.14   " TH02_12,
	"NO.15   " TH02_13,
	"           Å@Å@                 ", // ZUN bloat
	"        " TH02_QT,
};

const char* MUSIC_FILES[] = {
	BGM_MENU_MAIN_FN,
	"stage0.m",
	"stage1.m",
	"stage2.m",
	"stage3.m",
	"stage4.m",
	"boss1.m",
	"boss4.m",
	"boss2.m",
	"boss3.m",
	"mima.m",
	"end1.m",
	"ending.m",
	"stage5.m",
	"boss5.m",
};
