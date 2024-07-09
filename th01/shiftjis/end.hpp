#include "pc98.h"
#include "shiftjis.hpp"

// Endings
// -------

#define END_BAD_LINE_1        	"Try to 'No continue'!!"
#define END_BAD_LINE_2_MAKAI  	"      Bad Ending1     "
#define END_BAD_LINE_2_JIGOKU 	"      Bad Ending2     "
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
const shiftjis_t *VERDICT_TITLES[VERDICT_GROUPS][VERDICT_LEVELS] = { {
	"�@�����L�[�@",
	"�@�ސl��",
	"�z���T�s�G���X",
	"�@���l",
	"�@�ː_�@",
	"�@�_�𒴉z"
}, {
	"���q�l�Q�[�}�[",
	"����X�R�A���[",
	"�~�h���X�R�A���[",
	"�n�C�X�R�A���[",
	"�X�[�p�[�Q�[�}�[",
	"�Q�[�}�[�𒴉z",
}, {
	"�������݂���",
	"�U�b�N�[���̎�",
	"�֒f�̗ь�",
	"���E���̗t",
	"�����C�_�O�o",
	"�@�A�����^"
} };
// --------------
