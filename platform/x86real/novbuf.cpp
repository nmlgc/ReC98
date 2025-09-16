// Disabling buffering of redirected stdin and stdout on Borland compilers
// -----------------------------------------------------------------------
// Section 7.21.3/7 of the C standard mandates that stdin and stdout must be
// initially buffered if they refer to non-TTY devices. Both the check and the
// subsequent activation of buffering are fairly code-intensive operations that
// cause the following functions to be pulled into the binary:
// • isatty()
// • lseek()
// • fflush()
// • flushall()
// • fseek()
// • setvbuf()
// • write()
// • xfflush()
// • setupio()
// The only PC-98 Touhou game that uses the C I/O streams for stdin and stdout
// is TH01, and the scanf() calls in debug mode rely on stdin being buffered.
// In all other games, we can remove this setup to save 1,722 bytes of binary
// size.

#pragma option -zC_TEXT

#if defined(__TURBOC__) && defined(__MSDOS__)

extern "C" void __cdecl near _setupio(void)
{
}

#endif
