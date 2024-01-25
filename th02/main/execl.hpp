// Performs the following cleanup functions:
//
// • Shuting down all subsystems with heap-allocated data
// • Clearing text RAM and hiding VRAM
// • (TH04/TH05) Saving all gameplay metrics that are used in MAINE.EXE to the
//   resident structure
//
// Then launches into [binary_fn], replacing the current process. Does not
// return if [binary_fn] was launched successfully, and otherwise returns
// execl()'s return value.
int pascal GameExecl(const char *binary_fn); /* ZUN symbol [MAGNet2010] */
