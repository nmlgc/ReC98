# The Touhou PC-98 Restoration Project (*"ReC98"*)

[![4-week crowdfunding goal…](https://rec98.nmlgc.net/badge/cap)](https://rec98.nmlgc.net)

|    Reverse-engineered: | [![All games…](https://rec98.nmlgc.net/badge/re)][HP] [![TH01…](https://rec98.nmlgc.net/badge/re/1)][HP] [![TH02…](https://rec98.nmlgc.net/badge/re/2)][HP] [![TH03…](https://rec98.nmlgc.net/badge/re/3)][HP] [![TH04…](https://rec98.nmlgc.net/badge/re/4)][HP] [![TH05…](https://rec98.nmlgc.net/badge/re/5)][HP] |
|-----------------------:|:---------------|
| [Finalized]: | [![All games…](https://rec98.nmlgc.net/badge/td)][HP] [![TH01…](https://rec98.nmlgc.net/badge/td/1)][HP] [![TH02…](https://rec98.nmlgc.net/badge/td/2)][HP] [![TH03…](https://rec98.nmlgc.net/badge/td/3)][HP] [![TH04…](https://rec98.nmlgc.net/badge/td/4)][HP] [![TH05…](https://rec98.nmlgc.net/badge/td/5)][HP] |
| [Position independence]: | [![All games…](https://rec98.nmlgc.net/badge/pi)][HP] [![TH01…](https://rec98.nmlgc.net/badge/pi/1)][HP] [![TH02…](https://rec98.nmlgc.net/badge/pi/2)][HP] [![TH03…](https://rec98.nmlgc.net/badge/pi/3)][HP] [![TH04…](https://rec98.nmlgc.net/badge/pi/4)][HP] [![TH05…](https://rec98.nmlgc.net/badge/pi/5)][HP] |

[Check the homepage for more detailed progress numbers and information about the crowdfunding!][HP]

[HP]: https://rec98.nmlgc.net
[Finalized]: https://rec98.nmlgc.net/blog/2021-12-15
[Position independence]: https://rec98.nmlgc.net/faq#pi-what

----

### Overview

This project aims to perfectly reconstruct the source code of the first five [Touhou Project](http://en.wikipedia.org/wiki/Touhou_Project) games by *ZUN Soft* (now *Team Shanghai Alice*), which were originally released exclusively for the NEC PC-9801 system.

The original games in question are:

* TH01: 東方靈異伝　～ The Highly Responsive to Prayers (1997)
* TH02: 東方封魔録　～ the Story of Eastern Wonderland (1997)
* TH03: 東方夢時空　～ Phantasmagoria of Dim.Dream (1997)
* TH04: 東方幻想郷　～ Lotus Land Story (1998)
* TH05: 東方怪綺談　～ Mystic Square (1998)

Since we only have the binaries, we obviously can't know how ZUN named any variables and functions, and which comments the original code was surrounded with. *Perfect* therefore means that the binaries compiled from the code in the ReC98 repository are [indistinguishable] from ZUN's original builds, making it impossible to *disprove* that the original code *couldn't* have looked like this. This property is maintained for every Git commit along the way.

Aside from the preservation angle and the resulting deep insight into the games' mechanics, the code can then serve as the foundation for any type of mod, or any port to non-PC-98 platforms, developed by the community. This is also why ReC98 values *readable and understandable* code over a pure decompilation.

#### Why?
There are a number reasons why achieving moddability via full decompilation seems to be more worthwhile for the PC-98 games, in contrast to a [PyTouhou](http://pytouhou.linkmauve.fr/)-style black-box reimplementation:

* While stage enemies and their bullet patterns are controlled by bytecode in TH04's and TH05's .STD files that *could* just be interpreted by an alternate VM, midboss and boss battles are entirely hardcoded into the executables.
* Even though complete decompilation will take a long time, partial reverse-engineering results will be very useful to modders who just want to work on the original PC-98 versions of the games.
* PC-98 emulation is messy and overly complicated. It has been getting better as of 2018 thanks to [DOSBox-X](https://github.com/joncampbell123/dosbox-x) adding support for the platform, but even at its best, it will always consume way more system resources than what would be appropriate for those games.
* thcrap-style multilingual translation on PC-98 would be painful for languages with non-ASCII scripts. The obvious method of modifying the font ROM specifically for each language is ugly and won't work on real hardware, so a custom renderer would be needed. That by itself requires a lot of reverse-engineering and, preferably, compilable source code to avoid the limits of hex-editing. Or, even better, the prospect to do this entirely on a more modern system.
* These games stopped being sold in 2002, ZUN has confirmed on multiple occasions to have lost all the data of the "earlier games" <sup>[citation needed]</sup>, and PC-98 hardware is long obsolete. In short, these games are as abandoned as they can possibly be, and are unlikely to ever turn a profit again.

#### Is this even viable?

Ever since crowdfunding has brought a continuous stream of support, progress has been steady. Decompilation of TH01 fully completed in August 2022, and the remaining games are only a matter of time.

Over the years, this project led to a deep understanding of the original compilers and PC-98 hardware, to the point where the decompilation itself has become pretty mechanical. To ensure that this project remains both worthwhile to support and interesting to work on, its focus has shifted more toward meticulous documentation and review of ZUN's original code. The [project blog] details all the findings in a more generally readable way and has arguably become the main attraction, with the source code reconstruction itself almost turning into a byproduct of the underlying deep research into these games.

The project started out pretty viable as well. During the development of the static English patches for these games, we identified two main libraries used across all 5 games, and even found their source code. These are:

* [master.lib](http://www.koizuka.jp/~koizuka/master.lib/), a 16-bit x86 assembly library providing an abstraction layer for all components of a PC-98 DOS system
* as well as the Borland C/C++ runtime library, version 4.0.
* Additionally, TH01 includes the [Pi loader library by 電脳科学研究所/BERO](http://www.vector.co.jp/soft/dos/prog/se037608.html),
* and TH03's `ZUNSP.COM` (accessible via `ZUN.COM -4`) is a rebranded version of Promisence Soft's `SPRITE16.COM`, a 16-color PC-98 EGC display driver, version 0.04, which was bundled with the sample game *StormySpace*.

master.lib and the C/C++ runtime alone make up a sizable amount of the code in all the executables. In TH05, for example, they amount to 74% of all code in `OP.EXE`, and 40% of all code in `MAIN.EXE`. That's already quite a lot of code we do not have to deal with. Identifying the rest of the code shared across the games will further reduce the workload to a more acceptable amount.

With DOSBox-X and [the Debug edition of Neko Project II](https://github.com/nmlgc/np2debug), we also have two open-source PC-9821 emulators capable of running the games. These have helped to answer most hardware-related questions, together with old books about PC-98 development and occasional tests on real hardware.

## Dumped executables
* TH01: `zunsoft.com`, `op.exe`, `reiiden.exe`, `fuuin.exe`
* TH02: zun.com (<s>`ongchk.com`</s>, `zuninit.com`, `zun_res.com`, <s>`zunsoft.com`</s>), `op.exe`, `main.exe`, `maine.exe`
* TH03: zun.com (<s>`ongchk.com`</s> [-1], <s>`zuninit.com`</s> [-2], <s>`zunsoft.com`</s> [-3], `zunsp.com` [-4], `res_yume.com` [-5]), `op.exe`, `main.exe`, `mainl.exe`
* TH04: zun.com (<s>`ongchk.com`</s> [-O], `zuninit.com` [-I], `res_huma.com` [-S], `memchk.com` [-M]), `op.exe`, `main.exe`, `maine.exe`
* TH05: zun.com (<s>`ongchk.com`</s> [-O], `zuninit.com` [-I], `res_kso.com` [-S], `gjinit.com` [-G], `memchk.com` [-M]), `op.exe`, `main.exe`, `maine.exe`

Crossed-out files are identical to their version in the previous game. ONGCHK.COM is part of the PMD sound driver by KAJA, and therefore doesn't need to be disassembled either; we only need to keep the binary to allow bit-perfect rebuilds of ZUN.COM.

**This project does not include any asset data from the original PC-98 releases. Running the compiled executables will still require an existing copy of the original games.**

## Branches

* [`master`]: ZUN's original code, without mods or bugfixes
* [`debloated`]: Rearchitected version of ZUN's code that is easier to read and modify, and builds smaller and faster PC-98 binaries. Only removes [bloat] and [landmines]; all [bugs] and [quirks] from ZUN's original code are left in place. **Ports should start from that branch**, and it's also the recommended base for mods that don't care about similarity to the original binary.
* [`anniversary`]: Takes `debloated` and additionally fixes [bugs], achieving a smoother and flicker-free gameplay experience on the PC-98 platform while still leaving [quirks] in place. Might be an even better starting port for mods and ports.
* [`BossRush`]
* [`th03_no_gdc_frequency_check`]: Allows TH03 to be run with the GDC clock set to 5&nbsp;MHz. The original game enforces 2.5&nbsp;MHz, but doesn't functionally require it, even on real hardware.
* [`xJeePx`]: Code changes for xJeePx's 2014 English translation patch.
* [`th01_critical_fixes`]: Fixes [two critical bugs in TH01]:
  * Potential heap corruptions in the game's debug mode when decrementing boss HP by holding ↵ Return while the HP bar is still filling up.
  * General Protection Faults when defeating bosses with diagonally moving shootout lasers on screen. These are most commonly reported for Elis or Mima, and when playing on real hardware or Anex86.
* [`th01_end_pic_optimize`]: Speeds up image blitting in TH01's cutscenes to 50% of the original runtime. Mainly serves as an example of how to get close to optimal EGC-powered blitting code out of Turbo C++ 4.0J without writing a single ASM instruction; the EGC is definitely not the best tool for this job.
* [`th01_orb_debug`]: Shows the following information in TH01's debug mode:
  * Physics values for the Yin-Yang Orb at the bottom center of the playfield
  * The frames since the last collision with every bumper bar in the top-left corner of the respective stage object tile
* [`th01_sariel_fixes`]: Fixes three sprite glitches in the [TH01 Sariel fight] that result from clear logic errors in the original code.
* [`th03_real_hitbox`]: Renders [TH03's collision bitmap] onto both playfields. Highly unplayable.

* Fixes for the [TH04 Stage 5 Yuuka No-EMS crash]:
  * [`th04_noems_crash_fix`]: Increases the self-imposed memory limit of TH04's `MAIN.EXE` by just the right amount to fix that one crash.
  * [`mem_assign_all`]: Removes the self-imposed memory limits in all TH02-TH05 executables, additionally fixing other potential out-of-memory crashes that may occur during modding.

* Workarounds for the [TH04 Kurumi Divide Error crash]:
  * [`th04_0_ring_ignore`]
  * [`th04_0_ring_as_single_bullet`]
  * [`th04_0_ring_as_cap_bullets`]
  * [`th04_0_ring_as_gameover`]

* Workarounds for the [TH04 Stage 4 Marisa Divide Error crash]:
  * [`th04_marisa4_crash_still`]
  * [`th04_marisa4_crash_move`]
  * ▶ **`th04_marisa4_crash_warp`** (You are here!)

* [`community_choice_fixes`]: Combination branch of all "obvious" bugfixes that don't affect gameplay or visuals:
  * [`th01_critical_fixes`]
  * [`th03_no_gdc_frequency_check`]
  * [`th04_noems_crash_fix`]

  Plus the following workarounds for TH04's `Divide Error` bugs, chosen by community vote:

  * [`th04_0_ring_as_single_bullet`] ([poll results](https://twitter.com/ReC98Project/status/1512941767162798090))
  * [`th04_marisa4_crash_still`] ([poll results](https://twitter.com/ReC98Project/status/1515018996885688325))

----

## Building

### Required tools

* **Borland Turbo C++ 4.0J**

  This was the compiler ZUN originally used, so it's the only one that can deterministically compile this code to executables that are bit-perfect to ZUN's original ones.

  ----

* **Borland Turbo Assembler (TASM), version 5.0 or later, for 32-bit Windows (`TASM32.EXE`)**

  Borland never made a cross compiler targeting 16-bit DOS that runs on 32-bit Windows, so the C++ parts *have* to be compiled using a 16-bit DOS program. The not yet decompiled ASM parts of the code, however, *can* be assembled using a 32-bit Windows tool. This not only way outperforms any 16-bit solution that would have to be emulated on modern 64-bit systems, making build times, well, tolerable. It also removes any potential EMS or XMS issues we might have had with `TASMX.EXE` on these emulators.

  These advantages were particularly relevant in the early days of ReC98, when the ASM files were pretty huge. That's also when I decided to freely use long file names that don't need to conform to the 8.3 convention… As a result, the build process still starts with a separate 32-bit part (`build32b.bat`), which must be run in Windows (or Wine).

  In the end though, we'd definitely like to have a single-step 16-bit build process that requires no 32-bit tools. This will probably happen some time after reaching 100% position independence over all games.

  ----

* **Borland C++ 5.5, for 32-bit Windows (`BCC32.EXE`)**

  Released as freeware, and as of July 2020, still sort of officially downloadable from

    http://altd.embarcadero.com/download/bcppbuilder/freecommandLinetools.exe

  (SHA-256 `433b44741f07f2ad673eb936511d498c5a6b7f260f98c4d9a6da70c41a56d855`)

  Needed to fulfill the role of being "just *any* native C++ compiler" for our own tools that either don't necessarily *have* to run on 16-bit DOS, or are required by the 32-bit build step, as long as that one still exists (see above).

  Currently, this category of tools only includes the [converter for hardcoded sprites]. Since that one is written to be as platform-independent as possible, it could easily be compiled with any other native C compiler you happen to have already installed. (Which also means that future port developers hopefully have one less thing to worry about.)
  So, if you dislike additional dependencies, feel free to edit the `Tupfile` so that `bmp2arr` is compiled with any other C compiler of your choice.

  However, choosing Borland C++ 5.5 as a default for everyone else fits ReC98 very well for several reasons:

  * It still happens to be the most hassle- and bloat-free way to get *any* sort of 32-bit Windows C++ compiler to people, clearly beating Open Watcom, and the required registration for [Borland/Embarcadero's own C++ 7.30]. Depending on anything bigger would be way out of proportion, considering how little we use it for
  * We already rely on a 32-bit Windows tool
  * Turbo C++ 4.0J defines the lower bound for our allowed level of C++ features anyway, making Borland C++ 5.5's old age and lacking C++ standard compliance a non-issue
  * Unlike 7.30, 5.5 still works on Windows 9x, which is what typically runs on the real PC-98 hardware that some people might want to compile ReC98 on.
  * Other tiny C compilers have no C++ support. While the sprite converter is written in C, future tools might not be, and I'm too old to restrict people to C for no good reason.

  ----

* [**Tup**](http://gittup.org/tup/), for Windows (optional, but recommended)

  A sane, parallel build system, used to ensure minimal rebuilds during the 32-bit build part. Provides perfect tracking of dependencies via code injection and hooking a compiler's file opening syscalls, allowing it to automatically add all `#include`d files to the build dependency graph. This makes it way superior to most `make` implementations, which lack this vital feature, and are therefore inherently unsuited for pretty much any programming language imaginable. With no abstractions for specific compilers, Tup also fits perfectly with the ancient Borland tools required for this project.

  As of September 2020, the Windows version of Tup requires Vista or higher. In case Tup can't run or isn't installed, the build process falls back on a dumb batch file, which always fully rebuilds the entire 32-bit part.

  ----

* **DOSBox** (if you're running a 64-bit version of Windows, or a non-Windows operating system)

  For the most part, it shouldn't matter whether you use [the original DOSBox](https://dosbox.com) or your favorite fork. A DOSBox with dynamic recompilation is highly recommended for faster compilation, though. Make sure to enable that feature by setting the following options in its configuration file (`dosbox.conf` for the original version):

  ```ini
  [cpu]
  core=dynamic
  cycles=max
  ```

  ----

The most performant OS for building ReC98 is therefore a 32-bit Windows ≥Vista and <11, where both the 32-bit and 16-bit build parts can run natively from a single shell. The build process was tested and should work reliably on pretty much every system though – from modern 64-bit Windows and Linux, down to Windows 95, which you might use on actual PC-98 hardware.

### How to build

* Make sure you've created the `bin/bcc32.cfg` and `bin/ilink32.cfg` files for Borland C++ 5.5, as pointed out in its `readme.txt` file. This fixes errors like

  ```text
  Error E2209 Pipeline/bmp2arrl.c 12: Unable to open file 'io.h'
  ```

  that you will encounter otherwise.

* Running on a 64-bit OS? Run `build32b.bat` in a Windows shell, followed `build16b.bat` in your DOSBox of choice.
* Running on 32-bit Windows? Run just `build.bat`.

All batch files will abort with an error if any of the necessary tools can't be found in the `PATH`.

The final executables will be put into `bin\th0?`, using the same names as the originals. Running them requires each game's original assets in the same directory.

### Troubleshooting

* TCC compiles, but fails to link, with `Error: Unable to execute command 'tlink.exe'`

  **Cause:** To locate TLINK, TCC needlessly copies the `PATH` environment variable into a statically allocated 128-byte buffer. It then constructs absolute `tlink.exe` filenames for each of the semicolon- or `\0`-terminated paths, writing these into a buffer that immediately follows the 128-byte `PATH` buffer in memory. The search is finished as soon as TCC found an existing file, which gives precedence to earlier paths in the `PATH`. If the search didn't complete until a potential "final" path that runs past the 128 bytes, the final attempted filename will consist of the part that still fit into the buffer, followed by the previously attempted path.

  **Workaround:** Make sure that the `BIN\` path to Turbo C++ 4.0J is fully contained within the first 127 bytes of the `PATH` inside your DOS system.
  (The 128<sup>th</sup> byte must either be a separating `;` or the terminating `\0` of the `PATH` string.)

* TLINK fails with `Loader error (0000): Unrecognized Error` on 32-bit Windows ≥Vista

  This can be fixed by configuring the NTVDM DPMI driver to be loaded into conventional memory rather than upper memory, by editing `%WINDIR%\System32\autoexec.nt`:

  ```patch
  REM Install DPMI support
  -LH %SystemRoot%\system32\dosx
  +%SystemRoot%\system32\dosx
  ```

  Requires a reboot after that edit to take effect.

  ([Source](http://oshow.txt-nifty.com/blog/2008/11/loader-error-00.html))

## Contribution guidelines

See [`CONTRIBUTING.md`](CONTRIBUTING.md).

----

[indistinguishable]: https://github.com/nmlgc/mzdiff
[project blog]: https://rec98.nmlgc.net/blog
[converter for hardcoded sprites]: https://github.com/nmlgc/ReC98/issues/8
[Borland/Embarcadero's own C++ 7.30]: https://www.embarcadero.com/de/free-tools/ccompiler/free-download
[bloat]: CONTRIBUTING.md#zun-bloat
[landmines]: CONTRIBUTING.md#zun-landmine
[bugs]: CONTRIBUTING.md#zun-bug
[quirks]: CONTRIBUTING.md#zun-quirk

[TH04 Stage 5 Yuuka No-EMS crash]: https://rec98.nmlgc.net/blog/2021-11-29
[TH01 Sariel fight]: https://rec98.nmlgc.net/blog/2022-01-31
[TH03's collision bitmap]: https://rec98.nmlgc.net/blog/2022-02-18
[TH04 Kurumi Divide Error crash]: https://rec98.nmlgc.net/blog/2022-04-18
[TH04 Stage 4 Marisa Divide Error crash]: https://rec98.nmlgc.net/blog/2022-04-18
[two critical bugs in TH01]: https://rec98.nmlgc.net/blog/2022-05-31

[`master`]: https://github.com/nmlgc/ReC98/tree/master
[`anniversary`]: https://github.com/nmlgc/ReC98/tree/anniversary
[`debloated`]: https://github.com/nmlgc/ReC98/tree/debloated
[`BossRush`]: https://github.com/nmlgc/ReC98/tree/BossRush
[`community_choice_fixes`]: https://github.com/nmlgc/ReC98/tree/community_choice_fixes
[`mem_assign_all`]: https://github.com/nmlgc/ReC98/tree/mem_assign_all
[`th01_critical_fixes`]: https://github.com/nmlgc/ReC98/tree/th01_critical_fixes
[`th01_end_pic_optimize`]: https://github.com/nmlgc/ReC98/tree/th01_end_pic_optimize
[`th01_orb_debug`]: https://github.com/nmlgc/ReC98/tree/th01_orb_debug
[`th01_sariel_fixes`]: https://github.com/nmlgc/ReC98/tree/th01_sariel_fixes
[`th03_no_gdc_frequency_check`]: https://github.com/nmlgc/ReC98/tree/th03_no_gdc_frequency_check
[`th03_real_hitbox`]: https://github.com/nmlgc/ReC98/tree/real_hitbox
[`th04_0_ring_ignore`]: https://github.com/nmlgc/ReC98/tree/th04_0_ring_ignore
[`th04_0_ring_as_cap_bullets`]: https://github.com/nmlgc/ReC98/tree/th04_0_ring_as_cap_bullets
[`th04_0_ring_as_gameover`]: https://github.com/nmlgc/ReC98/tree/th04_0_ring_as_gameover
[`th04_0_ring_as_single_bullet`]: https://github.com/nmlgc/ReC98/tree/th04_0_ring_as_single_bullet
[`th04_marisa4_crash_move`]: https://github.com/nmlgc/ReC98/tree/th04_marisa4_crash_move
[`th04_marisa4_crash_still`]: https://github.com/nmlgc/ReC98/tree/th04_marisa4_crash_still
[`th04_noems_crash_fix`]: https://github.com/nmlgc/ReC98/tree/th04_noems_crash_fix
[`xJeePx`]: https://github.com/nmlgc/ReC98/tree/xJeePx
