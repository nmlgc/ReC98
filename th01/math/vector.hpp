#if (GAME == 1)
	// Slightly different parameter lists compared to later games!
	void vector2(int &ret_x, int &ret_y, int length, unsigned char angle);

	void vector2_between(
		int x1, int y1, int x2, int y2, int& ret_x, int &ret_y, int length
	);
#endif
