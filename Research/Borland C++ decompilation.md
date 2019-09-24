## C++

* Every class method that returns `*this` inlines to the ideal representation.

  **Certainty**: See the examples in `9d121c7`. This is what allows us to use
  custom types with overloaded assignment operators, with the resulting code
  generation being indistinguishable from equivalent C preprocessor macros.

* Returning *anything else* will first store that result in `AX`, leading any
  branches at the call site to then refer to `AX`.

  **Certainty**: Maybe Borland (not Turbo) C++ has an optimization option
  against it?

## Limits of decompilability

### `MOV BX, SP`-style functions, or others with no standard stack frame

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
