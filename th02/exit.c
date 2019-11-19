void game_exit(void)
{
	pfend();
	graph_clear_both();

#if GAME >= 4
	mem_unassign();
	vsync_end();
#else
	vsync_end();
	mem_unassign();
#endif

	text_clear();

#if GAME >= 3
	js_end();
#endif

	egc_start();

#if GAME >= 4
	bgm_finish();
#endif
}
