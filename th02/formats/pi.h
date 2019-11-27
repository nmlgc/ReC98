#if GAME == 5
# define PI_COUNT 8
#else
# define PI_COUNT 6
#endif

extern PiHeader pi_slot_headers[PI_COUNT];
extern void far *pi_slot_buffers[PI_COUNT];
