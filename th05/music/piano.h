/// Graphics
/// --------
#define PIANO_LEFT 384
#define PIANO_TOP 64
#define PIANO_H 15
#define PIANO_KEY_W 4
#define PIANO_BLACK_H 9
#define PIANO_BLACK_PRESSED_H 8
#define PIANO_PADDING_BOTTOM 3
#define PIANO_H_PADDED (PIANO_H + PIANO_PADDING_BOTTOM)

#define PIANO_OCTAVES 8
#define PIANO_OCTAVE_W (7 * PIANO_KEY_W)

#define PIANO_VRAM_LEFT (PIANO_LEFT / BYTE_DOTS)
#define PIANO_VRAM_W ((PIANO_OCTAVES * PIANO_OCTAVE_W) / BYTE_DOTS)

// Sprite data
extern const dots8_t PIANO_KEYS_BLACK[PIANO_VRAM_W];
/// --------

#define PIANO_LABEL_DIST_X 32
#define PIANO_LABEL_DIST_Y 4

#define PIANO_LABEL_LEFT(col) \
	(PIANO_LEFT - PIANO_LABEL_DIST_X + (col * PIANO_LABEL_FONT_W))
#define PIANO_LABEL_TOP(row) \
	(PIANO_TOP  + PIANO_LABEL_DIST_Y + (row * PIANO_H_PADDED))

// Assumes that the GRCG is active.
#define piano_label_puts(row, chr1, chr2, chr3) \
	piano_label_putc(0, row, chr1); \
	piano_label_putc(1, row, chr2); \
	piano_label_putc(2, row, chr3); \

#define piano_label_putc(col, row, chr) \
	_AL = chr; \
	_DI = vram_offset_muldiv(PIANO_LABEL_LEFT(col), PIANO_LABEL_TOP(row)); \
	piano_label_put_raw();

void pascal piano_label_put_raw();

// Note data
// ---------
extern OPEN_WORK *pmd_workadr;

typedef struct {
	char fm[5];
	char unused[3]; // SSG?
} piano_notes_t;

extern piano_notes_t piano_notes_cur;
extern piano_notes_t piano_notes_prev;
// ---------

void piano_setup(void);
void piano_render(void);
