#pragma option -WX -k-

extern "C" {
#include "platform.h"
#include "th02/snd/snd.h"
#include "th02/snd/se_impl.hpp"

void snd_se_reset(void)
{
	snd_se_frame = 0;
	snd_se_playing = SE_NONE;
}
#pragma codestring "\x90"

}
