#if (GAME == 2)
int game_init_op(void);
int game_init_main(void);
#endif

void game_exit(void);
void game_exit_to_dos(void);

#define graph_clear_both() \
	graph_accesspage(1);	graph_clear(); \
	graph_accesspage(0);	graph_clear(); \
	graph_accesspage(0);	graph_showpage(0);
