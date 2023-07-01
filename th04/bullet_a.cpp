#pragma option -zPmain_03

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/overlap.hpp"
#include "th04/math/motion.hpp"
#include "th04/math/randring.hpp"
#include "th04/math/vector.hpp"
#include "th04/sprites/main_pat.h"
extern "C" {
#include "th04/main/playfld.hpp"
#include "th04/main/playperf.hpp"
#include "th04/main/player/player.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th04/main/bullet/clearzap.hpp"
}
#include "th04/main/gather.hpp"

#pragma option -a2
extern "C" {
#include "th04/main/bullet/add.cpp"
}
