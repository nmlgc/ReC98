#include "pc98.h"

#define HIT_KEY " �g�h�s�@�j�d�x"

#define MAIN_CHOICES { \
	"   �r�s�`�q�s   ", \
	"�b�n�m�s�h�m�t�d", \
	"�@�n�o�s�h�n�m�@", \
	"�@�@�p�t�h�s�@�@", \
}

static const pixel_t MAIN_CHOICE_W = (9 * GLYPH_FULL_W);

#define OPTION_CHOICES { \
	"�@�q�`�m�j�@ ", \
	" �l�t�r�h�b  ", \
	"�o�k�`�x�d�q ", \
	"�l�D�s�d�r�s ", \
	"�@�p�t�h�s�@ ", \
}

#define MUSIC_CHOICES { \
	"�l�t�r�h�b�@�m���D", \
	"�@�@�p������      ", \
}

#define MUSIC_TITLES { \
	"    A Sacret Lot", \
	"      ���̐_��     ", \
	"     �i���̛ޏ�    ", \
	"  Highly Responsive", \
	"     ��������k    ", \
	"  Oriental Magician", \
	"�@  �j�ׂ̏������@ ", \
	" The Legend of KAGE", \
	"Positive and Negative", \
	"�@�@  �V�g�`���@�@ ", \
	"�@�@�@  �����@�@�@ ", \
	"�����|��������̎��܂�", \
	"�@�@���Ȃ΂���Ƃ��@�@", \
	"�@�@  ���H���m", \
	"�@�@�@�A�C���X", \
}

#define GOODBYE "�����ꂳ�܂ł����I�I\n"
