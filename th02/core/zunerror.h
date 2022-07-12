// Debugging
// ---------
// Calls ZUN's interrupt vector set up in ZUNINIT.COM to display an error
// message.
typedef enum {
	ERROR_FILE_NOT_FOUND = 2,
	ERROR_OUT_OF_MEMORY = 3,
	ERROR_MISSING_DRIVER = 4,
	ERROR_SCOREDAT_CORRUPT = 5,

	_zun_error_t_FORCE_UINT16 = 0xFFFF
} zun_error_t;

void pascal zun_error(zun_error_t err);
// ---------
