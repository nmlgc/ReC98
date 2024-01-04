#include "th03/shiftjis/bgm.hpp"
#include "th03/shiftjis/fns.hpp"

const shiftjis_t* MUSIC_CHOICES[] = {
	"NO.1   " TH03_01,
	"NO.2   " TH03_02,
	"NO.3   " TH03_03,
	"NO.4   " TH03_04,
	"NO.5   " TH03_05,
	"NO.6   " TH03_06,
	"NO.7   " TH03_07,
	"NO.8   " TH03_08,
	"NO.9   " TH03_09,
	"NO.10  " TH03_10,
	"NO.11  " TH03_11,
	"NO.12  " TH03_12,
	"NO.13  " TH03_13,
	"NO.14  " TH03_14,
	"NO.15  " TH03_15,
	"NO.16  " TH03_16,
	"NO.17  " TH03_17,
	"NO.18  " TH03_18,
	"NO.19  " TH03_19,
	"           Å@Å@                 ", // ZUN bloat
	"       " TH03_QT,
};

const char* MUSIC_FILES[] = {
	BGM_MENU_MAIN_FN,
	"select.m",
	"00mm.m",
	"01mm.m",
	"02mm.m",
	"03mm.m",
	"04mm.m",
	"05mm.m",
	"06mm.m",
	"dec.m",
	"07mm.m",
	"08mm.m",
	"demo1.m",
	"demo2.m",
	"demo3.m",
	"demo4.m",
	"demo5.m",
	"ed.m",
	"score.m\0MUSIC.TXT\0op3.pi",
};
