#define COL_SELECTED 3
#define COL_REGULAR 7

#define ALPHABET_TOP 240
#define MARGIN_W 32
#define KANJI_PADDING_X 16
#define KANJI_PADDING_Y 8

#define KANJI_PADDED_W (GLYPH_FULL_W + KANJI_PADDING_X)
#define KANJI_PADDED_H (GLYPH_H + KANJI_PADDING_Y)

#define KANJI_PER_ROW \
	((RES_X - (MARGIN_W * 2)) / KANJI_PADDED_W)

#define relative_top(row) \
	((row) * KANJI_PADDED_H)

inline int relative_top_for(int kanji_id)
{
	return relative_top(kanji_id / KANJI_PER_ROW);
}

inline int row_ceil(int count)
{
	return ((count + (KANJI_PER_ROW - 1)) / KANJI_PER_ROW);
}

inline int left_for(int kanji_id)
{
	return (((kanji_id % KANJI_PER_ROW) * KANJI_PADDED_W) + MARGIN_W);
}

#define alphabet_putca_fx(top_for_0, i, fx, fmt_instance, kanji) \
	graph_putkanji_fx( \
		left_for(i), (top_for_0 + relative_top_for(i)), fx, fmt_instance, kanji \
	);

#define alphabet_putsa_fx(top_for_0, i, fx, str) \
	extern const char str[]; \
	graph_printf_fx(left_for(i), (top_for_0 + relative_top_for(i)), fx, str);

#define A_TO_Z_COUNT 26
#define NUM_COUNT 10
// TODO: Should be derived via `sizeof()` once the array is declared here.
#define SYM_COUNT 18
extern const uint16_t ALPHABET_SYMS[];

// Rows
#define LOWER_TOP (ALPHABET_TOP)
#define UPPER_TOP (LOWER_TOP + relative_top(row_ceil(A_TO_Z_COUNT)))
#define SYM_TOP (UPPER_TOP + relative_top(row_ceil(A_TO_Z_COUNT)))
#define NUM_TOP (SYM_TOP + relative_top(row_ceil(SYM_COUNT)))

inline uint16_t kanji_swap(uint16_t kanji)
{
	return (kanji << 8) | (kanji >> 8);
}

void alphabet_put_initial()
{
	int fx = FX(COL_REGULAR, 2, 0);
	uint16_t kanji;
	int i;
#if (BINARY == 'M')
	char kanji_str[3];
#endif

	kanji = kanji_swap('‚‚');
	for(i = 1; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(LOWER_TOP, i, fx, 0, kanji);
		kanji++;
	}
	extern const char ALPHABET_A[];
	graph_putsa_fx(
		MARGIN_W, LOWER_TOP, FX_REVERSE | FX(COL_SELECTED, 2, 0), ALPHABET_A
	);

	kanji = kanji_swap('‚`');
	for(i = 0; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(UPPER_TOP, i, fx, 1, kanji);
		kanji++;
	}

	for(i = 0; i < SYM_COUNT; i++) {
		kanji = ALPHABET_SYMS[i];
		alphabet_putca_fx(SYM_TOP, i, fx, 2, kanji);
	}

	kanji = kanji_swap('‚O');
	for(i = 0; i < NUM_COUNT; i++) {
		alphabet_putca_fx(NUM_TOP, i, fx, 3, kanji);
		kanji++;
	}
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_SPACE);	i = (KANJI_PER_ROW - 3);
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_LEFT); 	i++;
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_RIGHT);	i++;
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_ENTER);	i++;
}
