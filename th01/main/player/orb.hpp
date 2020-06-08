static const int ORB_W = 32;
static const int ORB_H = 32;

static const int ORB_LEFT_MIN = (PLAYFIELD_LEFT);
static const int ORB_LEFT_MAX = (PLAYFIELD_RIGHT - ORB_W);
static const int ORB_TOP_MIN = (PLAYFIELD_TOP);
static const int ORB_TOP_MAX = (PLAYFIELD_BOTTOM - ORB_H);

static const int ORB_LEFT_START = (ORB_LEFT_MAX -  8);
static const int  ORB_TOP_START = ( ORB_TOP_MAX - 88);

extern int  orb_cur_left,  orb_cur_top;
extern int orb_prev_left, orb_prev_top;
