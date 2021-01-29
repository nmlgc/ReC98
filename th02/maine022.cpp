/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's MAINE.EXE
 */

#pragma codeseg SHARED

extern "C" {
#include "platform.h"
#include "master.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/formats/pf.hpp"

#include "th02/snd/data.c"
extern const char pf_fn[] = PF_FN;

#include "th02/hardware/input.c"
}
