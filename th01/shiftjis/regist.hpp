#include "th01/shiftjis/title.hpp"

#define REGIST_TITLE             	GAME_TITLE "�@���҂̋L�^"
#define REGIST_TITLE_WITH_SPACE  	REGIST_TITLE "�@"
#define REGIST_TITLE_RANKS { \
	"�@�C�[�W�[�@", \
	"�@�m�[�}���@", \
	"�@�n�[�h�@�@", \
	"���i�e�B�b�N", \
}

static const pixel_t REGIST_TITLE_W = shiftjis_w(REGIST_TITLE_WITH_SPACE);

#define REGIST_HEADER_PLACE      	"�@��@�ʁ@"
#define REGIST_HEADER_NAME       	"�@�@���@�@�O�@�@"
#define REGIST_HEADER_SCORE      	"�@�@���@�@�_�@�@"
#define REGIST_HEADER_STAGE_ROUTE	"�X�e�[�W�E���[�g"
#define REGIST_PLACE_0           	"�@�ˁ@�_�@"
#define REGIST_PLACE_1           	"����������"
#define REGIST_PLACE_2           	"�@�V�@��@"
#define REGIST_PLACE_3           	"�@�_�@��@"
#define REGIST_PLACE_4           	"�@�n�@��@"
#define REGIST_PLACE_5           	"�@�l�@��@"
#define REGIST_PLACE_6           	"�@��@���@"
#define REGIST_PLACE_7           	"�A�@�z�@�t"
#define REGIST_PLACE_8           	"�ˁ@�}�@�t"
#define REGIST_PLACE_9           	"�C�@�Ɓ@��"
#define REGIST_NAME_BLANK        	"�Q�Q�Q�Q�Q�Q�Q�Q"
#define REGIST_STAGE_ROUTE_DASH  	"�|"
#define REGIST_STAGE_MAKAI       	"���E"
#define REGIST_STAGE_JIGOKU      	"�n��"

#define ALPHABET_A    	"��"
#define ALPHABET_SPACE	"SP"

static const shiftjis_kanji_t KANJI_A          = '�`';
static const shiftjis_kanji_t KANJI_a          = '��';
static const shiftjis_kanji_t KANJI_b          = '��';
static const shiftjis_kanji_t KANJI_0          = '�O';
static const shiftjis_kanji_t KANJI_SPACE      = '�@';
static const shiftjis_kanji_t KANJI_LEFT       = '��';
static const shiftjis_kanji_t KANJI_RIGHT      = '��';
static const shiftjis_kanji_t KANJI_ENTER      = '�I';
static const shiftjis_kanji_t KANJI_UNDERSCORE = '�Q';

const shiftjis_kanji_t ALPHABET_SYMS[] = {
	'�I', '�H', '��', '��', '��', '��', '��', '��', '��',
	'��', '��', '��', '�c', '�g', '�h', '�^', '�D', '�E',
};
