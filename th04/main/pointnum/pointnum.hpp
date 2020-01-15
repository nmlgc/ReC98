#define POINTNUM_POPUP_DISTANCE (12.0f)
#define POINTNUM_POPUP_FRAMES 24
#define POINTNUM_FRAMES 36

/// Structure
/// ---------
#if GAME == 5
# define POINTNUM_DIGITS 5
# define POINTNUM_YELLOW_COUNT 80
#else
# define POINTNUM_DIGITS 4
# define POINTNUM_YELLOW_COUNT 200
# define POINTNUM_TIMES_2_W (POINTNUM_W * 2)
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

void pascal near pointnums_invalidate(void);
void pascal near pointnums_update(void);
/// ---------

/// Rendering
/// ---------
// Stores pointers to all point numbers that should be rendered in the current
// frame. Starts with the white ones, and [pointnum_first_yellow_alive]
// indicates the first yellow one.
extern pointnum_t near *pointnums_alive[POINTNUM_COUNT + 1];
extern pointnum_t near *pointnum_first_yellow_alive;

// Blits the given point[num] sprite to the given position. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// Returns _DX (= left) advanced by the width of the numeral.
#define pointnum_put(left, top, numeral) \
	_CX = numeral; \
	pointnum_put_raw(patnum);
void __fastcall near pointnum_put_raw(int top, int left);

void pascal near pointnums_render(void);
/// ---------
