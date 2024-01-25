static const vc_t COL_TYPE = 15;

// Types [len] half- (ank) or full-width (kanji) characters of [str] onto the
// given position in VRAM, with a frame delay between each character.
void pascal graph_type_ank_n(
	screen_x_t left, vram_y_t top, int len, const sshiftjis_t *str
);
void pascal graph_type_kanji_n(
	screen_x_t left, vram_y_t top, int len, const sshiftjis_kanji_t *str
);

#define graph_type_ank(left, top, str) { \
	graph_type_ank_n(left, top, (sizeof(str) - 1), str); \
}
#define graph_type_kanji(left, top, str) { \
	graph_type_kanji_n(left, top, ((sizeof(str) - 1) / 2), str); \
}
