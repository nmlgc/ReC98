// ZUN bloat: At 257 bytes of static data, [_ctype] might be a rather heavy
// dependency for three digit checks. It's also *technically* wrong, as the
// <ctype.h> functions are affected by the current locale (see section 7.4.2
// of the C standard), whereas the subsequent conversion is hardcoded as a
// single subtraction from an ASCII '0'.
#include <ctype.h>

// Code generation… PORTERS: Remove.
#if defined(__TURBOC__) && defined(__MSDOS__)
	#undef _IS_DIG
	static const unsigned char _IS_DIG = 2;
#endif

// Reads up to 3 number digits from [p] and writes the resulting 3-digit number
// to [ret]. If [p] does not point to any digit, [default_value] is written to
// [ret] instead.
template <class T> inline void str_consume_up_to_3_digits(
	int*& ret, T& p, const int& default_value
) {
	unsigned char c0 = *(p++);
	unsigned char c1 = *(p++);
	unsigned char c2 = *(p++);
	if(!isdigit(c0)) {
		*ret = default_value;
		p -= 3;
	} else if(!isdigit(c1)) {
		*ret = (c0 - '0');
		p -= 2;
	} else if(!isdigit(c2)) {
		*ret = (((c0 - '0') * 10) + c1 - '0');
		p -= 1;
	} else {
		*ret = (((c0 - '0') * 100) + ((c1 - '0') * 10) + (c2 - '0'));
	}
}
