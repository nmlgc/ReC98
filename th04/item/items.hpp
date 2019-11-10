enum item_type_t {
	IT_POWER = 0,
	IT_POINT = 1,
	IT_DREAM = 2,
	IT_BIGPOWER = 3,
	IT_BOMB = 4,
	IT_1UP = 5,
	IT_FULLPOWER = 6,
	IT_COUNT,
};

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

extern const int ITEM_TYPE_PATNUM[IT_COUNT];

void pascal near items_add(Subpixel x, Subpixel y, item_type_t type);
