// Note the slight semantic differences to the item_splash_t structure.
struct circle_t {
	char flag;
	unsigned char age;
	point_t center;
	pixel_t radius_cur;
	pixel_t radius_delta;
};

#if (GAME == 5)
	static const int CIRCLE_COUNT = 8;
#else
	static const int CIRCLE_COUNT = 16;
#endif
extern circle_t circles[CIRCLE_COUNT];
