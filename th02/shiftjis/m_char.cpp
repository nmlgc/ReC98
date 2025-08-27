#include "th02/common.h"
#include "shiftjis.hpp"

const shiftjis_t *DESC[SHOTTYPE_COUNT][3] = {
	" �A�z�ʂ̗͂��g��Ȃ� ",
	" �L�͈͂ł��@���͂� ",
	"�@�������@���̓^�C�v�@",

	" �@�ˌ����D��Ă��� �@",
	"�@ �o�����X�̎�ꂽ�@ ",
	"�@�@�h��d���^�C�v�@�@",

	" �@�A�z�ʂ̗͂Ő키   ",
	"�@�U���͂��D��Ă���@",
	"�@�@�U���d���^�C�v�@�@"
};
const shiftjis_t *CHOOSE = "�˖��̐퓬�X�^�C�����A���̂R���炦���ł�";
const shiftjis_t *EXTRA_NOTE[] = {
	"���j�@�G�L�X�g���X�e�[�W�ł́A��Փx�A�v���C���[�A�{�����͕ύX�o���܂���",
	"�@�@�@���ꂼ��A��Փx�d�w�s�q�`�A�v���C���[�R�l�A�{���P�ƂȂ�܂�    "
};
const shiftjis_t *CLEARED = "  �����b�k�d�`�q�d�c����  ";
