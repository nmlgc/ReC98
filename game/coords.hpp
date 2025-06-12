#include "th01/math/subpixel.hpp"

// Coordinates that change from subpixel space to pixel space within the same
// variable...
// ZUN bloat: Just use separate variables.
union space_changing_pixel_t {
	Subpixel sp;
	pixel_t pixel;
};

// Points that change from subpixel screen space to pixel screen space within
// the same variable...
// ZUN bloat: Just use separate variables.
union space_changing_point_t {
	SPPoint sp;
	screen_point_t pixel;
};

template <class Coord> struct LTWH {
	Coord left;
	Coord top;
	Coord w;
	Coord h;
};

template <class TX, class TY> struct LRTB {
	TX left, right;
	TY top, bottom;
};

template <class TX, class TY> struct LTRB {
	TX left, top;
	TY right, bottom;
};
