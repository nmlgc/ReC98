void game_exit(void)
{
	pfend();
	graph_clear_both();
	vsync_end();
	mem_unassign();
	text_clear();
	egc_start();
}
