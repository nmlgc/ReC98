#define CFG_LIVES_MAX 6
#define CFG_LIVES_DEFAULT 3

#if GAME == 5
# define CFG_BOMBS_MAX 3
#else
# define CFG_BOMBS_MAX 2
#endif
#define CFG_BOMBS_DEFAULT CFG_BOMBS_MAX
