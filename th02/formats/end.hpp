// Just like its in-game dialogs and Music Room comments, TH02 also stores its
// ending and verdict text in a simple plaintext file. This is the most loosely
// defined out of the three formats:
//
// • The line count of each particular file and sequence are hardcoded into the
//   ending script, just as for in-game dialogs.
// • While the line length and padded line size are consistent across the three
//   files, the implementation still treats them as variable. Still defining it
//   here for consistency with other file formats.

#include "shiftjis.hpp"

static const shiftjis_ank_amount_t END_LINE_LENGTH = 44;
static const shiftjis_ank_amount_t END_LINE_SIZE = (END_LINE_LENGTH + 2);
