// Macros for constructing fixed-length gaiji strings out of adjacent slots.
#define g_str_1(first) (first + 0)
#define g_str_2(first) g_str_1(first), (first + 1)
#define g_str_3(first) g_str_2(first), (first + 2)
#define g_str_4(first) g_str_3(first), (first + 3)
#define g_str_5(first) g_str_4(first), (first + 4)
#define g_str_6(first) g_str_5(first), (first + 5)
#define g_str_7(first) g_str_6(first), (first + 6)

// Macros for constructing fixed-length gaiji strings out of per-character
// alphabets.
#define g_chr_1(prefix, c1)\
	prefix##_##c1
#define g_chr_2(prefix, c1,c2) \
	g_chr_1(prefix, c1), prefix##_##c2
#define g_chr_3(prefix, c1,c2,c3) \
	g_chr_2(prefix, c1,c2), prefix##_##c3
#define g_chr_4(prefix, c1,c2,c3,c4) \
	g_chr_3(prefix, c1,c2,c3), prefix##_##c4
#define g_chr_5(prefix, c1,c2,c3,c4,c5) \
	g_chr_4(prefix, c1,c2,c3,c4), prefix##_##c5
#define g_chr_6(prefix, c1,c2,c3,c4,c5,c6) \
	g_chr_5(prefix, c1,c2,c3,c4,c5), prefix##_##c6
#define g_chr_7(prefix, c1,c2,c3,c4,c5,c6,c7) \
	g_chr_6(prefix, c1,c2,c3,c4,c5,c6), prefix##_##c7
#define g_chr_8(prefix, c1,c2,c3,c4,c5,c6,c7,c8) \
	g_chr_7(prefix, c1,c2,c3,c4,c5,c6,c7), prefix##_##c8
#define g_chr_9(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9) \
	g_chr_8(prefix, c1,c2,c3,c4,c5,c6,c7,c8), prefix##_##c9
#define g_chr_10(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10) \
	g_chr_9(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9), prefix##_##c10
#define g_chr_11(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11) \
	g_chr_10(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10), prefix##_##c11
#define g_chr_12(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12) \
	g_chr_11(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11), prefix##_##c12
#define g_chr_13(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13) \
	g_chr_12(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12), prefix##_##c13
#define g_chr_14(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14) \
	g_chr_13(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13), prefix##_##c14
#define g_chr_15(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15) \
	g_chr_14(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14), prefix##_##c15
#define g_chr_16(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16) \
	g_chr_15(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15), prefix##_##c16
#define g_chr_17(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17) \
	g_chr_16(prefix, c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16), prefix##_##c17
