#include "pc98.h"

// ZUN bloat: String alignment consistencies are deliberate and match where the
// strings appear on screen relative to each other. Would be easier to use the
// same left coordinate for all of them.

#define STAFFROLL_TITLE    	  "�����^�@�@�r�s�`�e�e"
#define STAFFROLL_PROGRAM  	"�v���O�����@�@�@�y�t�m"
#define STAFFROLL_GRAPHIC_1	"�O���t�B�b�N�@�y�t�m"
#define STAFFROLL_GRAPHIC_2	"�@�@�@�@�@�@�@��������"
#define STAFFROLL_GRAPHIC_3	"�@�@�@�@�i�I�[���N���A��j"
#define STAFFROLL_MUSIC    	  "�l�t�r�h�b�@�@�y�t�m"
#define STAFFROLL_TESTER_1 	"�s�d�r�s�@�o�k�`�x�d�q"
#define STAFFROLL_TESTER_2 	"�@�@�@�@������"
#define STAFFROLL_TESTER_3 	"�@�@�@�@�b�|�v"
#define STAFFROLL_TESTER_4 	"�@�@ �R�c�@�b��Y"
#define STAFFROLL_TESTER_5 	" ���̑��吨�݂̂Ȃ���"

#define VERDICT_THANKYOU         	"�s���������@�������@�������@��������������"
#define VERDICT_LABEL_SCORE      	     "�@�ŏI���_"
#define VERDICT_LABEL_CONTINUES  	     "�R���e�B�j���["
#define VERDICT_LABEL_RANK       	     "�@ �����N"
#define VERDICT_LABEL_START_LIVES	     "�v���C���[����"
#define VERDICT_LABEL_START_BOMBS	     " �쌂������"
#define VERDICT_LABEL_TITLE      	     "���Ȃ��̘r�O"
#define VERDICT_COPYRIGHT        	     "�P�X�X�V�@�y�t�m  (Amusement Makers)"

// TRANSLATORS: Replace with your longest label.
static const pixel_t VERDICT_LABEL_W = shiftjis_w(VERDICT_LABEL_CONTINUES);
