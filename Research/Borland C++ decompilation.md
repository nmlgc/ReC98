## Local variables

| | |
|-|-|
| `DX` | First 8-bit variable declared *if no other function is called*<br />Second 16-bit variable declared *if no other function is called* |
| `[bp-1]` | First 8-bit variable declared *otherwise* |
| `SI` | First 16-bit variable declared |
| `DI` | Second 16-bit variable declared *if other functions are called* |

Example:

|      ASM | Declaration sequence in C |
|----------|---------------------------|
|     `SI` | `int near *var_1;`        |
| `[bp-1]` | `char var_2;`             |
| `[bp-2]` | `char var_3;`             |

### Grouping

Any structures or classes that contain more than a single scalar-type member
are grouped according to their declaration order, and placed *after* (that is,
further away from BP) than all scalar-type variables. This means that it's not
possible to bundle a set of variables with the same meaning into a structure
(e.g. pointers to all 4 VRAM planes) if a scalar-type variable is placed
inbetween two of these structure instances on the stack: Those structure
instances would be grouped and always placed next to each other, no matter
where the scalar-type variable is declared in relation to them.

## Signedness

| | |
|-|-|
| `MOV al, var`<br />`MOV ah, 0`| `var` is *unsigned char* |
| `MOV al, var`<br />`CBW` | `var` is *char*, `AX` is *int* |

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

## Function calls

### `NOP` insertion

Happens for every `far` call to outside of the current translation unit, even
if both the caller and callee end up being linked into the same code segment.

**Certainty:** Seems like there *might* be a way around that, apart from
temporarily spelling out these calls in ASM until both functions are compiled
as part of the same translation unit. Found nothing so far, though.

### Pushing byte arguments to functions

Borland C++ just pushes the entire word. Will cause IDA to mis-identify
certain local variables as `word`s when they aren't.

## Flags

### `-O` (Optimize jumps)

Inhibited by identical variable declarations within more than one scope – the
optimizer will only merge the code *after* the last ASM reference to that
declared variable. Yes, even though the emitted ASM would be identical:
```c
if(a) {
    int v = set_v();
    do_something_else();
    use(v);
} else if(underline) {
    // Second declaration of [v]. Even though it's assigned to the same stack
    // offset, the second `PUSH w` call will still be emitted separately.
    // Thus, jump optimization only reuses the `CALL use` instruction.
    // Move the `int v;` declaraion to the beginning of the function to avoid
    // this.
    int v = set_v();
    use(v);
}
```

## Inlining

Always worth a try to get rid of a potential macro. Some edge cases don't
inline optimally though:

* Assignments to a pointer in `SI` – that pointer is moved to `DI`,
  [clobbering that register](#clobbering-di). Try a [class method](#C++)
  instead.

## C++

Class methods inline to their ideal representation if all of these are true:

* returns `void` || (returns `*this` && is at the first nesting level of
  inlining)
* takes no parameters || takes only built-in, scalar-type parameters

Examples:

* A class method (first nesting level) calling an overloaded operator (second
  nesting level) returning `*this` will generate (needless) instructions
  equivalent to `MOV AX, *this`. Thus, any overloaded `=`, `+=`, `-=`, etc.
  operator should always return `void`.

  **Certainty**: See the examples in `9d121c7`. This is what allows us to use
  custom types with overloaded assignment operators, with the resulting code
  generation being indistinguishable from equivalent C preprocessor macros.

* Returning *anything else* but `void` or `*this` will first store that result
  in `AX`, leading any branches at the call site to then refer to `AX`.

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

<a id="clobbering-di"></a>

* A reference to the `DI` register. In that case, Turbo C++ always inserts a
  `PUSH DI` at the beginning (before the `MOV BX, SP`), and a `POP DI` before
  returning.

  **Certainty:** Confirmed through reverse-engineering `TCC.EXE`, no way
  around it.
