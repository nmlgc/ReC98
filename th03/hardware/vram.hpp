#include "pc98.h"

inline unsigned char to_vram_word(pixel_t screen_v) {
	return static_cast<unsigned char>(screen_v / 16);
}

class VRAMWord {
public:
	// Code generation will require direct access to v, if performing
	// arithmetic with a local variable...
	unsigned char v;

	void operator =(pixel_t screen_v) {
		v = to_vram_word(screen_v);
	}
};
