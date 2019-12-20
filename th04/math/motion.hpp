typedef struct {
	SPPoint cur;
	SPPoint prev;
	SPPoint velocity;

	void init(float screen_x, float screen_y) {
		cur.x = screen_x;
		prev.x = screen_x;
		cur.y = screen_y;
		prev.y = screen_y;
	}
} motion_t;
