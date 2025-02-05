#include "platform.h"

// Prevents stage enemies from being spawned if `true`.
extern bool midboss_active;

#if (GAME == 2)
	// Returns the new value of [midboss_active].
	extern bool (*midboss_invalidate)(void);

	extern void (*midboss_update_and_render);
#endif
