#define ALPHABET_Y 240
#define MARGIN_W 32
#define KANJI_PADDING_X 16
#define KANJI_PADDING_Y 8

#define KANJI_PADDED_W (GLYPH_FULL_W + KANJI_PADDING_X)
#define KANJI_PADDED_H (GLYPH_H + KANJI_PADDING_Y)

#define KANJI_PER_ROW \
	((RES_X - (MARGIN_W * 2)) / KANJI_PADDED_W)

inline int row_ceil(int count)
{
	return ((count + (KANJI_PER_ROW - 1)) / KANJI_PER_ROW);
}

inline int alphabet_x(int i)
{
	return (((i % KANJI_PER_ROW) * KANJI_PADDED_W) + MARGIN_W);
}

inline int alphabet_y(int start_row, int i)
{
	return (((i / KANJI_PER_ROW) * KANJI_PADDED_H) +
		(ALPHABET_Y + ((start_row) * KANJI_PADDED_H)));
}

#define alphabet_putca_fx(start_row, i, fx, fmt_instance, kanji) \
	graph_putkanji_fx( \
		alphabet_x(i), alphabet_y(start_row, i), fx, fmt_instance, kanji \
	);

#define alphabet_putsa_fx(start_row, i, fx, str) \
	extern const char str[]; \
	graph_printf_fx(alphabet_x(i), alphabet_y(start_row, i), fx, str);

// TODO: Should be derived via `sizeof()` once the array is declared here.
#define SYM_COUNT 18
extern const uint16_t ALPHABET_SYMS[];

inline uint16_t kanji_swap(uint16_t kanji)
{
	return (kanji << 8) | (kanji >> 8);
}

void alphabet_put_initial()
{
	#define A_TO_Z_COUNT 26
	#define NUM_COUNT 10

	#define CAPITAL_ROW (row_ceil(A_TO_Z_COUNT))
	#define SYM_ROW (CAPITAL_ROW + row_ceil(A_TO_Z_COUNT))
	#define NUM_ROW (SYM_ROW + row_ceil(SYM_COUNT))

	int fx = FX(7, 2, 0);
	uint16_t kanji;
	int i;
#if (BINARY == 'M')
	char kanji_str[3];
#endif

	kanji = kanji_swap('‚‚');
	for(i = 1; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(0, i, fx, 0, kanji);
		kanji++;
	}
	extern const char ALPHABET_A[];
	graph_putsa_fx(MARGIN_W, ALPHABET_Y, FX_REVERSE | FX(3, 2, 0), ALPHABET_A);

	kanji = kanji_swap('‚`');
	for(i = 0; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(CAPITAL_ROW, i, fx, 1, kanji);
		kanji++;
	}

	for(i = 0; i < SYM_COUNT; i++) {
		kanji = ALPHABET_SYMS[i];
		alphabet_putca_fx(SYM_ROW, i, fx, 2, kanji);
	}

	kanji = kanji_swap('‚O');
	for(i = 0; i < NUM_COUNT; i++) {
		alphabet_putca_fx(NUM_ROW, i, fx, 3, kanji);
		kanji++;
	}
	alphabet_putsa_fx(NUM_ROW, i, fx, ALPHABET_SPACE);	i = (KANJI_PER_ROW - 3);
	alphabet_putsa_fx(NUM_ROW, i, fx, ALPHABET_LEFT); 	i++;
	alphabet_putsa_fx(NUM_ROW, i, fx, ALPHABET_RIGHT);	i++;
	alphabet_putsa_fx(NUM_ROW, i, fx, ALPHABET_ENTER);	i++;
}
