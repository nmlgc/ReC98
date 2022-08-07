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
#define ALPHABET_LEFT 	"←"
#define ALPHABET_RIGHT	"→"
#define ALPHABET_ENTER	"終"

// ZUN bloat: Storing fullwidth characters as regular 16-bit big-endian
// integers would have worked just fine.
#define kanji_to_le(kanji) ( \
	(static_cast<uint16_t>(kanji) << 8) | (static_cast<uint16_t>(kanji) >> 8) \
)

#define KANJI_A         	kanji_to_le('Ａ')
#define KANJI_a         	kanji_to_le('ａ')
#define KANJI_b         	kanji_to_le('ｂ')
#define KANJI_0         	kanji_to_le('０')
#define KANJI_SP        	kanji_to_le('　')
#define KANJI_UNDERSCORE	kanji_to_le('＿')

const uint16_t ALPHABET_SYMS[] = {
	kanji_to_le('！'), kanji_to_le('？'), kanji_to_le('＃'), kanji_to_le('＆'),
	kanji_to_le('＊'), kanji_to_le('§'), kanji_to_le('☆'), kanji_to_le('◆'),
	kanji_to_le('∞'), kanji_to_le('∴'), kanji_to_le('♂'), kanji_to_le('♀'),
	kanji_to_le('…'), kanji_to_le('“'), kanji_to_le('”'), kanji_to_le('／'),
	kanji_to_le('．'), kanji_to_le('・'),
};
