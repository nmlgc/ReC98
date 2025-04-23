// Macros for constructing fixed-length gaiji strings out of adjacent slots.
#define g_str_1(first) (first + 0)
#define g_str_2(first) g_str_1(first), (first + 1)
#define g_str_3(first) g_str_2(first), (first + 2)
#define g_str_4(first) g_str_3(first), (first + 3)
#define g_str_5(first) g_str_4(first), (first + 4)
#define g_str_6(first) g_str_5(first), (first + 5)
#define g_str_7(first) g_str_6(first), (first + 6)
