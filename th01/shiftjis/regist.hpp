#include "th01/shiftjis/title.hpp"

#define REGIST_TITLE             	GAME_TITLE "　強者の記録"
#define REGIST_TITLE_WITH_SPACE  	REGIST_TITLE "　"
#define REGIST_TITLE_RANKS { \
	"　イージー　", \
	"　ノーマル　", \
	"　ハード　　", \
	"ルナティック", \
}

static const pixel_t REGIST_TITLE_W = shiftjis_w(REGIST_TITLE_WITH_SPACE);

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
#define REGIST_NAME_SPACES       	"　　　　　　　　"
#define REGIST_NAME_BLANK        	"＿＿＿＿＿＿＿＿"
#define REGIST_STAGE_ROUTE_DASH  	"－"
#define REGIST_STAGE_MAKAI       	"魔界"
#define REGIST_STAGE_JIGOKU      	"地獄"

#define ALPHABET_A    	"ａ"
#define ALPHABET_SPACE	"SP"

#define KANJI_A         	kanji_swap('Ａ')
#define KANJI_a         	kanji_swap('ａ')
#define KANJI_b         	kanji_swap('ｂ')
#define KANJI_0         	kanji_swap('０')
#define KANJI_SPACE     	kanji_swap('　')
#define KANJI_LEFT      	kanji_swap('←')
#define KANJI_RIGHT     	kanji_swap('→')
#define KANJI_ENTER     	kanji_swap('終')
#define KANJI_UNDERSCORE	kanji_swap('＿')

const shiftjis_kanji_swapped_t ALPHABET_SYMS[] = {
	kanji_swap('！'), kanji_swap('？'), kanji_swap('＃'), kanji_swap('＆'),
	kanji_swap('＊'), kanji_swap('§'), kanji_swap('☆'), kanji_swap('◆'),
	kanji_swap('∞'), kanji_swap('∴'), kanji_swap('♂'), kanji_swap('♀'),
	kanji_swap('…'), kanji_swap('“'), kanji_swap('”'), kanji_swap('／'),
	kanji_swap('．'), kanji_swap('・'),
};
