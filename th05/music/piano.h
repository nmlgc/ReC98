#define PIANO_X 384
#define PIANO_Y 64
#define PIANO_H 15
#define PIANO_PADDING_BOTTOM 3
#define PIANO_H_PADDED (PIANO_H + PIANO_PADDING_BOTTOM)

// Using the same naming convention as for the gaiji characters...
#pragma option -b-
typedef enum {
	pl_F = 0,
	pl_M = 1,
	pl_1 = 2,
	pl_2 = 3,
	pl_3 = 4,
	pl_4 = 5,
	pl_5 = 6,
	pl_S = 7,
	pl_G = 8,
	pl_COUNT,
} piano_label_t;
#pragma option -b

#define PIANO_LABEL_FONT_H 8

extern const unsigned char PIANO_LABEL_FONT[pl_COUNT][PIANO_LABEL_FONT_H];

#define PIANO_LABEL_DIST_X 32
#define PIANO_LABEL_DIST_Y 4

#define PIANO_LABEL_X(col) (PIANO_X - PIANO_LABEL_DIST_X + (col * PIANO_LABEL_FONT_W))
#define PIANO_LABEL_Y(row) (PIANO_Y + PIANO_LABEL_DIST_Y + (row * PIANO_H_PADDED))

// Assumes that the GRCG is active.
#define piano_label_puts(row, chr1, chr2, chr3) \
	piano_label_putc(0, row, chr1); \
	piano_label_putc(1, row, chr2); \
	piano_label_putc(2, row, chr3); \

#define piano_label_putc(col, row, chr) \
	_AL = chr; \
	_DI = (PIANO_LABEL_Y(row) * ROW_SIZE) + (PIANO_LABEL_X(col) / 8); \
	piano_label_put_raw();

void pascal piano_label_put_raw();
