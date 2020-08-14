#include "th04/main/playperf.hpp"
#include "th04/main/bullet/bullet.hpp"

#define tmpl bullet_template

void near tune_for_easy(void)
{
	switch(tmpl.pattern) {
	case BP_STACK:
	case BP_STACK_AIMED:
		tmpl.delta.stack_speed -= (tmpl.delta.stack_speed / 4);
		if(tmpl.count >= 2) {
			tmpl.count--;
		}
		break;

	case BP_SPREAD:
	case BP_SPREAD_AIMED:
		if(tmpl.count >= 3) {
			tmpl.count -= 2;
		}
		break;

	case BP_RANDOM_ANGLE:
	case BP_RING:
	case BP_RING_AIMED:
		tmpl.count /= 2;
		break;
	}
}

void near tune_for_hard(void)
{
	switch(tmpl.pattern) {
	case BP_SINGLE_AIMED:
		tmpl.pattern = BP_STACK_AIMED;
		tmpl.count = 2;
		tmpl.delta.stack_speed = to_sp(0.375f);
		break;
	case BP_SINGLE:
		tmpl.pattern = BP_STACK;
		tmpl.count = 2;
		tmpl.delta.stack_speed = to_sp(0.375f);
		break;

	case BP_STACK:
	case BP_STACK_AIMED:
		tmpl.delta.stack_speed += (tmpl.delta.stack_speed / 2);
		break;

	case BP_SPREAD:
	case BP_SPREAD_AIMED:
		tmpl.count += 2;
		break;

	case BP_RING:
	case BP_RING_AIMED:
		tmpl.count *= 3;
		tmpl.count /= 2;
		if(tmpl.count > 48) {
			tmpl.count = 48;
		}
		break;

	case BP_RANDOM_ANGLE:
	case BP_RANDOM_ANGLE_AND_SPEED:
		tmpl.count += (tmpl.count / 2);
		break;
	}
}

void near tune_for_lunatic(void)
{
	switch(tmpl.pattern) {
	case BP_SINGLE_AIMED:
		tmpl.pattern = BP_SPREAD_AIMED;
		tmpl.count = 3;
		tmpl.delta.spread_angle = to_sp(0.375f);
		break;
	case BP_SINGLE:
		tmpl.pattern = BP_SPREAD;
		tmpl.count = 3;
		tmpl.delta.spread_angle = to_sp(0.375f);
		break;

	case BP_STACK:
	case BP_STACK_AIMED:
		tmpl.delta.stack_speed += (tmpl.delta.stack_speed / 2);
		tmpl.count++;
		break;

	case BP_SPREAD:
	case BP_SPREAD_AIMED:
		tmpl.count += 4;
		break;

	case BP_RING:
	case BP_RING_AIMED:
		tmpl.count *= 2;
		if(tmpl.count > 48) {
			tmpl.count = 48;
		}
		break;

	case BP_RANDOM_ANGLE:
	case BP_RANDOM_ANGLE_AND_SPEED:
		tmpl.count *= 2;
		break;
	}
}

void near tune_for_playperf(void)
{
	switch(tmpl.pattern) {
	case BP_STACK:
	case BP_STACK_AIMED:
		if(playperf >= 24) {
			tmpl.count++;
		} else if((playperf <= 6) && (tmpl.count >= 2)) {
			tmpl.count--;
		}
		break;

	case BP_SPREAD:
	case BP_SPREAD_AIMED:
		if(playperf >= 24) {
			tmpl.count += 2;
		} else if((playperf <= 6) && (tmpl.count >= 3)) {
			tmpl.count -= 2;
		}
		break;

	case BP_RING:
	case BP_RING_AIMED:
		if(playperf >= 24) {
			tmpl.count += 4;
		} else if(playperf >= 20) {
			tmpl.count += 2;
		} else if(tmpl.count >= 5) {
			if(playperf <= 10) {
				tmpl.count -= 2;
			}
			if(playperf <= 4) {
				tmpl.count -= 4;
			}
		}
		break;
	}
}

#undef tmpl

void pascal near bullet_template_tune_easy(void)
{
	tune_for_playperf();
	tune_for_easy();
}

void pascal near bullet_template_tune_normal(void)
{
	tune_for_playperf();
}

void pascal near bullet_template_tune_hard(void)
{
	tune_for_playperf();
	tune_for_hard();
}

void pascal near bullet_template_tune_lunatic(void)
{
	tune_for_playperf();
	tune_for_lunatic();
}
