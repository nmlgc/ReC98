// TH02 packfile declarations.

// "東方封魔.録" in Shift-JIS
#define PF_FN "\x93\x8C\x95\xFB\x95\x95\x96\x82\x2E\x98\x5E"

static inline void game_pfopen(void) {
	extern const char pf_fn[];
	pfkey = 0x12;
	pfstart(pf_fn);
}
