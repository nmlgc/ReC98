## Welcome!

If we've seen you doing any kind of reverse-engineering or modding work on the
PC-98 Touhou games before, you might have already been [invited as a
collaborator][2]. In that case, feel free to create separate branches for your
work directly in this repository – this will immediately inform anyone who
watches this repo or subscribed to a webhook. If you prefer, you can still
use your own fork though.

### What can I do on these separate branches?

Anything – reverse-engineering and decompilation of original ZUN code (which
then could be merged back into `master` after review) or your own custom mods,
no matter how large or small.

For starters, simply naming functions or global variables to reflect their
actual intent will already be helpful. *Any* name is better than
`sub_<something>`, and can always be fixed or improved later.

# Contribution guidelines

## Rule #1

**`master` must never introduce code changes that change the decompressed
program image, or the unordered set of relocations, of any original game
binary, as compared using [mzdiff].** The only allowed exceptions are:
1) different encodings of identical x86 instructions within code segments
2) padding with `00` bytes at the end of the file.

## Taste issues

* Use tabs for indentation.

* Spaces for alignment are allowed, especially if they end up giving the code
  a nice visual structure, e.g. with multiple calls to the same function with
  varying pixel coordinates.

* Don't indent `extern "C"` blocks that span the entire file.

* Always use `{ brackets }`, even around single-statement conditional
  branches.
* Add spaces around binary operators. `for(i = 0; i < 12; i++)`

* Variables should be *signed* in the absence of any ASM instruction
  (conditional jump, arithmetic, etc.) or further context (e.g. parameters
  with a common source) that defines their signedness. If a variable is used
  in both signed and unsigned contexts, declare it as the more common one.

## Code organization

* Try to avoid repeating numeric constants – after all, easy moddability
  should be one of the goals of this project. For local arrays, use `sizeof()`
  if the size can be expressed in terms of another array or type. Otherwise,
  `#define` a macro if there is a clear intent behind a number.
  (Counterexample: Small, insignificant amounts of pixels in e.g. entity
  movement code.)

* Try rewriting `db 0` or `NOP` padding instructions in ASM land into `even`
  or `align 2` directives. This makes mzdiffs a bit shorter in common cases
  where a single byte was erroneously added somewhere, by providing a chance
  for the code to catch up to its original byte positions.

* Documenting function comments exclusively go into C/C++ header files, right
  above the corresponding function prototype, *not* into ASM slices.

* Newly found function prototypes, `struc`ts, and "sequence of numeric equate"
  enums defined in ASM land should immediately be reflected in a header file
  in C/C++ land, with the correct types and calling conventions.

* Try moving repeated sections of code into a separate `inline` function
  before grabbing the `#define` hammer. Turbo C++ will generally inline
  everything declared as `inline` that doesn't contain `do`, `for`, `while`,
  `goto`, `switch`, `break`, `continue`, or `case`.

* These inlining rules also apply to C++ class methods, so feel free to
  declare classes if you keep thinking "overloaded operators would be nice
  here" or "this code would read really nicely if this functionality was
  encapsulated in a method". (Sometimes, you will have little choice, in
  fact!) Despite Turbo C++'s notoriously outdated C++ implementation, [there
  are quite a lot of possibilites for abstractions that inline perfectly][1].
  Subpixels, as seen in 9d121c7, are the prime example here. Don't overdo it,
  though – use classes where they meaningfully enhance the original procedural
  code, not to replace it with an overly nested, "enterprise-y" class
  hierarchy.

## Decompilation

* Don't try to decompile self-modifying code. Yes, it may be *possible* by
  calculating addresses relative to the start of the function, but as soon as
  someone starts modding or porting that function, things *will* crash at
  runtime. Inline ASM in C/C++ source files is fine, that will trip up future
  port developers at compile time. Self-modifying code can only do the same if
  it's kept in separate ASM files.

## Naming conventions

* ASM file extensions: `.asm` if they emit code, `.inc` if they don't
* Macros defining the number of instances of an entity: `<ENTITY>_COUNT`
* Functionally identical reimplementations or micro-optimizations of
  master.lib functions: `z_<master.lib function name>`

## Identifiers from ZUN's original code

On some occasions, ZUN leaked pieces of the actual PC-98 Touhou source code
during interviews. From these, we can derive ZUN's original names for certain
variables, functions, or macros. To indicate one of those and protect them
from being renamed, put a `/* ZUN symbol [reference] */` comment next to the
declaration of the identifier in question.

Currently, we know about the following [references]:

* `[MAGNet2010]`: Interview with ZUN for the NHK BS2 TV program MAG・ネット
  (MAG.Net), originally broadcast 2010-05-02. At 09m36s, ZUN's monitor briefly
  displays a piece of TH04's `MAIN.EXE`, handling demo recording and the setup
  of the game's EMS area.

[mzdiff]: https://github.com/nmlgc/mzdiff
[1]: Research/Borland%20C++%20decompilation.md#c
[2]: https://github.com/nmlgc/ReC98/invitations
