/* ReC98
 * -----
 * VSync interrupt callback clear function. In REIIDEN.EXE, this function needs
 * to be put into a segment separate from vsync.c.
 */

extern int vsync_callback_is_set;

void vsync_callback_clear(void)
{
	vsync_callback_is_set = 0;
}
