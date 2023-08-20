Cross-compiling varlpenis for Atari 8-bit systems
=================================================

This tutorial is designed to work with the
[cc65](https://cc65.github.io/) compiler.
Get a copy working on your system, as well as an emulator such as
[Altirra](https://www.virtualdub.org/altirra.html) for
optional testing purposes.

Compiling
---------

The following macros may be set as needed:

| Macro                 | Definition                                          |
|----------------------:|-----------------------------------------------------|
| `VP_NO_ARGV`          | Enables inputting options without a shell           |
| `VP_NO_TIME`          | Use methods other than `time()` to seed `srand()`   |
| `VP_VERSION_STR`      | Define with program version as seen in `configure`  |

Finally, you should be able compile the program.
Below is an example command for an Atari 800:

```console
smp@sakura:~/programs/varlpenis/src $ cl65 -O -t atari -o varlpenis -D VP_NO_ARGV -D VP_NO_TIME -D VP_VERSION_STR=\"3.0.3-A800\" main.c draw.c options.c
```

I'll leave loading the executable onto tape/disk to you, the user who
knows much more about their Atari system than I do.

Bugs
----

The program behaves strangely in two specific ways:

1. When run with no arguments, the shaft is eighteen characters long and the penis
   has no head or ejaculate.
2. When run with argument `-l` and any value, the penis is not present.
   On an Atari 800 emulated in Altirra, a few characters of the penis appear briefly
   before disappearing.
