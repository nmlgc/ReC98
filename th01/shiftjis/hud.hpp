#include "pc98.h"

// Pause menu
// ----------

#define PAUSE_TITLE         	"�o�`�t�r�d"
#define PAUSE_CHOICE_RESUME 	"�ĊJ"
#define PAUSE_CHOICE_QUIT   	"�I��"

#define QUIT_TITLE     	"�{���ɏI�������Ⴄ�́H"
#define QUIT_CHOICE_NO 	"�����ł���"
#define QUIT_CHOICE_YES	"�͂���"

// ZUN bloat: Does this mean that this menu used to be shown in text RAM?
#define PAUSE_CURSOR_INITIAL	"���@�@�@�@�@�@"

#define PAUSE_CURSOR        	"��"

// Leaving one fullwidth space for the cursor in front of each, and another
// one to right-pad the first option.
#define PAUSE_CHOICE_0	"�@" PAUSE_CHOICE_RESUME "�@"
#define PAUSE_CHOICE_1	"�@" PAUSE_CHOICE_QUIT
#define QUIT_CHOICE_0 	"�@" QUIT_CHOICE_NO "�@"
#define QUIT_CHOICE_1 	"�@" QUIT_CHOICE_YES
#define PAUSE_CHOICES 	PAUSE_CHOICE_0 PAUSE_CHOICE_1
#define QUIT_CHOICES  	QUIT_CHOICE_0 QUIT_CHOICE_1
// ----------

// Continue menu
// -------------
// ZUN bloat: Note the subtle whitespace differences, and how they keep us from
// calculating any of the actual used widths.

#define CONTINUE_TITLE	"�����������������H�@�@�@  "
#define CONTINUE_YES_1	        "�x�����@�@  �@"
#define CONTINUE_NO_1 	        "�m���@�@  �@ "
#define CONTINUE_YES_2	        "�x�����@�@�@  "
#define CONTINUE_NO_2 	        "�m���@�@�@   "

static const pixel_t CONTINUE_TITLE_W = (9 * GLYPH_FULL_W);
static const pixel_t CONTINUE_CHOICE_W = (3 * GLYPH_FULL_W);
// -------------
