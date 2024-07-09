// (#included from th05/main/boss/b6.cpp, due to alignment reasons.)

#include "th01/math/overlap.hpp"
#include "th04/main/bullet/clearzap.hpp"
#include "th05/main/playperf.hpp"
#include "th04/main/custom.hpp"
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
		p->pos.cur = b6ball_template.origin;
		vector2_near(p->pos.velocity, b6ball_template.angle, speed);
		p->patnum_tiny = b6ball_template.patnum_tiny;
		p->cloud_radius.set(48.0f);
		return;
	}
}

void near b6balls_update(void)
{
	custom_assert_count(b6ball_t, B6BALL_COUNT);

	b6ball_t near *p;
	int i;
	for((p = b6balls, i = 1); i < (1 + B6BALL_COUNT); (i++, p++)) {
		if(p->flag == B6BF_FREE) {
			continue;
		}
		if(p->flag == B6BF_CLOUD) {
			p->cloud_radius -= 2.0f;
			if(p->cloud_radius.v < to_sp(B6BALL_W / 2)) {
				static_cast<unsigned char>(p->flag)++;
			} else {
				continue;
			}
		}

		if(bullet_clear_time || bullet_zap.active) {
			p->flag = B6BF_DECAY;
		}

		p->age++;
		/* DX:AX = */ p->pos.update_seg3();
		if(!playfield_encloses(_AX, _DX, B6BALL_W, B6BALL_H)) {
			optimization_barrier();
			p->flag = B6BF_FREE;
		} else if(p->flag != B6BF_DECAY) {
			_AX -= player_pos.cur.x.v;
			_DX -= player_pos.cur.y.v;
			if(overlap_wh_inplace_fast(
				_AX, _DX, to_sp(B6BALL_W / 2), to_sp(B6BALL_H / 2)
			)) {
				player_is_hit = true;
				p->flag = B6BF_DECAY;
				continue;
			}
			optimization_barrier();
		} else if(p->patnum_tiny < PAT_DECAY_B6BALL) {
			// Rather brave to assume that the regular patnums of this entity
			// can't be smaller. You know how you properly DRY decay state
			// initialization? By moving it into a function...
			p->patnum_tiny = PAT_DECAY_B6BALL;
			p->pos.velocity.x.v /= 2;
			p->pos.velocity.y.v /= 2;
			p->decay_frames = 0;
		} else /* if(p->flag == B6BF_DECAY) */ {
			p->decay_frames++;
			if((p->decay_frames % 4) == 0) {
				p->patnum_tiny++;
				if(p->patnum_tiny >= (PAT_DECAY_B6BALL_last + 1)) {
					p->flag = B6BF_FREE;
				}
			}
		}
	}
}
