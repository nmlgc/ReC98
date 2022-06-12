// Endings
// -------

#define END_GOOD_LINE_1       	"Congratulations!"
#define END_GOOD_LINE_2_MAKAI 	"     Good Ending1     "
#define END_GOOD_LINE_2_JIGOKU	"     Good Ending2     "
// -------

// Boss slideshow
// --------------

#define SLIDES_TITLE_5       	"STAGE 5 BOSS"
#define SLIDES_TITLE_10      	"STAGE 10 BOSS"
#define SLIDES_TITLE_15      	"STAGE 15 BOSS"
#define SLIDES_TITLE_20      	"STAGE 20 BOSS"
#define SLIDES_BOSS_5        	"Gatekeeper 'SinGyoku'"
#define SLIDES_BOSS_10_MAKAI 	"EvilEyes 'YuugenMagan'"
#define SLIDES_BOSS_10_JIGOKU	"Revengeful Ghost 'Mima'"
#define SLIDES_BOSS_15_MAKAI 	"Innocence Devil 'Elis'"
#define SLIDES_BOSS_15_JIGOKU	"HellMoon 'Kikuri'"
#define SLIDES_BOSS_20_MAKAI 	"Angel of Death'Sariel'"
#define SLIDES_BOSS_20_JIGOKU	"Astral Knight 'Konngara'"
// --------------

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
