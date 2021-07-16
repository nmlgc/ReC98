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

// Moves the given [motion] instance by one step, and returns its new position.
// The _seg1() and _seg3() variants are provided for near calls within code
// segment #1 (rendering) and code segment #3 (update), respectively.
// Note that some calls to these functions directly access the returned value
// through the AX (X) and DX (Y) registers.
SPPoint pascal near motion_update_seg1(motion_t near &motion);
SPPoint pascal near motion_update_seg3(motion_t near &motion);
