// Types [len] half- (ank) or full-width (kanji) characters of [str] onto the
// given position in VRAM, with a frame delay between each character.
void pascal graph_type_ank(int left, int top, int len, const char *str);
void pascal graph_type_kanji(int left, int top, int len, const char *str);
