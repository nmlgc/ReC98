#define CURVEBULLET_W 32
#define CURVEBULLET_H 32
#define CURVEBULLET_TRAIL_NODE_COUNT 16
#define CURVEBULLET_COUNT 7

typedef struct {
	char flag;
	char col;
	SPPoint node_pos[CURVEBULLET_TRAIL_NODE_COUNT];
	unsigned char node_sprite[CURVEBULLET_TRAIL_NODE_COUNT];
} curvebullet_trail_t;

extern curvebullet_trail_t curvebullet_trails[CURVEBULLET_COUNT + 1];

void pascal near curvebullets_add();
void pascal near curvebullets_update();
void pascal near curvebullets_render();
