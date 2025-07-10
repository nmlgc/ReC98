// Calculates either the X or Y coordinate of a point with the given [radius]
// away from [center]. [ratio] is either the cosine or the sine of the intended
// angle.
#if (GAME >= 4)
int pascal polar(int center, int radius, int ratio);
#else
int __cdecl polar(int center, int radius, int ratio);
#endif

#define polar_x(center, radius, angle) polar(center, radius, CosTable8[angle])
#define polar_y(center, radius, angle) polar(center, radius, SinTable8[angle])
