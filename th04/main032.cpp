/* ReC98
 * -----
 * 2nd part of code segment #3 of TH04's MAIN.EXE
 */

#pragma option -zCmain_032_TEXT -zPmain_03

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/overlap.hpp"
#include "th04/math/motion.hpp"
#include "th04/math/randring.h"
#include "th04/math/vector.hpp"
#include "th04/sprites/main_pat.h"
#include "th04/main/frames.h"
#include "th04/main/playfld.hpp"
#include "th04/main/playperf.hpp"
#include "th04/main/player/player.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th04/main/hud/hud.h"
#include "th04/main/hud/popup.hpp"
#include "th04/main/pointnum/pointnum.hpp"
#include "th04/main/rank.hpp"
#include "th04/main/spark.hpp"
#include "th04/main/score.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/slowdown.hpp"
#include "th04/main/gather.hpp"

#pragma option -a2
#include "th04/main/bullet/add.cpp"
}
