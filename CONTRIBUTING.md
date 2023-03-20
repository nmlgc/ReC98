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

## Setup

Before committing anything, enable the Git hooks from the `hooks/` subdirectory
to automatically catch common mistakes:

```shell
git config --local core.hooksPath hooks/
```

# Contribution guidelines

## Rule #1

**`master` must never introduce code that changes the decompressed program
image, or the unordered set of relocations, of any original game binary, as
compared using [mzdiff].** The only allowed exceptions are:

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
  branches and single-instruction inline assembly.

* The opening `{ ` bracket of a function goes into
  * the next line if the function is non-inlined (Linux style), and
  * the end of the line with the closing `)` if the function is inlined.

* Add spaces around binary operators. `for(i = 0; i < 12; i++)`

* Variables should be *signed* in the absence of any ASM instruction
  (conditional jump, arithmetic, etc.) or further context (e.g. parameters
  with a common source) that defines their signedness. If a variable is used
  in both signed and unsigned contexts, declare it as the more common one.

## Compatibility

* Despite the games' native encoding being Shift-JIS, most files should be
  encoded in UTF-8, as it's simply more comfortable to work with in modern
  tools. The only (necessary) exceptions are

  * the big .ASM dump files in the root directory,
  * and any files in the per-game `shiftjis/` subdirectory. All hardcoded
    Shift-JIS strings should be put there. With files full of Shift-JIS text,
    it's also easier to see when an editor didn't recognize the encoding,
    which keeps the annoyance from accidentally destroyed files to a minimum.

* Use `_asm` as the keyword for decently sane or temporary inline assembly.
  This variation has the biggest compiler support, which will ease potential
  future ports to other x86 systems:

   | Compiler support                  | `asm` |  `_asm` | `__asm` |
   |-----------------------------------|-------|---------|---------|
   | Microsoft QuickC 2.51             |       |    ✔    |         |
   | Turbo C++ 4.0                     |   ✔   |    ✔    |    ✔    |
   | Borland C++ 5.5.1                 |   ✔   |    ✔    |    ✔    |
   | Open Watcom 2.0                   |       |    ✔    |    ✔    |
   | Visual Studio 2022                |       |    ✔    |    ✔    |
   | Clang 13 (default)                |       |         |         |
   | Clang 13 (with `-fms-extensions)` |   ✔   |    ✔    |    ✔    |

  * Conversely, use `asm` as the keyword for the particularly dumb small
    pieces of inline assembly that refer to or depend on register
    pseudovariables from surrounding code, and are just needed to ensure
    correct code generation. These *should* break on other compilers.

    Example:

    ```cpp
    _CX = loop_count;
    loop_label: {
        // …

        // `asm`, with no underscore, because the x86 LOOP instruction
        // branches depending on the value in CX, which was set using a
        // pseudovariable access above.
        asm { loop	loop_label; }
    }
    ```

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

* If an ASM translation unit requires the `.MODEL` directive *and* uses 32-bit
  80386 instructions via `.386`, make sure to specify the `USE16` model
  modifier, as in

  ```asm
  .model use16 large
  ```

  Otherwise, some TASM versions might create 32-bit segments if `.386` is
  specified before `.MODEL`, causing all sorts of issues and messing up
  segment alignments. (TASM32 version 5.3 is known to do this, for example.)
  Specifying `USE16` is a lot more understandable than switching back and
  forth between CPUs, or relying on the order of the `.MODEL` and `.386`
  directives to imply the default 16-bit behavior.

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

* In ASM functions with ZUN's silly `MOV BX, SP` stack frame, use the `arg_bx`
  and `ret_bx` macros from `th03/arg_bx.inc` to declare parameters and return
  with the correct amount of bytes released from the stack. The parameter
  names only get a single `@` as their prefix in this case:
  <table>
        <tr>
            <td>
                <code>foo proc near</code><br />
                <code>arg_2 = byte ptr 2</code><br />
                <code>arg_0 = word ptr 4</code><br />
                <code></code><br />
                <code>mov bx, sp</code><br />
                <code>mov	al, ss:[bx+arg_2]</code><br />
                <code>mov	bx, ss:[bx+arg_0]</code><br />
                <code>ret 2</code><br />
                <code>foo endp</code>
            </td>
            <td>→</td>
            <td>
                <code>foo	proc near</code><br />
                <code>arg_bx  near, @arg_2:byte, @arg_0:word</code><br />
                <code></code><br />
                <code></code><br />
                <code></code><br />
                <code>mov	al, @arg_0</code><br />
                <code>mov	bx, @arg_2</code><br />
                <code>ret_bx</code><br />
                <code>foo endp</code>
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
  are quite a lot of possibilities for abstractions that inline perfectly][1].
  Subpixels, as seen in 9d121c7, are the prime example here. Don't overdo it,
  though – use classes where they meaningfully enhance the original procedural
  code, not to replace it with an overly nested, "enterprise-y" class
  hierarchy.

* Prefer `#pragma option -zC` and `#pragma option -zP` for renaming code
  segments and groups. It might look uglier than `#pragma codeseg`, but has the
  advantage of not generating an empty segment with the default name and the
  default padding. This is particularly relevant [if the `-WX` option is used
  to enforce word-aligned code segments][3]: That empty default segment would
  otherwise also (unnecessarily) enforce word alignment for the segment that
  ends up following the empty default one. It also reduces a bit of bloat from
  linker map files.

  * These options can only be used "at the beginning" of a translation unit –
    before the first non-preprocessor and non-comment C language token. Any
    other `#pragma option` settings should also be put there.

  * `#pragma codeseg` will still be necessary if a translation unit emits code
    into more than one segment. In that case, use `#pragma option -zC` and
    `#pragma option -zP` for the first segment and group, and `#pragma codeseg`
    for the second and later ones.

  * When working with `near` functions, `#pragma codeseg` directives might be
    needed in headers to ensure that other translation units [calculate their
    references correctly][4]. In that case, these directives should *only*
    occur there if possible, and not in the `.cpp` file corresponding to such a
    header.

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
  `switch` tables that originally were word-aligned, put a single
  `#pragma option -a2` *after* all header inclusions.

## Portability

* Use `__seg *` wherever it doesn't make the code all too ugly. Type
  conversions into `far` pointers automatically set the offset to 0, so
  `MK_FP` is not necessary in such a case:

  ```c++
  void resident_set(resident __seg *seg)
  {
    // Redundant, and requires the MK_FP() macro to be declared
    resident_t far *resident = MK_FP(seg, 0);

    // Does the same, without requiring a macro
    resident_t far *resident = seg;
  }
  ```

* All original `.EXE` binaries use the *large* memory model, meaning that both
  function and data pointers are `far` by default. Therefore, pointers and
  references should only explicitly be declared `far` if

  1. they are actually constructed from a segment and an offset via the two
     methods above, or
  2. the code performs segment/offset arithmetic on them.

## Naming conventions

* ASM file extensions: `.asm` if they emit code, `.inc` if they don't
* Macros defining the number of instances of an entity: `<ENTITY>_COUNT`
* Macros defining the number of distinct sprites in an animation: `*_CELS`
* Frame variables counting from a frame count to 0: `*_time`
* Frame variables and other counters starting from 0: `*_frames`
* Functions that show multi-frame animations in a blocking way, using their own
  `frame_delay()` calls: `*_animate`
* Generic 0-based IDs: `*_id`
* Generic 1-based IDs, with 0 indicating some sort of absence: `*_num`
* Functionally identical reimplementations or micro-optimizations of
  master.lib functions: `z_<master.lib function name>`
* Plain-old-data `struct`s: `struct snake_case_t {}`
* `struct`s and `class`es with C++ methods: `(struct|class) CamelCase {}`
  * Multiple consecutive capital letters are allowed.
* `template` `struct`s and `class`es, as well as their template parameters, are
  CamelCase regardless of whether they have methods or not.
* Fallback naming scheme for space-saving `union`s whose members have wildly
  unrelated semantics: `u1`, `u2`, `u3`, …

## Identifiers from ZUN's original code

On some occasions, ZUN leaked pieces of the actual PC-98 Touhou source code
during interviews. From these, we can derive ZUN's original names for certain
variables, functions, or macros. To indicate one of those, put a
`/* ZUN symbol [reference] */` comment next to the declaration and definition
of the identifier in question. Preserving any aspect from leaked ZUN code just
for the sake of it is not mandatory though, and in fact tends to make the
resulting code harder to understand. If you can come up with a better (or less
wrong) name, go for it.

Currently, we know about the following [references]:

* `[Strings]`: The symbol name is mentioned in error or debug messages. Can be
  easily verified by grepping over the ReC98 source tree.
* `[MAGNet2010]`: Interview with ZUN for the NHK BS2 TV program MAG・ネット
  (MAG.Net), originally broadcast 2010-05-02. At 09m36s, ZUN's monitor briefly
  displays a piece of TH04's `MAIN.EXE`, handling demo recording and the setup
  of the game's EMS area.

## Labeling weird or broken code

There's a lot of it in these games, and each such piece of code is relevant to
a different audience of this codebase. While `master` won't fix anything in the
original code, it is the right branch to point out all of these issues in
source code comments. By assigning specific labels based on the code's impact,
`master` can make it easier for other branches and forks to identify and fix
only the subset of issues they care about.

When categorizing such issues, first ask whether a fix could be <a
id="observable" href="#observable">🔗 observed</a>: Would it change any of the
individual frames rendered by the game, as defined by the original frame delay
boundaries?

### Categories

#### `ZUN bloat`

Code that wastes memory, CPU cycles, or even just the mental capacity of anyone
trying to read and understand the code. The broadest label, encompassing all
code that could be significantly simplified without making [observable]
changes.

Examples:

* Splitting the game into multiple executables for misguided reasons
* Code without any effect
* Assembly code at any place above the lowest level of the platform layer
* Unused code or data

Bloat is removed on the aptly named `debloated` branch. That branch is the
recommended foundation for nontrivial mods that don't care about being
byte-for-byte comparable to ZUN's original binary.

#### `ZUN landmine`

Code that is technically wrong, but does *not* have [observable] effects within
the following assumptions:

* ZUN's original build of the decompiled game is correctly installed and
  accessible, together with all its original data files.
* No files of this installation were modified.
* All files can be read as intended without I/O errors.
* The game runs on a clean PC-98 DOS system that matches the official minimum
  system requirements, with enough free memory.
* The only active TSRs are the game's intended sound driver, an [expanded
  memory][5] manager, and the resident part of `COMMAND.COM`.
* All system-level interfaces (interrupt APIs, I/O ports, and special memory
  segments) behave as typically expected.

The effects might never be triggered by the original data, or they might be
mitigated by other parts of the original binary, including Turbo C++ 4.0J
code generation details.

Examples:

* Out-of-bounds memory accesses with no consequences
* Every [bug] in unused code
* Missing error handling for file I/O

Landmines are likely to cause issues as soon as the game is modded or compiled
with a different compiler, which breaks the above assumptions. Therefore, it
should be fixed on every branch that breaks the code or data layout of the
game. Most notably, they are removed from the `debloated` and `anniversary`
branches.

#### `ZUN bug`

Logic errors or incorrect programming language / interface / system use with
[observable] negative or unexpected effects in ZUN's original build. The
surrounding code must provide evidence that ZUN did not intend the bug. Fixing
these issues must not affect hypothetical replay compatibility, and any
resulting visual changes must match ZUN's provable intentions. As a result of
these constraints, bugs are pretty much limited to rendering issues and
crashes.

Examples:

* All crashes
* Sprites that were created to be shown in a single place, but are never
  rendered because of a logic error in their clipping condition
* Blitting operations that are limited to the PC-98's 8×1-pixel VRAM byte grid,
  but reflect the position of entities that can move at a finer granularity.
  This was likely done for performance reasons rather than artistic ones.

Bugs are fixed on the `anniversary` branch. Critical ones may also receive
individual bugfix branches that preserve the code and data layout of the
original game by only modifying as few bytes as possible.

#### `ZUN quirk`

Weird code that looks incorrect in context, but either defines game logic or is
part of a possibly intentional visual effect. Fixing these issues would desync
a hypothetical replay recorded on the original game, or affect the visuals so
much that the result is no longer faithful to ZUN's original release. It might
very well be called a fangame at that point.

Examples:

* Incorrect or inconsistent coordinate calculations of gameplay entities
* Inconsistencies in visual effects that lack the clear evidence necessary for
  a [bug]. One example is the missing quarter of the big dotted circle featured
  in an early pattern of the TH01 Elis fight: There is code that is supposed to
  render the quarter, but doesn't due to an incorrect angle calculation. In
  this case, it can be argued that this is either a bug (because the
  inconsistency exists in the first place) or a feature (because the
  inconsistency is easily spotted, and ZUN did not fix it).

Fixing quirks is fanfiction territory and thus out of scope for the main ReC98
project, but forks are welcome to do so.

#### Summary

|                             | Bloat | Landmines | Bugs | Quirks |
| --------------------------- | ----- | --------- | ---- | ------ |
| Fix would be [observable]   | No    | No        | Yes  | Yes    |
| Fix would desync replays    | No    | No        | No   | Yes    |
| Might have been intentional | No*   | No        | No   | Yes    |

(* The games contain code that explicitly delays execution at microsecond,
millisecond, and frame granularity. If bloated code does not include explicit
delays, it makes sense to assume that it was not written to be slow on purpose,
and the bloat simply came from ZUN's lack of knowledge and experience at the
time of the respective game's development. [He admitted as much in an
interview.](https://en.touhougarakuta.com/article/specialtaidan_zun_hiroyuki_2-en))

The comments for each of these issues should be prefixed with a `ZUN
(bloat|landmine|bug|quirk):` label, and include a description that points out
the specific issue. This description can be left out for obvious cases of
bloat, like unused variables or code with no effect.

----

[mzdiff]: https://github.com/nmlgc/mzdiff
[1]: Research/Borland%20C++%20decompilation.md#c
[2]: https://github.com/nmlgc/ReC98/invitations
[3]: Research/Borland%20C++%20decompilation.md#padding-bytes-in-code-segments
[4]: Research/Borland%20C++%20decompilation.md#memory-segmentation
[5]: https://en.wikipedia.org/wiki/Expanded_memory
[bug]: #zun-bug
[observable]: #observable
