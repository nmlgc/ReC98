// Disabling buffering of stdin and stdout on Borland compilers
// ------------------------------------------------------------
// To ensure the proper functionality of C's standard I/O functions, Borland's
// libc must properly configure `stdin` and `stdout` at startup depending on
// whether they refer to a TTY or were redirected to a file:
//
// |      |     stdin     |    stdout    |
// | ---: | :-----------: | :----------: |
// |  TTY | line-buffered | no buffering |
// | File |        fully buffered        |
//
// The redirected case is mandated by Section 7.21.3/7 of the C standard, while
// the TTY case is implementation-defined. However, both the check and the
// subsequent activation of buffering are fairly code-intensive operations that
// cause the following functions to be pulled into the binary:
//
// • isatty()
// • lseek()
// • fflush()
// • flushall()
// • fseek()
// • setvbuf()
// • write()
// • xfflush()
// • setupio()
//
// The only PC-98 Touhou game that uses C's `stdin` and `stdout` is TH01, and
// the scanf() calls in Debug mode indeed rely on `stdin` being buffered. In
// all other games though, we can remove this setup to save 1,722 bytes of
// binary size.

#pragma option -zC_TEXT

#if defined(__TURBOC__) && defined(__MSDOS__)

extern "C" void __cdecl near _setupio(void)
{
}

#endif
