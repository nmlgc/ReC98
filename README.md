# The Touhou PC-98 Restoration Project (*"ReC98"*)

### Overview

This project aims to rebuild the first five games of the [Touhou Project](http://en.wikipedia.org/wiki/Touhou_Project) series by *ZUN Soft* (now *Team Shanghai Alice*), which were originally released exclusively for the NEC PC-9801 system, into a cross-platform, open and truly moddable form.

The original games in question are:

* TH01: 東方靈異伝　～ The Highly Responsive to Prayers (1997)
* TH02: 東方封魔録　～ the Story of Eastern Wonderland (1997)
* TH03: 東方夢時空　～ Phantasmagoria of Dim.Dream (1997)
* TH04: 東方幻想郷　～ Lotus Land Story (1998)
* TH05: 東方怪綺談　～ Mystic Square (1998)

After completely decompiling the games first, we can then build an efficient environment for modifications on top. This project could then easily achieve what [thcrap](http://thcrap.nmlgc.net) has always wanted to do but struggled to realize, due to its nature of only being a patching framework targeted at 32-bit Windows binaries.

This approach is different from a project like [PyTouhou](http://pytouhou.linkmauve.fr/), a free/libre black-box reimplementation of the engine of TH06, [東方紅魔郷 ～ the Embodiment of Scarlet Devil](http://en.wikipedia.org/wiki/The_Embodiment_of_Scarlet_Devil). There are a number reasons why decompilation seems to be more worthwhile for the PC-98 games:

* While stage enemies and their bullet patterns are controlled by bytecode in TH04's and TH05's .STD files that *could* just be interpreted by an alternate VM, midboss and boss battles are entirely hardcoded into the executables.
* Even though complete decompilation will take a long time, partial reverse-engineering results will be very useful to modders who just want to work on the original PC-98 versions of the games.
* PC-98 emulation is messy and overly complicated. It has been getting better as of 2018 thanks to [DOSBox-X](https://github.com/joncampbell123/dosbox-x) adding support for the platform, but even at its best, it will always consume way more system resources than what would be appropriate for those games.
* thcrap-style multilingual translation on PC-98 would be painful for languages with non-ASCII scripts. The obvious method of modifying the font ROM specifically for each language is ugly and won't work on real hardware, so a custom renderer would be needed. That by itself requires a lot of reverse-engineering and, preferably, compilable source code to avoid the limits of hex-editing. Or, even better, the prospect to do this entirely on a more modern system.
* These games stopped being sold in 2002, ZUN has confirmed on multiple occasions to have lost all the data of the "earlier games" <sup>[citation needed]</sup>, and PC-98 hardware is long obsolete. In short, these games are as abandoned as they can possibly be, and are unlikely to ever turn a profit again.

#### So is this about remakes?
Even once we get to porting the games to modern systems, our goal will still be quite different from the typical idea of [a from-scratch *remake* in a modern engine](https://www.youtube.com/watch?v=-W5YIY4UWsY), which typically involves little or no original data. ReC98 by itself will only ever be about providing *exact, credible, source ports* that fully replace the need for the proprietary, PC-98-exclusive original releases and their emulation for even the most conservative fan. Ultimately, this project should merely serve as the *foundation* for future remastered versions of these games, developed by third parties. And after all, preserving a reconstructed, readable version of the games' source code is undoubtedly more valuable than preserving a bunch of binaries.

To achieve this, ReC98 has been kept in an openly available Git repository from day one. Each commit represents an atomic step along the way. This makes it easy to prove the correctness of the reconstruction process, or to track down potential regressions.

#### Is this even viable?
It certainly *seems* to be. During the development of the static English patches for these games, we identified two main libraries used across all 5 games, and even found their source code. These are:

* [master.lib](http://www.koizuka.jp/~koizuka/master.lib/), a 16-bit x86 assembly library providing an abstraction layer for all components of a PC-98 DOS system
* as well as the Borland C/C++ runtime library, version 4.0.
* Additionally, TH01 includes the [Pi loader library by 電脳科学研究所/BERO](http://www.vector.co.jp/soft/dos/prog/se037608.html).

master.lib and the C/C++ runtime alone make up a sizable amount of the code in all the executables. In TH05, for example, they amount to 74% of all code in `OP.EXE`, and 40% of all code in `MAIN.EXE`. That's already quite a lot of code we do not have to deal with. Identifying the rest of the code shared across the games will further reduce the workload to a more acceptable amount.

With DOSBox-X and [the Debug edition of Neko Project II](https://github.com/nmlgc/np2debug), we now also have two open-source PC-9821 emulators capable of running the games. This will greatly help in understanding and porting all hardware-specific code.

Still, it will no doubt take a long time until this project will have made any visible and useful progress. Any help will be appreciated!

## Roadmap

### Reconstruction phase
First, we have to accurately reconstruct understandable C/C++ source code for all the games from the original binaries, while still staying on the PC-98 platform. To ensure the correctness of the process, each commit during this phase should result in a build that ideally is byte-identical to the previous commit.

##### Step 1: Dumping
Based on the auto-analysis done by IDA, create assembly dumps for all necessary executables, and edit them until they successfully recompile back into working binaries equivalent to ZUN's builds. In total, there are 27 unique executables we need to dump:

* TH01: `zunsoft.com`, `op.exe`, `reiiden.exe`, `fuuin.exe`
* TH02: zun.com (<s>`ongchk.com`</s>, `zuninit.com`, `zun_res.com`, <s>`zunsoft.com`</s>), `op.exe`, `main.exe`, `maine.exe`
* TH03: zun.com (<s>`ongchk.com`</s> [-1], <s>`zuninit.com`</s> [-2], <s>`zunsoft.com`</s> [-3], `zunsp.com` [-4], `res_yume.com` [-5]), `op.exe`, `main.exe`, `mainl.exe`
* TH04: zun.com (<s>`ongchk.com`</s> [-O], `zuninit.com` [-I], `res_huma.com` [-S], `memchk.com` [-M]), `op.exe`, `main.exe`, `maine.exe`
* TH05: zun.com (<s>`ongchk.com`</s> [-O], `zuninit.com` [-I], `res_kso.com` [-S], `gjinit.com` [-G], `memchk.com` [-M]), `op.exe`, `main.exe`, `maine.exe`

Crossed-out files are identical to their version in the previous game. ONGCHK.COM is part of the PMD sound driver by KAJA, and therefore doesn't need to be disassembled either; we only need to keep the binary to allow bit-perfect rebuilds of ZUN.COM.

##### Step 2: Reduction (current)
Identify duplicated functions and either replace them with references to the original libraries or move them to separate include files. In the end, only ZUN's own code and data will remain in the dumps created in Step 1.

##### Step 3: Reverse-engineering
Translate the remaining assembly back into platform-independent C code. Some PC-98-specific in-line assembly inside ZUN's code will remain, which will have to be kept and moved to a separate library for now.

### Modernization phase
With the source code recreated, everything is possible! Let's turn them into the best games they can possibly be.

##### Step 4: Porting
* Refactor Neko Project II's graphics and sound emulation into a library we can hook up to our code
* Port all of master.lib and the shared hardware-specific library built in Step 3
* Rewrite all DOS API calls (`int 21h`) into platform-independent alternatives

##### Step 5: Sanitization
Get rid of any bad coding practices and the remaining hardware-specific formats, while breaking compatibility to both PC-98 hardware and the original data in the process. This includes, but won't be limited to:
* removing unnecessary encryption
* using text and custom fonts instead of graphics where possible
* standardizing graphics formats to PNG, replacing all the original ones (.grf, .cdg, .cd2, .bos, .mrs, .pi, .grp, as well as hardcoded bitmaps)
* merging the three executables per game into one
* changing gaiji characters into a semantically better representation (Unicode characters, alternate fonts, or simply normal graphics) on a case-by-case basis

##### Step 6: Moddability
Do whatever else is necessary to easily modify the game elements people like to modify. This may involve further changes to the formats used by the games, and the addition of one or more scripting languages (and subsequent porting of previously hardcoded functions). Mods will use the thcrap patch format, complete with support for patch stacking and dependencies, and will be easily selectable from a new menu added to every game.

A clear line will be drawn between the original content and fanmade modifications, which will only be available as optional packages. This also means that we won't ship the reconstructed games with any existing English translation patch. For the visible modifications that *will* be necessary (read: the "Mods" screen in the main menu), great care will be taken to keep them in the spirit of the original PC-98 games.

Since this will most likely result in graphics mods that exceed the specifications of PC-98 hardware, there will also be an optional filter to reduce the rendered output to the original resolution of 640x400 and a 16-color palette, for the sake of keeping the original spirit.

## Building
You will need:

* Borland Turbo C++ 4.0J
* Borland Turbo Assembler (TASM), version 5.0 or later, in a 32-bit version (`TASM32.EXE`)
* [DOSBox](http://dosbox.com) if you're running a 64-bit version of Windows, or a non-Windows operating system

  To speed up compilation, make sure to set the following in `dosbox.conf`:
  ```
  [cpu]
  core=dynamic
  cycles=max
  ```

The Borland tools are the only ones that will, with the correct command-line switches for each game, deterministically compile this source code to executables that are bit-perfect to ZUN's original ones. Hence, they are the only supported build tools during all of the reconstruction phase.

To build, simply run `build.bat` and follow the instructions.

Since I, unfortunately, decided earlier in development to freely use long file names that don't need to conform to the 8.3 convention, the first part of the building process (`build32b.bat`) must be run in Windows (or Wine). This will be fixed as development goes along.

The final executables will be put into `bin\th0?`, using the same names as the originals.
