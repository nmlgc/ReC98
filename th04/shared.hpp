/* ReC98
 * -----
 * Types shared between TH04 and TH05
 */

/// Math
/// ----
class Subpixel {
private:
	int v;

public:
	Subpixel() {}
	Subpixel(float screen_v) { *this = screen_v; }

	Subpixel& operator =(float screen_v) {
		v = static_cast<int>(screen_v * 16.0f);
		return *this;
	}
};

struct SPPoint {
	Subpixel x, y;

	void set(float screen_x, float screen_y) {
		x = screen_x;
		y = screen_y;
	}
};

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
/// ----

/// Score
/// -----
extern unsigned long score_delta;

void pascal near score_update_and_render(void);

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void);
/// -----
