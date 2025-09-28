#include "pc98.h"

// ZUN bloat: String alignment inconsistencies are deliberate and match where
// the strings appear on screen relative to each other. Would be easier to use
// the same left coordinate for all of them.

#define STAFFROLL_TITLE    	  "封魔録　　ＳＴＡＦＦ"
#define STAFFROLL_PROGRAM  	"プログラム　　　ＺＵＮ"
#define STAFFROLL_GRAPHIC_1	"グラフィック　ＺＵＮ"
#define STAFFROLL_GRAPHIC_2	"　　　　　　　高附日向"
#define STAFFROLL_GRAPHIC_3	"　　　　（オールクリア画）"
#define STAFFROLL_MUSIC    	  "ＭＵＳＩＣ　　ＺＵＮ"
#define STAFFROLL_TESTER_1 	"ＴＥＳＴ　ＰＬＡＹＥＲ"
#define STAFFROLL_TESTER_2 	"　　　　かおる"
#define STAFFROLL_TESTER_3 	"　　　　Ｃ－Ｗ"
#define STAFFROLL_TESTER_4 	"　　 山田　恵一郎"
#define STAFFROLL_TESTER_5 	" その他大勢のみなさん"

#define VERDICT_THANKYOU         	"Ｔｈａｎｋ　ｙｏｕ　ｆｏｒ　ｐｌａｙｉｎｇ"
#define VERDICT_LABEL_SCORE      	     "　最終得点"
#define VERDICT_LABEL_CONTINUES  	     "コンティニュー"
#define VERDICT_LABEL_RANK       	     "　 ランク"
#define VERDICT_LABEL_START_LIVES	     "プレイヤー初期"
#define VERDICT_LABEL_START_BOMBS	     " 霊撃初期数"
#define VERDICT_LABEL_TITLE      	     "あなたの腕前"
#define VERDICT_COPYRIGHT        	     "１９９７　ＺＵＮ  (Amusement Makers)"

// TRANSLATORS: Replace with your longest label.
static const pixel_t VERDICT_LABEL_W = shiftjis_w(VERDICT_LABEL_CONTINUES);
