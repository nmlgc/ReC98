
// Verdict screen
// --------------

#define VERDICT_RANK            "難易度　　　　　　　　　　  "
#define VERDICT_SCORE_HIGHEST   "今回の最高得点　　　　　　  "
#define VERDICT_SCORE           "最終得点　　　　　　　　　  "
#define VERDICT_SCENE_CONTINUES "コンティニュー回数"
#define VERDICT_SHRINE          "　神社　　　　（１面～５面） 　 "
#define VERDICT_MAKAI_1         "　ゲート　　　（６面～１０面）  "
#define VERDICT_MAKAI_2         "  ヴィナの廃墟（１１面～１５面）"
#define VERDICT_MAKAI_3         "  堕ちたる神殿（１５面～２０面）"
#define VERDICT_JIGOKU_1        "　祠　　　　　（６面～１０面）  "
#define VERDICT_JIGOKU_2        "　炎の腐界　　（１１面～１５面）"
#define VERDICT_JIGOKU_3        "　静かなる神殿（１５面～２０面）"
#define VERDICT_MAKAI_TOTAL     "  魔界ルート総合　　　　　　  "
#define VERDICT_JIGOKU_TOTAL    "　地獄ルート総合　　　　　　　"
#define VERDICT_THANKYOU        "    Thank you for Playing !! "
// (yes, outdented by 4 spaces)
#define VERDICT_TITLE       "★★★あなたの称号★★★"

// Adding 7 for the rank itself
static const pixel_t VERDICT_W = shiftjis_w(VERDICT_RANK "LUNATIC");
static const pixel_t VERDICT_TITLE_LEFT_OFFSET = shiftjis_w("    ");
static const pixel_t VERDICT_TITLE_PADDED_W = shiftjis_w(VERDICT_TITLE "    ");

static const int VERDICT_GROUPS = 3;
static const int VERDICT_LEVELS = 6;
extern const unsigned char *VERDICT_TITLES[VERDICT_GROUPS][VERDICT_LEVELS];
// --------------
