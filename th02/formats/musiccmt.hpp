// Similar to TH02's in-game dialog system, the Music Rooms of all 4 games use
// a simple plaintext file for track comments, storing each comment in 20
// successive 40-byte lines of text, with 2 unused padding bytes per line. The
// original files use the padding bytes for a CRLF newline sequence to simplify
// editing.
// The first line contains the track title and is rendered to a different
// position than the other 19 lines.
//
// As of TH04, comment lines can start with a semicolon, which prevents them
// from being rendered. This is purely a performance hint, and is functionally
// equivalent to a line consisting of only whitespace.

static const shiftjis_ank_amount_t CMT_LINE_LENGTH = ((GAME >= 4) ? 38 : 40);
static const shiftjis_ank_amount_t CMT_LINE_SIZE = (CMT_LINE_LENGTH + 2);
static const int CMT_TITLE_LINE = 0;
static const int CMT_COMMENT_LINES = ((GAME == 5) ? 9 : 19);
static const int CMT_LINES = (1 + CMT_COMMENT_LINES);
