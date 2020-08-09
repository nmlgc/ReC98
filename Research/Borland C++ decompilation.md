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

## Integer arithmetic

| | |
|-|-|
| `ADD [m8], imm8` | Only achievable through a C++ method operating on a  member? |
| `MOV AL, [m8]`<br />`ADD AL, imm8`<br />`MOV [m8], AL` | Opposite; *not* an inlined function |
| `CWD`<br />`SUB AX, DX`<br />`SAR AX, 1` | `AX / 2`, `AX` is *int* |
| `MOV [new_var], AX`<br />`CWD`<br />`XOR AX, DX`<br />`SUB AX, DX` | `abs(AX)`, defined in `<stdlib.h>`. `AX` is *int* |

### Arithmetic on a register *after* assigning it to a variable?

Assigment is part of the C expression. If it's a comparison, that comparison
must be spelled out to silence the `Possibly incorrect assignment` warning.

| | |
|-|-|
| `CALL somefunc`<br />`MOV ??, AX`<br />`OR AX, AX`<br />`JNZ ↑` | `while(( ?? = somefunc() ) != NULL)` |

### `SUB ??, imm` vs. `ADD ??, -imm`

`SUB` means that `??` is unsigned. Might require suffixing `imm` with `u` in
case it's part of an arithmetic expression that was promoted to `int`.

## Floating-point arithmetic

* Since the x87 FPU can only load from memory, all temporary results of
  arithmetic are spilled to one single compiler-generated variable (`fpu_tmp`)
  on the stack, which is reused across all of the function:

  | | |
  |-|-|
  | `MOV  AX, myint`<br />`INC  AX`<br />`MOV  fpu_tmp, ax`<br />`FILD fpu_tmp`<br />`FSTP ret` | `float ret = (myint + 1)` |

* The same `fpu_tmp` variable is also used as the destination for `FNSTSW`,
  used in comparisons.

* Performing arithmetic or comparisons between `float` and `double` variables
  *always* `FLD`s the `float` first, before emitting the corresponding FPU
  instruction for the `double`, regardless of how the variables are placed in
  the expression. The instruction order only matches the expression order for
  literals:

  ```c++
  char ret;
  float f;
  double d;

  ret = (f > d);     // FLD f,     FCOMP d
  ret = (d > f);     // FLD f,     FCOMP d

  ret = (d > 3.14f); // FLD d,     FCOMP 3.14f
  ret = (3.14f > d); // FLD 3.14f, FCOMP d
  ret = (f > 3.14);  // FLD f,     FCOMP 3.14 + 4
  ret = (3.14 > f);  // FLD 3.14,  FCOMP f + 4
  ```

## Assignments

* When assigning to a array element at a variable or non-0 index, the array
  element address is typically evaluated before the expression to be assigned.
  But when assigning
  * the result of any arithmetic expression of a *16-bit type*
  * to an element of a `far` array of a *16-bit type*,

  the expression will be evaluated first, if its signedness differs from that
  of the array:

  ```c
  int far *s;
  unsigned int far *u;
  int s1, s2;
  unsigned int u1, u2;

  s[1] = (s1 | s2); // LES BX, [s]; MOV AX, s1; OR AX, s2; MOV ES:[BX+2], AX
  s[1] = (s1 | u2); // MOV AX, s1; OR AX, u2; LES BX, [s]; MOV ES:[BX+2], AX
  s[1] = (u1 | u2); // MOV AX, u1; OR AX, u2; LES BX, [s]; MOV ES:[BX+2], AX

  u[1] = (s1 | s2); // MOV AX, s1; OR AX, s2; LES BX, [u]; MOV ES:[BX+2], AX
  u[1] = (s1 | u2); // LES BX, [u]; MOV AX, s1; OR AX, u2; MOV ES:[BX+2], AX
  u[1] = (u1 | u2); // LES BX, [u]; MOV AX, u1; OR AX, u2; MOV ES:[BX+2], AX
  ```

* Assigning `AX` to multiple variables in a row also indicates multiple
  assignment in C:

  ```c
  // Applies to all storage durations
  int a, b, c;

  a = 0;  // MOV [a], 0
  b = 0;  // MOV [b], 0
  c = 0;  // MOV [c], 0

  a = b = c = 0; // XOR AX, AX;  MOV [c], AX; MOV [b], AX;  MOV [a], AX;
                 // Note the opposite order of variables!
  ```

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

### Pushing pointers

When passing a `near` pointer to a function that takes a `far` one, the
segment argument is sometimes `PUSH`ed immediately, before evaluating the
offset:

```c++
#pragma option -ml

struct s100 {
  char c[100];
};

extern s100 structs[5];

void __cdecl process(s100 *element);

void foo(int i) {
  process((s100 near *)(&structs[i])); // PUSH DS; (AX = offset); PUSH AX;
  process((s100 far *)(&structs[i]));  // (AX = offset); PUSH DS; PUSH AX;
}
```

## Flags

### `-Z` (Suppress register reloads)

* The tracked contents of `ES` are reset after a conditional statement. If the
  original code had more `LES` instructions than necessary, this indicates a
  specific layout of conditional branches:

  ```c++
  struct foo {
    char a, b;

    char es_not_reset();
    char es_reset();
  };

  char foo::es_not_reset() {
    return (
      a    // LES BX, [bp+this]
      && b // `this` still remembered in ES, not reloaded
    );
  }

  char foo::es_reset() {
    if(a) return 1; // LES BX, [bp+this]
    // Tracked contents of ES are reset
    if(b) return 1; // LES BX, [bp+this]
    return 0;
  }
  ```

### `-3` (80386 Instructions) + `-Z` (Suppress register reloads)

Bundles two consecutive 16-bit function parameters into a single 32-bit one,
passed via a single 32-bit `PUSH`. Currently confirmed to happen for literals
and structure members whose memory layout matches the parameter list and
calling convention. Signedness doesn't matter.

Won't happen for two consecutive 8-bit parameters.

```c
// Works for all storage durations
struct {          int  x, y; } p;
struct { unsigned int  x, y; } q;

void __cdecl foo_c(char x, char y);
void __cdecl foo_s(int x, int y);
void __cdecl foo_u(unsigned int x, unsigned int y);

foo_s(640, 400); // PUSH LARGE 1900280h
foo_u(640, 400); // PUSH LARGE 1900280h
foo_s(p.x, p.y); // PUSH LARGE [p]
foo_u(p.x, p.y); // PUSH LARGE [p]
foo_s(q.x, q.y); // PUSH LARGE [p]
foo_u(q.x, q.y); // PUSH LARGE [p]
foo_c(100, 200); // PUSH 200; PUSH 100
```

### `-O` (Optimize jumps)

Also merges individual `ADD SP, imm8` or `POP CX` stack-clearing instructions
after `__cdecl` function calls into a single one with their combined parameter
size.

Inhibited by:

* identical variable declarations within more than one scope – the
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

* distinct instances of assignments of local variables in registers to itself

* inlined calls to empty functions

## Inlining

Always worth a try to get rid of a potential macro. Some edge cases don't
inline optimally though:

* Assignments to a pointer in `SI` – that pointer is moved to `DI`,
  [clobbering that register](#clobbering-di). Try a [class method](#C++)
  instead.
* Nested `if` statements – inlining will always generate a useless
  `JMP SHORT $+2` at the end of the last branch.

## Initialization

Any initialization of a variable with static storage duration (even a `const`
one) that involves function calls (even those that would regularly inline)
will emit a `#pragma startup` function to perform that initialization at
runtime.
This extends to C++ constructors, making macros the only way to initialize
such variables with arithmetic expressions at compile time.

```c
#define FOO(x) (x << 1)

inline char foo(const char x)  {
    return FOO(x);
}

const char static_storage[3] = { FOO(1), foo(2), FOO(3) };
```
Resulting ASM (abbreviated):
```asm
  .data
static_storage  db  2, 0, 6

  .code
@_STCON_$qv	proc	near
	push bp
	mov  bp, sp
	mov  static_storage[1], 4
	pop	 bp
	ret
@_STCON_$qv	endp
```

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

### Boilerplate for constructors defined outside the class declaration

```c++
struct MyClass {
  // Members…

  MyClass();
};

MyClass::MyClass() {
  // Initialization…
}
```

Resulting ASM:

```asm
; MyClass::MyClass(MyClass* this)
; Exact instructions differ depending on the memory model. Model-independent
; ASM instructions are in UPPERCASE.
@MyClass@$bctr$qv proc
  PUSH  BP
  MOV   BP, SP
  ; (saving SI and DI, if used in constructor code)
  ; (if this, 0)
  JNZ   @@ctor_code
  PUSH  sizeof(MyClass)
  CALL  @$bnew$qui      ; operator new(uint)
  POP   CX
  ; (this = value_returned_from_new)
  ; (if this)
  JZ    @@ret

@@ctor_code:
  ; Initialization…

@@ret:
  ; (retval = this)
  ; (restoring DI and SI, if used in constructor code)
  POP   BP
  RET
@MyClass@$bctr$qv endp
```

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
