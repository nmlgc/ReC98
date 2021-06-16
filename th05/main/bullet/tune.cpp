// Well, at least the decompilable parts...

#pragma option -k-

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th04/main/playperf.hpp"
#include "th04/main/bullet/bullet.hpp"

void pascal near tune_for_easy(void);
void pascal near tune_for_hard(void);
void pascal near tune_for_lunatic(void);

static inline uint8_t not_aimed() {
	return ~BGC0_AIMED;
}

void pascal near tune_for_playperf(void)
{
	if((bullet_template.group & not_aimed()) != BG_STACK) {
		return;
	}
	_AL = playperf;
	if(_AL >= 38) {
		bullet_template.stack++;
	} else if(_AL <= 24 && bullet_template.stack >= 2) {
		bullet_template.stack--;
	}
}

#pragma codestring "\x90"

void pascal near bullet_template_tune_easy(void)
{
	tune_for_playperf();
	tune_for_easy();
}

#pragma codestring "\x90"

void pascal near bullet_template_tune_normal(void)
{
	tune_for_playperf();
}

void pascal near bullet_template_tune_hard(void)
{
	tune_for_playperf();
	tune_for_hard();
}

#pragma codestring "\x90"

void pascal near bullet_template_tune_lunatic(void)
{
	tune_for_playperf();
	tune_for_lunatic();
}

#pragma codestring "\x90"

#pragma option -k.
