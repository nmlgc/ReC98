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

These cases should gradually be removed as development goes along, though.

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

## Compatibility

* Use `__asm` as the keyword for inline assembly. This form works in Borland
C++, Open Watcom, and Visual C++, which will ease future third-party ports.

## Build system

* Whenever you edit the `Tupfile`, run `tup generate Tupfile.bat` to update
  the dumb batch fallback script, for systems that can't run Tup.

## Code organization

* Try to avoid repeating numeric constants – after all, easy moddability
  should be one of the goals of this project. For local arrays, use `sizeof()`
  if the size can be expressed in terms of another array or type. Otherwise,
  `#define` a macro if there is a clear intent behind a number.
  (Counterexample: Small, insignificant amounts of pixels in e.g. entity
  movement code.)

* Try rewriting padding instructions in ASM land into TASM directives:

  * `db 0` / `NOP` → `even` / `align 2`
  * `db ?` → `evendata`

  This makes mzdiffs a bit shorter in common cases where a single byte was
  erroneously added somewhere, by providing a chance for the code to catch up
  to its original byte positions.

* Documenting function comments exclusively go into C/C++ header files, right
  above the corresponding function prototype, *not* into ASM slices.

* Newly named symbols in ASM land (functions, global variables, `struc`ts, and
  "sequence of numeric equate" enums) should immediately be reflected in C/C++
  land, with the correct types and calling conventions. Typically, these
  definitions would go into header files, but they can stay in .c/.cpp files
  if they aren't part of a public interface, i.e., not used by unrelated
  functions.

* Compress calls to *known* functions in ASM land to use TASM's one-line,
  interfaced call syntax, whenever all parameters are passed via consecutive
  `PUSH` instructions:

  * `pascal`:
    <table>
        <tr>
            <td>
                <code>push param1</code><br />
                <code>push param2</code><br />
                <code>call foo</code>
            </td>
            <td>→</td>
            <td>
                <code>call foo pascal, param1, param2</code>
            </td>
        </tr>
    </table>

  * `__cdecl`, single call, single parameter:
    <table>
        <tr>
            <td>
                <code>push param1</code><br />
                <code>call foo</code><br />
                <code>pop  cx</code>
            </td>
            <td>→</td>
            <td>
                <code>call foo stdcall, param1</code><br />
                <code>pop  cx</code>
            </td>
        </tr>
    </table>

  * `__cdecl`, single call, multiple parameters:
    <table>
        <tr>
            <td>
                <code>push param2</code><br />
                <code>push param1</code><br />
                <code>call foo</code><br />
                <code>add  sp, 4</code>
            </td>
            <td>→</td>
            <td>
                <code>call foo c, param1, param2</code>
            </td>
        </tr>
    </table>

  * `__cdecl`, single call, 32-bit parameters (Note that you have to use
    `large` whenever a parameter happens to be 32-bit, even if the disassembly
    didn't need it):
    <table>
        <tr>
            <td>
                <code>push  012345678h</code><br />
                <code>pushd param1</code><br />
                <code>call  foo</code><br />
                <code>add   sp, 8</code>
            </td>
            <td>→</td>
            <td>
                <code>call foo c, large param1, large 012345678h</code>
            </td>
        </tr>
    </table>

  * `__cdecl`, multiple calls with a single `add sp` instruction for their
    combined parameter size at the end:
    <table>
        <tr>
            <td>
                <code>push  param2</code><br />
                <code>push  param1</code><br />
                <code>call  foo</code><br />
                <code>[…]</code><br />
                <code>push  param2</code><br />
                <code>pushd param1</code><br />
                <code>call  bar</code><br />
                <code>add   sp, 0Ah</code>
            </td>
            <td>→</td>
            <td>
                <code>call foo stdcall, param1, param2</code><br />
                <code>[…]</code><br />
                <code>call bar stdcall, large param1, param2</code><br />
                <code>add  sp, 10</code>
            </td>
        </tr>
    </table>

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

* Don't use TCC's `-a` command-line option to force a particular code or data
  alignment. Instead, directly spell out the alignment by adding padding
  members to structures, and additional global variables. It's simply not
  worth requiring every structure to work around it. For functions with
  `switch` tables that originally were word-alignment, put a single
  `#pragma option -a2` at the top of the translation unit, after all header
  inclusions.

## Naming conventions

* ASM file extensions: `.asm` if they emit code, `.inc` if they don't
* Macros defining the number of instances of an entity: `<ENTITY>_COUNT`
* Macros defining the number of distinct sprites in an animation: `*_CELS`
* Frame variables counting from a frame count to 0: `*_time`
* Frame variables and other counters starting from 0: `*_frames`
* Generic 0-based IDs: `*_id`
* Generic 1-based IDs, with 0 indicating some sort of absence: `*_num`
* Functionally identical reimplementations or micro-optimizations of
  master.lib functions: `z_<master.lib function name>`

## Identifiers from ZUN's original code

On some occasions, ZUN leaked pieces of the actual PC-98 Touhou source code
during interviews. From these, we can derive ZUN's original names for certain
variables, functions, or macros. To indicate one of those and protect them
from being renamed, put a `/* ZUN symbol [reference] */` comment next to the
declaration of the identifier in question.

Currently, we know about the following [references]:

* `[Strings]`: The symbol name is mentioned in error or debug messages. Can be
  easily verified by grepping over the ReC98 source tree.
* `[MAGNet2010]`: Interview with ZUN for the NHK BS2 TV program MAG・ネット
  (MAG.Net), originally broadcast 2010-05-02. At 09m36s, ZUN's monitor briefly
  displays a piece of TH04's `MAIN.EXE`, handling demo recording and the setup
  of the game's EMS area.

[mzdiff]: https://github.com/nmlgc/mzdiff
[1]: Research/Borland%20C++%20decompilation.md#c
[2]: https://github.com/nmlgc/ReC98/invitations
