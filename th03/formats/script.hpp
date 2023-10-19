/// Common code for plaintext script formats
/// ----------------------------------------

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

enum script_ret_t {
	CONTINUE = 0,
	STOP = -1,
};

extern int script_param_number_default;

#define str_sep_control_or_space(c) \
	(iscntrl(c) || (c == ' '))

#ifdef script_p
	// Reads up to 3 ASCII number digits from [script_p] and writes the
	// resulting 3-digit number to [ret]. If [script_p] does not point to any
	// digit, [script_param_number_default] is written to [ret] instead.
	void pascal near script_param_read_number_first(int& ret)
	{
		unsigned char c0 = *script_p; script_p++;
		unsigned char c1 = *script_p; script_p++;
		unsigned char c2 = *script_p; script_p++;
		if(!isdigit(c0)) {
			ret = script_param_number_default;
			script_p -= 3;
		} else if(!isdigit(c1)) {
			ret = (c0 - '0');
			script_p -= 2;
		} else if(!isdigit(c2)) {
			ret = (((c0 - '0') * 10) + c1 - '0');
			script_p -= 1;
		} else {
			ret = (((c0 - '0') * 100) + ((c1 - '0') * 10) + (c2 - '0'));
		}
	}

	inline void script_param_read_number_first(int& ret, int default_value) {
		script_param_number_default = default_value;
		script_param_read_number_first(ret);
	}

	void pascal near script_param_read_number_second(int& ret)
	{
		if(*script_p == ',') {
			script_p++;
			script_param_read_number_first(ret);
		} else {
			ret = script_param_number_default;
		}
	}

	// Reads a filename parameter into [ret] – i.e., as many characters from
	// [script_p] until either
	// • encountering a control or ' ' character (leaving [script_p] pointing to
	//   the character after this sentinel one),
	// • or until up to a maximum of (PF_FN_LEN - 1) characters have beed read
	//   (leaving [script_p] pointing to the character after the last one read).
	// The resulting string is \0-terminated, and [temp_len] receives the
	// amount of characters before the \0 terminator.
	#define script_param_read_fn(ret, temp_len, temp_c) { \
		for(temp_len = 0; temp_len < (PF_FN_LEN - 1); temp_len++) { \
			temp_c = *script_p; \
			script_p++; \
			if(str_sep_control_or_space(temp_c)) { \
				break; \
			} \
			ret[temp_len] = temp_c; \
		} \
		ret[temp_len] = '\0'; \
	}

	// Commands shared between the cutscene and dialog systems
	// -------------------------------------------------------

	#define script_op_fade(c, func_in, func_out, temp_p1) { \
		script_p++; \
		script_param_read_number_first(temp_p1, 1); \
		if(c == 'i') { \
			func_in(p1); \
		} else { \
			func_out(p1); \
		} \
	}
	// -------------------------------------------------------
#endif
