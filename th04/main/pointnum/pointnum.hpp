/// Structure
/// ---------
#if GAME == 5
# define POINTNUM_DIGITS 5
# define POINTNUM_YELLOW_COUNT 80
#else
# define POINTNUM_DIGITS 4
# define POINTNUM_YELLOW_COUNT 200
#endif
#define POINTNUM_WHITE_COUNT 200
#define POINTNUM_COUNT (POINTNUM_WHITE_COUNT + POINTNUM_YELLOW_COUNT)

// [digits_lebcd] excludes the last 0 digit, [width] includes it. [width] also
// indicates the amount of used digits in [digits_lebcd], counted, obviously,
// from the end of the array.
struct pointnum_t {
	char flag;
	unsigned char age;
	SPPoint center_cur;
	Subpixel center_prev_y;
#if GAME == 5
	unsigned int width;
	unsigned char digits_lebcd[POINTNUM_DIGITS];
#else
	unsigned char digits_lebcd[POINTNUM_DIGITS];
	unsigned int width;
	bool times_2;
#endif
	int8_t padding;
};

extern pointnum_t pointnums[POINTNUM_COUNT];
/// ---------

// Blits the given point[num] sprite to the given position. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// Returns _DX (= left) advanced by the width of the numeral.
#define pointnum_put(left, top, numeral) \
	_CX = numeral; \
	pointnum_put_raw(patnum);
void __fastcall near pointnum_put_raw(int top, int left);
