// Header structures for multi-sprite formats. Used for .BOS and .GRC.
#pragma pack(push, 1)
struct spriteformat_header_inner_t {
	uint8_t image_count;
	int8_t unknown[7];
};

// For reference, never actually used by the game itself (unfortunately).
// [Outer] can be a grc_header_t or a bos_header_t.
template <class Outer> struct spriteformat_header_t {
	Outer outer;
	Palette4 pal;
};
#pragma pack(pop)
