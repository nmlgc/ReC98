#include "th01/shiftjis/title.hpp"
#include "shiftjis.hpp"
#include "pc98.h"

static const shiftjis_t* REGIST_TITLE[RANK_COUNT] = {
	GAME_TITLE "　強者の記録　　イージー　",
	GAME_TITLE "　強者の記録　　ノーマル　",
	GAME_TITLE "　強者の記録　　ハード　　",
	GAME_TITLE "　強者の記録　ルナティック",
};

#define REGIST_HEADER_PLACE      	"　霊　位　"
#define REGIST_HEADER_NAME       	"　　名　　前　　"
#define REGIST_HEADER_SCORE      	"　　得　　点　　"
#define REGIST_HEADER_STAGE_ROUTE	"ステージ・ルート"
#define REGIST_PLACE_0           	"　靈　神　"
#define REGIST_PLACE_1           	"太元帥明王"
#define REGIST_PLACE_2           	"　天　仙　"
#define REGIST_PLACE_3           	"　神　仙　"
#define REGIST_PLACE_4           	"　地　仙　"
#define REGIST_PLACE_5           	"　人　仙　"
#define REGIST_PLACE_6           	"　仙　女　"
#define REGIST_PLACE_7           	"陰　陽　師"
#define REGIST_PLACE_8           	"靈　媒　師"
#define REGIST_PLACE_9           	"修　業　者"
#define REGIST_NAME_BLANK        	"＿＿＿＿＿＿＿＿"
#define REGIST_STAGE_ROUTE_DASH  	"－"
#define REGIST_STAGE_MAKAI       	"魔界"
#define REGIST_STAGE_JIGOKU      	"地獄"

#define ALPHABET_A    	"ａ"
#define ALPHABET_SPACE	"SP"

static const shiftjis_kanji_t KANJI_A          = 'Ａ';
static const shiftjis_kanji_t KANJI_a          = 'ａ';
static const shiftjis_kanji_t KANJI_b          = 'ｂ';
static const shiftjis_kanji_t KANJI_0          = '０';
static const shiftjis_kanji_t KANJI_SPACE      = '　';
static const shiftjis_kanji_t KANJI_LEFT       = '←';
static const shiftjis_kanji_t KANJI_RIGHT      = '→';
static const shiftjis_kanji_t KANJI_ENTER      = '終';
static const shiftjis_kanji_t KANJI_UNDERSCORE = '＿';

const shiftjis_kanji_t ALPHABET_SYMS[] = {
	'！', '？', '＃', '＆', '＊', '§', '☆', '◆', '∞',
	'∴', '♂', '♀', '…', '“', '”', '／', '．', '・',
};
