#include <dos.h>
#include <errno.h>
#include <string.h>
#include "platform/x86real/spawnenv.hpp"
#include "platform/x86real/dos.hpp"

SpawnEnv::SpawnEnv(void) :
	buf(nullptr), buf_aligned(nullptr)
{
	char __seg* env_seg = reinterpret_cast<dos_psp_t __seg *>(_psp)->environ;
	char* far* src_p;

	uint16_t orig_bytes = 1;	// original, including the list terminator
	this->added_bytes = 0;  	// added since startup
	for(src_p = environ; *src_p != nullptr; src_p++) {
		char far* p = *src_p;
		uint16_t p_len = (strlen(p) + 1);
		if(static_cast<char __seg *>(p) != env_seg) {
			this->added_bytes += p_len;
		} else {
			orig_bytes += p_len;
		}
	}

	// The EXEC block only stores a segment-only pointer, so we need to
	// paragraph-align it.
	this->buf = reinterpret_cast<char far *>(malloc(
		orig_bytes + added_bytes + 15
	));
	if(!this->buf) {
		errno = ENOMEM;
		return;
	}
	this->buf_aligned = reinterpret_cast<char __seg *>(
		FP_SEG(this->buf) + (FP_OFF(this->buf + 15) >> 4)
	);

	char far* dst_p = this->buf_aligned;
	for(src_p = environ; *src_p != nullptr; src_p++) {
		dst_p = stpcpy(dst_p, *src_p);
		*(dst_p++) = '\0';
	}
	*(dst_p++) = '\0';
	// -----------------
}
