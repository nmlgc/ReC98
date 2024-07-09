#include "pc98.h"
#include "shiftjis.hpp"

static const int HELP_LINES = 9;
static const pixel_t HELP_W = (46 * GLYPH_HALF_W);

shiftjis_t* BGM_HELP[HELP_LINES] = {
	"�X�e���I�e�l�����FPC-9801-86(�݊�)�{�[�h�@�@�@",
	"�@�@�@�@�@�@�@�@�@CanBe���������ȂǁA         ",
	"�@�@�@�@�@�@�@�e�l�U���{�r�r�f�R���{���Y������",
	"�@�W���e�l�����F  PC-9801-26K(�݊�)�{�[�h     ",
	"                  PC-9801DA���ɓ����̉����Ȃ� ",
	"�@�@�@�@�@�@�@�@�@�e�l�R���{�r�r�f�R��        ",
	"�@�@���y�����F�@�@�e�l�����������ꍇ          ",
	"                                              ",
	"�Ȃ��A�����̐ݒ�͂n�����������ŕύX�\�ł�",
};

shiftjis_t* SE_HELP[HELP_LINES] = {
	"�@�e�l�����@�F���ʉ��ɂe�l�������g�p���܂��@�@",
	"�@�@�@�@�@�@�@�a�f�l���X�e���I�e�l�����������@",
	"�@ �@ �@�@�i�W���e�l�����ł́A3ch���g�p���܂� ",
	"�@ �@�@�@�@ �̂ŁA�a�f�l������ɂ����Ȃ������j",
	"�a�����������F���ʉ��ɂa�������������g�p���܂�",
	"              �e�l�����������ꍇ�g�p���܂��@�@",
	" ���ʉ����� �F���炩�̎���Ō��ʉ���炵����",
	"�@�@�@�@�@�@�@�����ꍇ                        ",
	"�Ȃ��A�����̐ݒ�͂n�����������ŕύX�\�ł�",
};

#define BGM_CHOICE_FM86	"�X�e���I�e�l����"
#define BGM_CHOICE_FM26	"�@�W���e�l�����@"
#define BGM_CHOICE_OFF 	"�@�@���y�����@�@"

#define SE_CHOICE_FM  	"�@�@�e�l�����@�@"
#define SE_CHOICE_BEEP	"�@�a�����������@"
#define SE_CHOICE_OFF 	"�@ ���ʉ����� �@"

// ZUN bloat: Why not centered? That's why we have to hardcode the length for
// those as well, even though we could infer it.
#define SETUP_BGM_CAPTION	"�@�@�@�@�@�g�p���鉹����I�����ĉ������ˁ�"
#define SETUP_SE_CAPTION 	"�@�@�@�@���ʉ��Ɏg�p���鉹����I�����Ăˁ�"

static const pixel_t CAPTION_W = (52 * GLYPH_HALF_W);
