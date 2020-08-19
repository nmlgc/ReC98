typedef struct {
	SPPoint cur;
	SPPoint prev;
	SPPoint velocity;

	void init(float screen_x, float screen_y) {
		cur.x.set(screen_x);
		prev.x.set(screen_x);
		cur.y.set(screen_y);
		prev.y.set(screen_y);
	}
} motion_t;
