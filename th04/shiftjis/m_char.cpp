static const int PLAYCHAR_TITLE_LEN = 24;
static const int PLAYCHAR_TITLE_LINES = 2;
static const int SHOTTYPE_TITLE_LEN = 24;
static const int SHOTTYPE_CHOOSE_LEN = 21;

const shiftjis_t* PLAYCHAR_TITLE[PLAYCHAR_COUNT][PLAYCHAR_TITLE_LINES] = {
	{ "@νθΛ²iή³ρj ", "     LΝΝU^@    " },
	{ " ΆJΉi@g’j", "     UΝd^      " },
};

const shiftjis_t* SHOTTYPE_TITLE[PLAYCHAR_COUNT][SHOTTYPE_COUNT] = {
	{ "@  T[`Vbg@  ", "    ChVbg    " },
	{ "C[W[U[", "   sbhVbg   " },
};

#define SHOTTYPE_CLEARED ""
#define SHOTTYPE_CHOOSE "TuEF|ΜIπ"
