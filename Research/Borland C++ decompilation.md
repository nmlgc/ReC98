## Signedness

| | |
|-|-|
| `MOV al, var`<br />`MOV ah, 0`| `var` is *unsigned char* |

## Arithmetic

| | |
|-|-|
| `ADD [m8], imm8` | Only achievable through a C++ method operating on a  member? |
| `MOV AL, [m8]`<br />`ADD AL, imm8`<br />`MOV [m8], AL` | Opposite; *not* an inlined function |

### Arithmetic on a register *after* assigning it to a variable?

Assigment is part of the C expression. If it's a comparison, that comparison
must be spelled out to silence the `Possibly incorrect assignment` warning.

| | |
|-|-|
| `CALL somefunc`<br />`MOV ??, AX`<br />`OR AX, AX`<br />`JNZ ↑` | `while(( ?? = somefunc() ) != NULL)` |

### `SUB ??, imm` vs. `ADD ??, -imm`

`SUB` means that `??` is unsigned. Might require suffixing `imm` with `u` in
case it's part of an arithmetic expression that was promoted to `int`.

## `switch` statements

* Sequence of the individual cases is identical in both C and ASM
* Multiple cases with the same offset in the table, to code that doesn't
  return? Code was compiled with `-O`

## Inlining

Always worth a try to get rid of a potential macro. Some edge cases don't
inline optimally though:

* Assignments to a pointer in `SI` – that pointer is moved to `DI`,
  [clobbering that register](#clobbering-di). Try a [class method](#C++)
  instead.

## C++

* Every class method that returns `void` inlines to the ideal representation.
* Every class method that returns `*this` inlines to the ideal representation
  *only at the first nesting level*. Example: A class method calling an
  overloaded operator returning `*this` will generate (needless) instructions
  equivalent to `MOV AX, *this`. Thus, any overloaded `=`, `+=`, `-=`, etc.
  operator should always return `void`.

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
