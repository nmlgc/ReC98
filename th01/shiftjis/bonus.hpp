#define STAGEBONUS_TITLE_PREFIX "‚r‚s‚`‚f‚d@"

// The fullwidth stage number is directly inserted into the single static copy
// of this string.
#define stagebonus_title STAGEBONUS_TITLE_PREFIX "@@@‚b‚n‚l‚o‚k‚d‚s‚d"

struct stagebonus_title_t {
	ShiftJISKanji prefix[(sizeof(STAGEBONUS_TITLE_PREFIX) - 1) / 2];
	ShiftJISKanji stage[2];
	ShiftJISKanji suffix[];
};

// ZUN bloat: Same here for all rendered fullwidth numbers. This constant seems
// to do us a favor by pre-filling the constant ones digit and the trailing
// space, but the game overwrites it anyway, making it entirely pointless.
#define stagebonus_digit_buf "@@@@‚O@"

#define STAGEBONUS_SUBTITLE     	"@@‚a‚n‚m‚t‚r"
#define STAGEBONUS_TIME         	"   @‚s‚‰‚‚…@"
#define STAGEBONUS_CARDCOMBO_MAX	"‚b‚‚Ž‚”‚‰‚Ž‚•‚‚•‚“"
#define STAGEBONUS_RESOURCES    	"‚a‚‚‚‚•‚o‚Œ‚‚™‚…‚’"
#define STAGEBONUS_STAGE_NUMBER 	"@@‚r‚s‚`‚f‚d"
#define STAGEBONUS_TOTAL        	"‚a‚n‚m‚t‚r@‚o‚‚‰‚Ž‚”"
#define STAGEBONUS_HIT_KEY      	"‚g‚‰‚”@‚y@‚j‚…‚™"

static const pixel_t STAGEBONUS_TITLE_W = shiftjis_w(stagebonus_title);

// TRANSLATORS: Replace with your longest string.
static const pixel_t STAGEBONUS_LABEL_W = shiftjis_w(STAGEBONUS_TOTAL);

static const pixel_t STAGEBONUS_METRIC_ROW_W = (
	STAGEBONUS_LABEL_W + GLYPH_FULL_W + shiftjis_w(stagebonus_digit_buf)
);

static const pixel_t STAGEBONUS_W = (
	(STAGEBONUS_TITLE_W > STAGEBONUS_METRIC_ROW_W)
		? STAGEBONUS_TITLE_W
		: STAGEBONUS_METRIC_ROW_W
);
