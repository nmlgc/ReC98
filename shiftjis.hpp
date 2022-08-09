// 2-byte JIS X 0208 codepoint.
typedef uint16_t jis_t;

// Multibyte Shift-JIS string. Use as replacement for `unsigned char` in
// situations where the contents are assumed to be Shift-JIS.
typedef uint8_t shiftjis_t;
typedef int8_t sshiftjis_t; // MODDERS: Delete

// 2-byte/fullwidth Shift-JIS codepoint.
typedef uint16_t shiftjis_kanji_t;
typedef int8_t sshiftjis_kanji_t; // MODDERS: Delete

// ZUN bloat: Byte-swapped 2-byte/fullwidth Shift-JIS codepoint for bytewise
// access.
typedef uint16_t shiftjis_kanji_swapped_t;
typedef int16_t sshiftjis_kanji_swapped_t; // MODDERS: Delete

#define kanji_swap(kanji) static_cast<shiftjis_kanji_swapped_t>( \
	(static_cast<shiftjis_kanji_t>(kanji) << 8) | \
	(static_cast<shiftjis_kanji_t>(kanji) >> 8) \
)

#ifdef DECOMP_HPP
	// Way too often, the games store fullwidth Shift-JIS codepoints in two
	// 8-bit variables rather than a single 16-bit one.
	typedef StupidBytewiseWrapperAround<shiftjis_kanji_t> ShiftJISKanji;
#endif

// Good luck deriving this from the StupidBytewiseWrapperAround template.
template <unsigned int Length> union ShiftJISKanjiBuffer {
	shiftjis_kanji_t t[Length];
	int8_t byte[sizeof(uint16_t) * Length];
	uint8_t ubyte[sizeof(uint16_t) * Length];
};

inline jis_t shiftjis_to_jis(shiftjis_kanji_t shiftjis) {
	return (0x1F21 +
		(((shiftjis >> 8) - (shiftjis >> 15) < 0x9E)
			? ((((shiftjis >> 8) - (shiftjis >> 15) - 0x40) & 0x1FF))
			: ((shiftjis >> 8) - (shiftjis >> 15) + 0x62)
		) + ((shiftjis & 0x3F) << 9)
	);
}
