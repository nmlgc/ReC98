// Lightweight DOS error reporting implementation
// ----------------------------------------------

#include "platform.h"

// Returns a message string for the current [errno] and [_doserrno].
const char near* dos_strerror(void);

// Prints dos_strerror() as a nicely formatted string consisting of up to three
// components between [argv[0]] and the error.
void pascal dos_print_error(
	const char *s1, const char *s2 = nullptr, const char *s3 = nullptr
);
