#include "pc98.h"

// Pause menu
// ----------

#define PAUSE_TITLE         	"ＰＡＵＳＥ"
#define PAUSE_CHOICE_RESUME 	"再開"
#define PAUSE_CHOICE_QUIT   	"終了"

#define QUIT_TITLE     	"本当に終了しちゃうの？"
#define QUIT_CHOICE_NO 	"うそですぅ"
#define QUIT_CHOICE_YES	"はいっ"

// ZUN bloat: Does this mean that this menu used to be shown in text RAM?
#define PAUSE_CURSOR_INITIAL	"●　　　　　　"

#define PAUSE_CURSOR        	"●"

// Leaving one fullwidth space for the cursor in front of each, and another
// one to right-pad the first option.
#define PAUSE_CHOICE_0	"　" PAUSE_CHOICE_RESUME "　"
#define PAUSE_CHOICE_1	"　" PAUSE_CHOICE_QUIT
#define QUIT_CHOICE_0 	"　" QUIT_CHOICE_NO "　"
#define QUIT_CHOICE_1 	"　" QUIT_CHOICE_YES
#define PAUSE_CHOICES 	PAUSE_CHOICE_0 PAUSE_CHOICE_1
#define QUIT_CHOICES  	QUIT_CHOICE_0 QUIT_CHOICE_1
// ----------

// Continue menu
// -------------
// ZUN bloat: Note the subtle whitespace differences, and how they keep us from
// calculating any of the actual used widths.

#define CONTINUE_TITLE	"ｃｏｎｔｉｎｕｅ？　　　  "
#define CONTINUE_YES_1	        "Ｙｅｓ　　  　"
#define CONTINUE_NO_1 	        "Ｎｏ　　  　 "
#define CONTINUE_YES_2	        "Ｙｅｓ　　　  "
#define CONTINUE_NO_2 	        "Ｎｏ　　　   "

static const pixel_t CONTINUE_TITLE_W = (9 * GLYPH_FULL_W);
static const pixel_t CONTINUE_CHOICE_W = (3 * GLYPH_FULL_W);
// -------------
