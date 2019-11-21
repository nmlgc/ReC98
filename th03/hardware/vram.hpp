typedef unsigned char vram_word_t;

inline vram_word_t to_vram_word(int screen_v) {
	return static_cast<vram_word_t>(screen_v / 16);
}

class VRAMWord {
public:
	// Code generation will require direct access to v, if performing
	// arithmetic with a local variable...
	vram_word_t v;

	void operator =(int screen_v) {
		v = to_vram_word(screen_v);
	}
};
