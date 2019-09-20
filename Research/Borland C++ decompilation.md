## Limits of decompilability

### `MOV BX, SP`-style functions, no stack frame

These almost certainly weren't compiled from C. By disabling stack frames
using `#pragma option -k-`, it *might* be possible to still get the exact same
code out of Turbo C++ – even though it will most certainly look horrible, and
barely more readable than assembly (or even less so), with tons of inline ASM
and register pseudovariables. However, it's futile to even try if the function
contains one of the following:

* A reference to the `DI` register. In that case, Turbo C++ always inserts a
  `PUSH DI` at the beginning (before the `MOV BX, SP`), and a `POP DI` before
  returning.

  **Certainty:** Confirmed through reverse-engineering `TCC.EXE`, no way
  around it.
