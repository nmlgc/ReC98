#pragma option -zPgroup_01

#include "libs/master.lib/master.hpp"
#include "th03/common.h"
#include "th03/formats/scoredat.hpp"

const char near* SCOREDAT_FN_PTR = SCOREDAT_FN; // ZUN bloat: Use the macro.
scoredat_section_t hi;

#include "th03/formats/score_es.cpp"
