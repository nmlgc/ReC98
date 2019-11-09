struct item_t {
	char flag;
	char unused;
	motion_t pos;
	unsigned char type;
	char unknown;
	int patnum;	// Assumed to be a 16×16 sprite.
	int pulled_to_player;	// Yup, a 16-bit bool.
};

#define ITEM_W 16
#define ITEM_H 16
#define ITEM_PULL_SPEED 10

#if GAME == 5
# define ITEM_COUNT 40
#else
# define ITEM_COUNT 32
#endif

extern item_t items[ITEM_COUNT];
