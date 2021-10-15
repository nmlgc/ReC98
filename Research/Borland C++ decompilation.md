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

* Local `enum` variables with underlying 1-byte types are always word-aligned,
  regardless of the value of `-a`.

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

* When bit-testing a variable with a 16-bit mask via `&` in a conditional
  expression, the `TEST` is optimized to cover just the high or low byte, if
  possible:
  ```c
  long v = 0xFFFFFFFF; // Works regardless of size or signedness
  char       b00 = (v & 0x00000001) != 0; // TEST  BYTE PTR [v + 0], 1
  char       b08 = (v & 0x00000100) != 0; // TEST  BYTE PTR [v + 1], 1
  char       b16 = (v & 0x00010000) != 0; // TEST DWORD PTR [v + 0], 0x00010000
  char       b24 = (v & 0x01000000) != 0; // TEST DWORD PTR [v + 0], 0x01000000
  char b00_to_15 = (v & 0x0000FFFF) != 0; // TEST  WORD PTR [v + 0], 0xFFFF
  char b16_to_31 = (v & 0xFFFF0000) != 0; // TEST DWORD PTR [v + 0], 0xFFFF0000
  char b08_to_23 = (v & 0x00FFFF00) != 0; // TEST DWORD PTR [v + 0], 0x00FFFF00
  ```

### Arithmetic on a register *after* assigning it to a variable?

Assigment is part of the C expression. If it's a comparison, that comparison
must be spelled out to silence the `Possibly incorrect assignment` warning.

| | |
|-|-|
| `CALL somefunc`<br />`MOV ??, AX`<br />`OR AX, AX`<br />`JNZ ↑` | `while(( ?? = somefunc() ) != NULL)` |

### `SUB ??, imm` vs. `ADD ??, -imm`

`SUB` means that `??` is unsigned. Might require suffixing `imm` with `u` in
case it's part of an arithmetic expression that was promoted to `int`.

### Comparisons

* Any comparison of a register with a literal 0 is optimized to `OR reg, reg`
  followed by a conditional jump, no matter how many calculations and inlined
  functions are involved. Any `CMP reg, 0` instructions must have either come
  from assembly, or referred to a *pointer* at address 0:

  ```c++
  extern void near *address_0; // Public symbol at near address 0
  register int i;

  if(i != reinterpret_cast<int>(address_0)) {
    // ↑ Will emit `CMP reg, 0`
  }
  ```

* `CMP` instructions not followed by jumps correspond to empty `if` statements:

  ```c++
  if(foo > 100) { // CMP foo, 100
  }
  bar = 8;        // MOV bar, 8
  ```

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

| | |
|-|-|
| `MOV ???, [SI+????]` | Only achievable through pointer arithmetic? |

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

* For trivially copyable structures, copy assignments are optimized to an
  equivalent of `memcpy()`:

  | Structure size | (no flags)  |  -G                  |
  |----------------|-------------|----------------------|
  |              1 | via `AL`    | via `AL`             |
  |              2 | via `AX`    | via `AX`             |
  |              3 | `SCOPY@`    | via `AX` and `AL`    |
  |              4 | via `DX:AX` | via `DX:AX`          |
  |        5, 7, 9 | `SCOPY@`    | via `AX` and `AL`    |
  |           6, 8 | `SCOPY@`    | via `AX`             |
  |  10, 12, 14, … | `SCOPY@`    | `REP MOVSW`          |
  |  11, 13, 15, … | `SCOPY@`    | `REP MOVSW`, `MOVSB` |

  (With the `-3` flag, `EAX` is used instead of `DX:AX` in the 4-byte case,
  but everything else stays the same.)

  Breaking triviality by overloading `operator =` in any of the structure
  members also breaks this optimization. In some cases, it might be possible
  to recreate it, by simulating triviality in an overloaded copy assignment
  operator inside the class in question:

  ```c++
  struct Nontrivial {
    nontrivial_char_t e[100];
    // Functions containing local classes aren't expanded inline, so...
    struct Trivial {
      char e[100];
    };

    void operator =(const Nontrivial &other) {
      reinterpret_cast<Trivial &>(*this) = (
          reinterpret_cast<const Trivial &>(other)
      );
    }
  };
  ```

  However, this only generates identical code to the original optimization if
  passing the `other` parameter can be inlined, which isn't always the case.

## Function pointers

Type syntax (cf. [platform.h](../platform.h)):

|                  | … near function           | … far function           |
|------------------|---------------------------|--------------------------|
| Near pointer to… | `int (near *near nn_t)()` | `int (far *near fn_t)()` |
| Far pointer to…  | `int (near *far  nf_t)()` | `int (far *far  ff_t)()` |

Calling conventions can be added before the `*`.

* Assigning a `near` function defined in a different group to a `nn_t` will
  cause a fixup overflow error at link time. The reason for that is pointed
  out in the compiler's assembly output (`-S)`:

  | C                        | ASM                                                                                  |
  |--------------------------|--------------------------------------------------------------------------------------|
  | `void near bar();`       | `extrn _bar:near`                                                                    |
  | `static nn_t foo = bar;` | `mov   word ptr DGROUP:_foo, offset CURRENTLY_​COMPILED_​BUT_​NOT_​ACTUAL_​GROUP_​OF:_bar` |

  The only known way of enforcing this assignment involves declaring `bar()` as
  a far function and then casting its implicit segment away:

  ```c++
  void far bar();
  static nn_t foo = reinterpret_cast<nn_t>(bar);
  ```

  This wrong declaration of `bar()` must, of course, not be `#include`d into
  the translation unit that actually defines `bar()` as a `near` function, as
  it was intended. It can't also be local to an inlined function that's part of
  a public header, since those declarations seem to escape to the global scope
  there.

## `switch` statements

* Sequence of the individual cases is identical in both C and ASM
* Multiple cases with the same offset in the table, to code that doesn't
  return? Code was compiled with `-O`
* Having no more than 3 `case`s (4 with an additional `default`) generates
  comparison/branching code instead of a jump table. The comparisons will be
  sorted in ascending order of the `case` values, while the individual branch
  bodies still match their order given in the code:

  ```c
  switch(foo) {            // MOV AX, foo
  default: foo = 0; break; // CMP AX, 10; JZ @@case_10
  case 30: foo = 3; break; // CMP AX, 20; JZ @@case_20
  case 10: foo = 1; break; // CMP AX, 30; JZ @@case_30
  case 20: foo = 2; break; // MOV foo, 0
  }                        // JMP @@after_switch
                           // @@case_30: MOV foo, 3; JMP @@after_switch
                           // @@case_10: MOV foo, 1; JMP @@after_switch
                           // @@case_20: MOV foo, 2;
                           // @@after_switch:
  ```

* With the `-G` (Generate for speed) option, complicated `switch` statements
  that require both value and jump tables are compiled to a binary search with
  regular conditional branches:

  ```c
  switch(foo) {
  case 0x4B: /* […] */ break;
  case 0x4D: /* […] */ break;
  case 0x11: /* […] */ break;
  case 0x1F: /* […] */ break;
  case 0x20: /* […] */ break;
  case 0x17: /* […] */ break;
  case 0x26: /* […] */ break;
  case 0x19: /* […] */ break;
  case 0x01: /* […] */ break;
  case 0x1C: /* […] */ break;
  }
  ```

  Resulting ASM:

  ```asm
  @@switch:
    MOV AX, foo
    CMP AX, 1Fh
    JZ  @@case_1Fh
    JG  @@GT_1Fh
    CMP AX, 17h
    JZ  @@case_17h
    JG  @@GT_17h_LT_1Fh
    CMP AX, 01h
    JZ  @@case_01h
    CMP AX, 11h
    JZ  @@case_11h
    JMP @@no_case_found

  @@GT_17h_LT_1Fh:
    CMP AX, 1Ch
    JZ  @@case_1Ch
    JMP @@no_case_found

  @@GT_1Fh:
    CMP AX, 4Bh
    JZ  @@case_4Bh
    JG  @@GT_4Bh
    CMP AX, 20h
    JZ  @@case_
    CMP AX, 26h
    JZ  @@case_26h
    JMP @@no_case_found

  @@GT_4Bh:
    CMP AX, 4Dh
    JZ  @@case_4Dh
    JMP @@no_case_found
  ```

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

### `-G` (Generate for speed)

* Replaces

  ```asm
  ENTER <stack size>, 0
  ```

  with

  ```asm
  PUSH BP
  MOV  BP, SP
  SUB  SP, <stack size>
  ```

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

  This also applies to divisors stored in `BX`.

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

Inhibited by:

* identical variable declarations within more than one scope – the
  optimizer will only merge the code *after* the last ASM reference to that
  declared variable. Yes, even though the emitted ASM would be identical:

  ```c
  if(a) {
      int v = set_v();
      do_something_else();
      use(v);
  } else if(b) {
      // Second declaration of [v]. Even though it's assigned to the same stack
      // offset, the second `PUSH c` call will still be emitted separately.
      // Thus, jump optimization only reuses the `CALL use` instruction.
      // Move the `int v;` declaraion to the beginning of the function to avoid
      // this.
      int v = set_v();
      use(v);
  }
  ```

* distinct instances of assignments of local variables in registers to itself

* inlined calls to empty functions

`-O` also merges individual `ADD SP, imm8` or `POP CX` stack-clearing
instructions after `__cdecl` function calls into a single one with their
combined parameter size.

* **[Bug:]** Any emitted call to `SCOPY@` will disable this feature of `-O` for
  all generated code in a translation unit that follows the `SCOPY@` call.

  This can explain why a function might seem impossible to decompile with the
  wrong translation unit layout. If it

  * *doesn't* contain the stack-clearing optimization,
  * but *does* definitely contain optimized jumps,
  * which couldn't be reproduced with the slight jump optimization provided by
    `-O- -y`,

  the translation unit is simply missing a `SCOPY@` before the function in
  question.

### `-y` (Produce line number info)

Provides its own kind of slight jump optimization if combined with `-O-`. Yes,
seriously. Might be required to decompile code that seems to contain both some
of the jump optimizations from `-O` and the stack-clearing instructions after
every function call from `-O-`.

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

## Padding bytes in code segments

* Usually, padding `0x00` bytes are only emitted to word-align `switch` jump
  tables with `-a2`. Anywhere else, it typically indicates the start or end of
  a word-aligned `SEGMENT` compiled from assembly. There are two potential
  workarounds though:

  * The `-WX` option (Create DPMI application) *will* enforce word alignment
    for the code segment, at the cost of slightly different code generation in
    certain places. Since it also adds an additional `INC BP` instruction
    before `PUSH BP`, and an additional `DEC BP` instruction after `POP BP`,
    this option can only really be used in translation units with disabled
    stack frames (`-k-`).

  * `#pragma codestring \x00` unconditionally emits a `0x00` byte. However,
    this won't respect different alignment requirements of surrounding
    translation units.

  **Certainty**: Reverse-engineering `TCC.EXE` confirmed that these are the
  only ways.

## C++

In C++ mode, the value of a `const` scalar-type variable declared at global
scope is always inlined, and not emitted into the data segment. Also, no
externally visible symbol for the variable is emitted into the .OBJ file, even
if the variable was not declared `static`. This makes such variables largely
equivalent to `#define` macros.

### Methods

Note the distinction between *`struct`/`class` distance* and *method distance*:

* Declaring the *type* as `near` or `far` controls whether `this` is passed as
  a near or far pointer.
* Declaring a *method* as `near` or `far` controls whether a method call
  generates a `CALL near ptr` or `CALL far ptr` instruction.

These can be freely combined, and one does not imply the other.

#### Inlining

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

* References to the `SI` or `DI` registers. In that case, Turbo C++ always
  inserts

  * a `PUSH (SI|DI)` at the beginning (after any `PUSH BP; MOV BP, SP`
  instructions and *before* anything else)
  * and a `POP (SI|DI)` before returning.

  **Certainty:** Confirmed through reverse-engineering `TCC.EXE`, no way
  around it.

## Compiler bugs

* Dereferencing a `far` pointer constructed from the `_FS` and `_GS`
  pseudoregisters emits wrong segment prefix opcodes – 0x46 (`INC SI`) and
  0x4E (`DEC SI`) rather than the correct 0x64 and 0x65, respectively.

  **Workaround**: Not happening when compiling via TASM (`-B` on the command
  line, or `#pragma inline`).

* Any emitted call to `SCOPY@` will disable the stack cleanup optimization
  generated by [`-O`](#-o-optimize-jumps) for all generated code in a
  translation unit that follows the `SCOPY@` call.

----

[Bug:]: #compiler-bugs
