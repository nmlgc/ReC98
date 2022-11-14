// ZUN bloat: At 257 bytes of static data, [_ctype] might be a rather heavy
// dependency for three digit and control character checks. For digits, it's
// also *technically* wrong, as the <ctype.h> functions are affected by the
// current locale (see section 7.4.2 of the C standard), whereas the subsequent
// conversion is hardcoded as a single subtraction from an ASCII '0'.
//
// In the original binary, "control character" refers to every ASCII codepoint
// < 0x20.
#include <ctype.h>

// Code generation… PORTERS: Remove.
#if defined(__TURBOC__) && defined(__MSDOS__)
	#undef _IS_DIG
	#undef _IS_CTL
	static const unsigned char _IS_DIG = 2;
	static const unsigned char _IS_CTL = 32;
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

#define str_sep_control_or_space(temp_c) \
	(iscntrl(temp_c) || (temp_c == ' '))

// Reads characters from [p] to [ret] until either
// • encountering a control or ' ' character (with [p] the pointing to the
//   character after this sentinel one),
// • or until up to a maximum of ([len_max] - 1) characters have been
//   read (with [p] then pointing to the character after the last one read).
// The resulting string is \0-terminated, and [len] receives the amount of
// characters before the \0 terminator.
#define str_consume_control_or_space_separated_string( \
	ret, len, p, len_max, temp_c \
) { \
	for(len = 0; len < (len_max - 1); len++) { \
		temp_c = *p; \
		p++; \
		if(str_sep_control_or_space(temp_c)) { \
			break; \
		} \
		ret[len] = temp_c; \
	} \
	ret[len] = '\0'; \
}
