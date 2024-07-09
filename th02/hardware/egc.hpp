#include "th01/hardware/egc.h"

// Starts the EGC, and initializes it for a copy.
#if (GAME >= 4)
	void near egc_start_copy_noframe(void);
#else
	void egc_start_copy_noframe(void);
#endif
