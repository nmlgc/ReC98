#include "th01/shiftjis/title.hpp"
#include "shiftjis.hpp"
#include "pc98.h"

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
#define REGIST_NAME_SPACES       	"�@�@�@�@�@�@�@�@"
#define REGIST_NAME_BLANK        	"�Q�Q�Q�Q�Q�Q�Q�Q"
#define REGIST_STAGE_ROUTE_DASH  	"�|"
#define REGIST_STAGE_MAKAI       	"���E"
#define REGIST_STAGE_JIGOKU      	"�n��"

#define ALPHABET_A    	"��"
#define ALPHABET_SPACE	"SP"
#define ALPHABET_LEFT 	"��"
#define ALPHABET_RIGHT	"��"
#define ALPHABET_ENTER	"�I"

#define KANJI_A         	kanji_swap('�`')
#define KANJI_a         	kanji_swap('��')
#define KANJI_b         	kanji_swap('��')
#define KANJI_0         	kanji_swap('�O')
#define KANJI_SP        	kanji_swap('�@')
#define KANJI_UNDERSCORE	kanji_swap('�Q')

const shiftjis_kanji_swapped_t ALPHABET_SYMS[] = {
	kanji_swap('�I'), kanji_swap('�H'), kanji_swap('��'), kanji_swap('��'),
	kanji_swap('��'), kanji_swap('��'), kanji_swap('��'), kanji_swap('��'),
	kanji_swap('��'), kanji_swap('��'), kanji_swap('��'), kanji_swap('��'),
	kanji_swap('�c'), kanji_swap('�g'), kanji_swap('�h'), kanji_swap('�^'),
	kanji_swap('�D'), kanji_swap('�E'),
};
