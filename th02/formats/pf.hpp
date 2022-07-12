// TH02 packfile declarations.
static inline void game_pfopen(void) {
	extern const char pf_fn[];
	pfkey = 0x12;
	pfstart(pf_fn);
}
