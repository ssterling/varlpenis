Cross-compiling varlpenis for Commodore products
================================================

This tutorial is designed to work with the
[https://cc65.github.io/](cc65) compiler.
Get a copy working on your system, as well as an emulator such as
[http://vice-emu.sourceforge.net/](VICE) for optional testing purposes.

With no modification, varlpenis should cross-compile for these systems:
* Commodore 64
* Commodore 128

With removal of RNG, varlpenis should cross-compile for the following as well:
* Commodore PET
* CBM-II 600-series
* Commodore Plus/4

For some reason or another, the code generated by cc65 is too large
to fit into a VIC-20 executable.

See the [https://cc65.github.io/doc/intro.html#ss6.5](cc65 wiki) for a list
of other Commodore platforms for which you can likely compile with modification.

Preliminary work
----------------

### Changing the ejaculation character

In PETSCII there does not exist a tilde character, `~`.
cc65 automatically replaces this with an inverse T character, `┴`;
however, this may not be suitable for some users.
To change this, simply change the value of the macro `EJAC_CHAR` in `draw.h`.

### Random number generation

varlpenis relies on the `time()` function to seed `rand()`.
For systems without a realtime clock, the program will
simply refuse to compile as its libraries do not contain time functions.
The simplest route of action is to remove the random number generation
code in `main.c` and replace it with a fixed number.
However, if you're eager enough to be reading this tutorial,
there's a solid chance you already know of a way to implement RNG
without `time()` on a Commodore machine.

Compiling
---------

The following macros may be set as needed:

| Macro                 | Definition                                          |
|----------------------:|-----------------------------------------------------|
| `VP_USE_COLOR_CONIO`  | Set to enable color output via cc65 `conio.h`       |
| `VP_NO_ARGV`          | Enables inputting options without a shell           |
| `VP_VERSION_STR`      | Define with program version as seen in `configure`  |

Finally, you should be able compile the program.
Below is an example command for Commodore 128:

```console
smp@sakura:~/programs/varlpenis/src $ cl65 -O -t c128 -o varlpenis -D VP_USE_COLOR_CONIO -D VP_NO_ARGV -D VP_VERSION_STR=\"2.1-C128\" main.c draw.c options.c
```

I'll leave loading the executable onto tape/disk to you, the user who
knows much more about their Commodore system than I do.