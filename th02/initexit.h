#if GAME >= 3
int game_init_op(const unsigned char *pf_fn);
int pascal game_init_main(const unsigned char *pf_fn);
#else
int game_init_op(void);
int pascal game_init_main(void);
#endif

void game_exit(void);
void game_exit_to_dos(void);
