Cross-compiling varlpenis for the Apple II series
=================================================

This tutorial is designed to work with the
[https://cc65.github.io/](cc65) compiler.
Get a copy working on your system, as well as an emulator such as
[https://github.com/AppleWin/AppleWin](AppleWin) for optional testing purposes.

Preliminary work
----------------

### Changing the ejaculation character

In the original Apple II character set,
there does not exist a tilde character, `~`.
cc65 automatically replaces this with a caret, `^`;
however, this may not be suitable for some users.
To change this, simply change the value of the macro `EJAC_CHAR` in `draw.h`.

Compiling
---------

The following macros may be set as needed:

| Macro                 | Definition                                          |
|----------------------:|-----------------------------------------------------|
| `VP_NO_ARGV`          | Enables inputting options without a shell           |
| `VP_VERSION_STR`      | Define with program version as seen in `configure`  |

Finally, you should be able compile the program.
Below is an example command for the Apple IIe Enhanced:

```console
smp@sakura:~/programs/varlpenis/src $ cl65 -O -t apple2enh -o varlpenis -D VP_NO_ARGV -D VP_VERSION_STR=\"2.1-APPLE\" main.c draw.c options.c
```

I'll leave loading the executable onto tape/disk to you, the user who
knows much more about their Apple II than I do.
