# Contribution guidelines

## Rule #1

**`master` must never introduce code changes that change the decompressed
program image, or the unordered set of relocations, of any original game
binary, as compared using [mzdiff].** The only allowed exceptions are:
1) different encodings of identical x86 instructions within code segments
2) padding with `00` bytes at the end of the file.

Other branches are, of course, free to experiment with mods or refactorings.

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
  if the size can be expressed in terms of another array. Otherwise, `#define`
  a macro if there is a clear intent behind a number. (Counterexample: Small,
  insignificant amounts of pixels in e.g. entity movement code.)
* Documenting function comments exclusively go into C/C++ header files, right
  above the corresponding function prototype, *not* into ASM slices.

* New `struc`ts or "sequence of numeric equate" enums defined in ASM land
  should immediately be reflected in a header file in C/C++ land, with the
  correct types and calling conventions.

* Try moving repeated sections of code into a separate `inline` function
  before grabbing the `#define` hammer. Turbo C++ will generally inline
  everything declared as `inline` that doesn't contain `do`, `for`, `while`,
  `goto`, `switch`, `break`, `continue`, or `case`.

* These inlining rules also apply to C++ class methods, so feel free to
  declar classes if you keep thinking "overloaded operators would be nice
  here" or "this code would read really nicely if this functionality was
  encapsulated in a method". (Sometimes, you will have little choice, in
  fact!) Despite Turbo C++'s notoriously outdated C++ implementation, [there
  are quite a lot of possibilites for abstractions that inline perfectly][1].
  Subpixels, as seen in 9d121c7, are the prime example here. Don't overdo it,
  though – use classes where they meaningfully enhance the original procedural
  code, not to replace it with an overly nested, "enterprise-y" class
  hierarchy.

## Naming conventions

* Macros defining the number of instances of an entity: `<ENTITY>_COUNT`
* Functionally identical reimplementations or micro-optimizations of
  master.lib functions: `z_<master.lib function name>`

[mzdiff]: https://github.com/nmlgc/mzdiff
[1]: Research/Borland%20C++%20decompilation.md#C++
