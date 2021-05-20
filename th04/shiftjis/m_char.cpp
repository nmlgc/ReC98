static const int PLAYCHAR_TITLE_LEN = 24;
static const int PLAYCHAR_TITLE_LINES = 2;
static const int SHOTTYPE_TITLE_LEN = 24;
static const int SHOTTYPE_CHOOSE_LEN = 21;

const unsigned char *PLAYCHAR_TITLE[PLAYCHAR_COUNT][PLAYCHAR_TITLE_LINES] = {
	{ "　博麗靈夢（巫女さん） ", "     広範囲攻撃型　    " },
	{ " 霧雨魔理沙（魔法使い）", "     攻撃力重視型      " },
};

const unsigned char *SHOTTYPE_TITLE[PLAYCHAR_COUNT][SHOTTYPE_COUNT] = {
	{ "　  サーチショット　  ", "    ワイドショット    " },
	{ "イリュージョンレーザー", "   ラピッドショット   " },
};

#define SHOTTYPE_CLEARED "☆"
#define SHOTTYPE_CHOOSE "サブウェポンの選択"
