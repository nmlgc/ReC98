// TH02 starts with one simple plaintext file for all text of a stage that
// stores successive 36-byte lines of dialog, with 4 unused padding bytes per
// line. Everything else is hardcoded – effects shown between text boxes, the
// face for each box, and even how many boxes are part of each dialog sequence.

static const shiftjis_ank_amount_t DIALOG_LINE_LENGTH = 36;
static const shiftjis_ank_amount_t DIALOG_LINE_SIZE = (DIALOG_LINE_LENGTH + 4);
static const int DIALOG_BOX_LINES = 2;
