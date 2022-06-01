
// Verdict screen
// --------------

#define VERDICT_RANK            "��Փx�@�@�@�@�@�@�@�@�@�@  "
#define VERDICT_SCORE_HIGHEST   "����̍ō����_�@�@�@�@�@�@  "
#define VERDICT_SCORE           "�ŏI���_�@�@�@�@�@�@�@�@�@  "
#define VERDICT_SCENE_CONTINUES "�R���e�B�j���[��"
#define VERDICT_SHRINE          "�@�_�Ё@�@�@�@�i�P�ʁ`�T�ʁj �@ "
#define VERDICT_MAKAI_1         "�@�Q�[�g�@�@�@�i�U�ʁ`�P�O�ʁj  "
#define VERDICT_MAKAI_2         "  ���B�i�̔p�Ёi�P�P�ʁ`�P�T�ʁj"
#define VERDICT_MAKAI_3         "  ������_�a�i�P�T�ʁ`�Q�O�ʁj"
#define VERDICT_JIGOKU_1        "�@�K�@�@�@�@�@�i�U�ʁ`�P�O�ʁj  "
#define VERDICT_JIGOKU_2        "�@���̕��E�@�@�i�P�P�ʁ`�P�T�ʁj"
#define VERDICT_JIGOKU_3        "�@�Â��Ȃ�_�a�i�P�T�ʁ`�Q�O�ʁj"
#define VERDICT_MAKAI_TOTAL     "  ���E���[�g�����@�@�@�@�@�@  "
#define VERDICT_JIGOKU_TOTAL    "�@�n�����[�g�����@�@�@�@�@�@�@"
#define VERDICT_THANKYOU        "    Thank you for Playing !! "
// (yes, outdented by 4 spaces)
#define VERDICT_TITLE       "���������Ȃ��̏̍�������"

// Adding 7 for the rank itself
static const pixel_t VERDICT_W = shiftjis_w(VERDICT_RANK "LUNATIC");
static const pixel_t VERDICT_TITLE_LEFT_OFFSET = shiftjis_w("    ");
static const pixel_t VERDICT_TITLE_PADDED_W = shiftjis_w(VERDICT_TITLE "    ");

static const int VERDICT_GROUPS = 3;
static const int VERDICT_LEVELS = 6;
extern const unsigned char *VERDICT_TITLES[VERDICT_GROUPS][VERDICT_LEVELS];
// --------------
