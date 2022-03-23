#pragma option -zCBOSS_6_TEXT

#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/vector.hpp"
#include "th04/main/playfld.hpp"
#include "th05/main/playperf.hpp"
}
#include "th05/main/custom.h"
#include "th05/main/bullet/b6ball.hpp"

void near b6balls_add(void)
{
	subpixel_t speed = playperf_speedtune(b6ball_template.speed);
	b6ball_t near *p;
	int i;
	for((p = b6balls, i = 1); i < (1 + B6BALL_COUNT); (i++, p++)) {
		if(p->flag != B6BF_FREE) {
			continue;
		}
		p->flag = B6BF_CLOUD;
		p->pos.cur = b6ball_template.pos.cur;
		vector2_near(p->pos.velocity, b6ball_template.angle, speed);
		p->patnum_tiny = b6ball_template.patnum_tiny;
		p->cloud_radius.set(48.0f);
		return;
	}
}
