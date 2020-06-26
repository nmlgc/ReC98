#if GAME == 3
// (different calling convention than the TH04/TH05 one)
int __cdecl vector1_at(int origin, int length, int angle);
#endif

int pascal vector2(int &ret_x, int &ret_y, unsigned char angle, int length);

int pascal vector2_between_plus(
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned char plus_angle,
	int &ret_x,
	int &ret_y,
	int length
);
