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
#include "th04/math/motion.hpp"
#include "th04/math/randring.h"
#include "th04/math/vector.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/playperf.hpp"
#include "th04/main/player/player.hpp"
#include "th04/main/bullet/bullet.hpp"

#pragma option -a2
#include "th04/main/bullet/add.cpp"
}
