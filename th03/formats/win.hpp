// TH03's win screen lines are stored in another simple plaintext file that
// contains one 3×60-byte block of lines per playchar, followed by two more
// fixed blocks shown at the end of stages 6 and 7. In contrast to TH02's
// dialog text files, these don't use any padding bytes.

static const int WIN_LINES = 3;
static const int WIN_LINE_SIZE = 60;
