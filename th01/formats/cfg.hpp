#define CFG_FN "reiiden.cfg"
#define CFG_ID "REIIDEN"

struct cfg_options_t {
	int8_t rank;
	bgm_mode_t bgm_mode;
	int8_t credit_bombs;
	int8_t credit_lives_extra;	// Add 2 for the actual number of lives
};

static const rank_t CFG_RANK_DEFAULT = RANK_NORMAL;
static const bgm_mode_t CFG_BGM_MODE_DEFAULT = BGM_MODE_MDRV2;
static const int8_t CFG_CREDIT_BOMBS_DEFAULT = 1;
static const int8_t CFG_CREDIT_LIVES_EXTRA_DEFAULT = 2;

static const int8_t CFG_CREDIT_LIVES_EXTRA_MAX = 5;

struct cfg_t {
	char id[sizeof(CFG_ID) - 1];
	cfg_options_t opts;
};
