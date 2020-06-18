// Vectors
// -------
#if GAME == 3
// (different calling convention than the TH04/TH05 one)
int __cdecl far vector1_at(int angle, int length, int origin)
#endif

int pascal far vector2(
	int far *ret_x, int far *ret_y, unsigned char angle, int length
);

// Constructs a vector from (x1, y1) to (x2, y2), and additionally applies
// [plus_angle] to the resulting angle between the two points.
int pascal far vector2_between_plus(
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned char plus_angle,
	int *ret_x,
	int *ret_y,
	int length
);
// -------
