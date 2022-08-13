// Option and error constants, according to PILOADC.DOC.

#define PILOAD_OPT_COLORKEY(col) ((col << 8) | 0x40)

// PiLoad also returns values >0 to indicate DOS file I/O errors.
#define PILOAD_ERR_OK 0
#define PILOAD_ERR_BUFFER_TOO_SMALL -8
#define PILOAD_ERR_NO_PI -31
#define PILOAD_ERR_NOT_SUPPORTED -32

#if defined(__LARGE__) || defined(__HUGE__)
	#define PiLoad PiLoadL
#elif defined(__COMPACT__)
	#define PiLoad PiLoadC
#endif

extern "C" int PiLoad(
	const char *name, char *buff, int Size, int X, int Y, int tone, int option
);
