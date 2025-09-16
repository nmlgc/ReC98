// All the redundant ways of identifying the currently updated player character

#include "th03/common.h"

extern pid_t pid_current;
extern pid_t pid_other;

// ZUN bloat: Doubly redundant: The player ID is already covered by
// [pid_current], while [so_attack] can be easily calculated from that ID.
extern union {
	unsigned char current;
	unsigned char so_attack; // sprite16_offset_t
} pid;
