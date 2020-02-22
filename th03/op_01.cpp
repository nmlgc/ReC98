/* ReC98
 * -----
 * Code segment #1 of TH03's OP.EXE
 */

extern bool snd_sel_disabled; // Yes, it's just (!snd_fm_possible).

extern const playchar_paletted_t demo_chars[DEMO_COUNT][PLAYER_COUNT];
extern const int32_t demo_rand[DEMO_COUNT];

void pascal near start_demo();
