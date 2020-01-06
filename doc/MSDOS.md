Compiling varlpenis on MS-DOS
=============================

For those interested in compiling a novelty penis program on archaic
operating systems, these instructions might come in handy.
Needed for this tutorial are a properly configured setup of
Borland Turbo C/C++ and `unix2dos` (or a similar program).

Preliminary work
----------------

### Creating `GETOPT.LIB`

Download the FreeDOS getopt library from ibilio at
<http://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/devel/libs/getopt/unix-like/>.
Compile the function with `TCC -c GETOPT.C`; this should produce `GETOPT.OBJ`.
Create a library with `TLIB /C GETOPT.LIB +GETOPT.OBJ`, and update the database
with `TLIB A:\PATH\TO\TC\LIB\CS.LIB+GETOPT.LIN`.
Finally, copy `GETOPT.H` into `TC\INCLUDE`.

### Converting line endings

At least with Borland Turbo C 2.01, the program refuses to compile without
DOS-style newlines (`\r\n` as opposed to `\n`), spitting out only the
cryptic message `Undefined module _main in C0S`.
Using a program such as `unix2dos`, convert the line endings of all
source files appropriately.

### Removing incompatible preprocessor directives

As of writing this tutorial, the only problematic directives are all
`#warning` in `draw.h`.
Just remove those; they're not completely necessary.

Actually compiling
------------------

The following macros should be set as needed:

| Macro                 | Definition                                          |
|----------------------:|-----------------------------------------------------|
| `VP_USE_GETOPT_H`     | Include `getopt.h` instead of `unistd.h` (required) |
| `VP_USE_COLOR_ANSI`   | Set to enable ANSI color output via `ANSI.SYS`      |
| `VP_VERSION_STR`      | Define with program version as seen in `configure`  |
| `OPTION_CHAR`         | Option prefix; likely `/` on DOS (`-` on UNIX)      |

Finally, you should be able compile the program.
Below is the command I used; your setup may vary:

```console
A:\VP\SRC>TCC -A -mt -DVP_USE_GETOPT_H -DVP_USE_COLOR_ANSI -DVP_VERSION_STR="2.0-DOS" -DOPTION_CHAR='/' MAIN.C DRAW.C
```
