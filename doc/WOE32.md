Compiling varlpenis on Windows
==============================

If you're using an inferior operating system and programming API,
these instructions might come in handy for you.
All that's needed for this measly tutorial is the MSVC compiler.

Preliminary work
----------------

### Including a `getopt()` function

I'm sure there are about seventy different POSIX-compatible
getopt substitutes out there, but I'll copy from the
[MS-DOS tutorial](MSDOS.md) and use the same thing.

Anywa, download the FreeDOS getopt library from ibilio at
<http://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/devel/libs/getopt/unix-like/>.
Copy `getopt.c` and `getopt.h` into the `src\` directory.
That should be about it.

Actually compiling
------------------

The following macros should be set as needed:

| Macro                | Definition                                          |
|---------------------:|-----------------------------------------------------|
| `VP_USE_GETOPT_H`    | Include `getopt.h` instead of `unistd.h` (required) |
| `VP_USE_COLOR_WOE32` | Set to enable color output via the Windows API      |
| `VP_USE_COLOR_ANSI`  | Set to enable color output via ANSI (Win10+ only)   |
| `VP_VERSION_STR`     | Define with program version as seen in `configure`  |
| `OPTION_CHAR`        | Option prefix; likely `/` on Woe32 (`-` on UNIX)    |

Finally, you should be able compile the program.
Below is the command I used; your setup may vary:

```console
E:\vp\src> cl /TC /Fe"varlpenis" main.c draw.c getopt.c /DVP_USE_GETOPT_H /DOPTION_CHAR="'/'" /DVP_USE_COLOR_WOE32 /DVP_VERSION_STR="2.0.1-WOE32"
```

Alternatively, download the executable
--------------------------------------

The latest version of varlpenis is available on my website at
<https://www.ssterling.net/comp/varlpenis/woe32/>.
