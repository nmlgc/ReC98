/* ReC98
 * -----
 * Code segment #4 of TH01's FUUIN.EXE
 */

#include "platform.h"
#include "th01/hardware/vsync.hpp"

// Special FUUIN.EXE version of frame_delay() that resets [z_vsync_Count1]
// first.
void frame_delay(unsigned int frames)
{
	z_vsync_Count1 = 0;
	while(z_vsync_Count1 < frames) {
	}
}
