/* ReC98
 * -----
 * Include file for TH02
 */

#include "ReC98.h"
#include "th01/ranks.h"

#undef grcg_off

// Formats
// -------
typedef struct {
	char magic[4]; // = "MPTN"
	char count;
	char unused;
} mptn_header_t;

#define MPTN_SIZE (8 * 16)

extern char mptn_show_palette_on_load;
extern unsigned char mptn_count;
extern int *mptn_buffer;
extern char mptn_palette[16 * 3];

int pascal mptn_load(const char *fn);
void pascal mptn_palette_show(void);
void pascal mptn_free(void);

// "東方封魔.録" in Shift-JIS
#define PF_FN "\x93\x8C\x95\xFB\x95\x95\x96\x82\x2E\x98\x5E"
#define PF_KEY 0x12
// -------

// Hardware
// -------
#define graph_clear_both() \
	graph_accesspage(1);	graph_clear(); \
	graph_accesspage(0);	graph_clear(); \
	graph_accesspage(0);	graph_showpage(0);

#include "th01/hardware/grppsafx.h"
// -------

// Music Room
#define MUSIC_CMT_FILE "MUSIC.TXT"
#define MUSIC_CMT_LINE_LEN 42
#define MUSIC_CMT_LINE_COUNT 20

extern char unused_op_2_3; // Maybe debug mode?
extern char rank;
extern char lives;
extern char bombs;

#define SHOTTYPE_COUNT 3
