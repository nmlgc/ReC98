/// Fire waves
/// ----------
#define FIREWAVE_COUNT 2

struct near firewave_t {
	bool alive;
	bool is_right;
	vram_y_t bottom;
	pixel_t amp;
};

extern firewave_t firewaves[FIREWAVE_COUNT];
/// ----------
