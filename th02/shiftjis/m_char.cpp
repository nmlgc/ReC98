#include "th02/common.h"
#include "shiftjis.hpp"

const shiftjis_t *DESC[SHOTTYPE_COUNT][3] = {
	" 陰陽玉の力を使わない ",
	" 広範囲でかつ機動力に ",
	"　強い高機動力タイプ　",

	" 　靈撃が優れている 　",
	"　 バランスの取れた　 ",
	"　　防御重視タイプ　　",

	" 　陰陽玉の力で戦う   ",
	"　攻撃力が優れている　",
	"　　攻撃重視タイプ　　"
};
const shiftjis_t *CHOOSE = "靈夢の戦闘スタイルを、下の３つからえらんでね";
const shiftjis_t *EXTRA_NOTE[] = {
	"注）　エキストラステージでは、難易度、プレイヤー、ボム数は変更出来ません",
	"　　　それぞれ、難易度ＥＸＴＲＡ、プレイヤー３人、ボム１個となります    "
};
const shiftjis_t *CLEARED = "  ☆☆ＣＬＥＡＲＥＤ☆☆  ";
