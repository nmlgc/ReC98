#include "game/pf.h"
#include "platform.h"
#include <stddef.h>

#define SEEK_SET 0
#define SEEK_CUR 1

// Encraption key
extern uint8_t arc_key;

// Initializes the internal archive state with the data from [fn]'s header.
// [fn] is closed at the end of the function, and assumed to remain unchanged
// for all arc_file_open() calls referring to any of its files, which will
// reopen this file.
void arc_load(const char fn[PF_FN_LEN]);

// Frees all internal buffers allocated during arc_load().
void arc_free();

// Opens the archive file previously loaded with arc_load() using master.lib's
// file_ropen(), looks up a packed file with the given name, and opens it for
// decompression or decryption.
void arc_file_open(const char fn[PF_FN_LEN]);

// Reads [size] bytes from the current position within the currently loaded
// packed file into [buf]. Stops at the end of file and returns the number of
// bytes actually read.
size_t arc_file_read(uint8_t *buf, size_t size);

#define arc_file_read_near(var) \
	arc_file_read(reinterpret_cast<uint8_t near *>(&var), sizeof(var))

#define arc_file_read_far(var) \
	arc_file_read(reinterpret_cast<uint8_t far *>(&var), sizeof(var))

// Classic fseek() on the currently opened file. Returns the new position
// within the unpacked data file.
size_t arc_file_seek(int pos, int dir);

// Closes the packfile.
void arc_file_close(void);
