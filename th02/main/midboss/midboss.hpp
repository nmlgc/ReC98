#include "platform.h"

// Prevents stage enemies from being spawned if `true`.
extern bool midboss_active;

#if (GAME == 2)
// Returns the new value of [midboss_active].
extern bool (*midboss_invalidate)(void);

extern void (*midboss_update_and_render);

#define MIDBOSS_DEC(stage) \
	bool midboss##stage##_invalidate(void); \
	void midboss##stage##_update_and_render(void);

// "midbosses" unfortunately has 9 characters and therefore won't work as a 8.3
// filename. However, since these have no names anyway, we can just declare all
// of them here.
MIDBOSS_DEC(1);
MIDBOSS_DEC(2);
MIDBOSS_DEC(3);
MIDBOSS_DEC(4);
MIDBOSS_DEC(x);
#endif
