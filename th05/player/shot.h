// We *really* want to fit those on a line...
#define OPT_L shot->from_option_l()
#define OPT_R shot->from_option_r()

#define VELOCITY_X(screen_x) shot->pos.velocity.x = screen_x;
#define VELOCITY_Y(screen_y) shot->pos.velocity.y = screen_y;

#define VELOCITY_XY(screen_x, screen_y) \
	VELOCITY_X(screen_x); \
	VELOCITY_Y(screen_y);

#define VELOCITY_YX(screen_y, screen_x) \
	VELOCITY_Y(screen_y); \
	VELOCITY_X(screen_x);
