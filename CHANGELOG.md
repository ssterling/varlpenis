Changelog
=========

3.0.1 (2022/10/31)
------------------

* Allow passing unrecognised arguments to configure script
  using `--ignore-invalid-arguments` (useful for wrappers
  expecting GNU Autoconf)

3.0.0 (2020/04/12)
------------------

The Great Compatibility Update.

* Added documentation for several vintage/retro platforms
* Cleaned up several `#ifdef` spaghetti chains to `#if defined(…)`
* Added `VP_USE_GETOPT_H` macro to select a local `getopt.h` over `unistd.h`
  for POSIX-noncompliant systems which have their own implementation
* Added `OPTION_CHAR` macro to properly tune getopt and docs
* Added color support for the Windows console, `conio.h` and 
	* Changed `--use-color` to `--use-color-<type>` to accomodate
* Moved options parsing to separate function
* Added ability to specify program arguments after launch
* Changed RNG to generate only if they're needed (to save time)
* Started using the right versioning system

2.0.1 (2020/01/01)
------------------

* Changes `str_length` in `repeat_string()` to be `strlen(str) + 1`,
  not just `strlen(str)`

2.0 (2020/01/01)
----------------

* Added NLS with gettext
* Added fullwidth (UTF-8) output option

1.2 (2019/04/13)
----------------

* Changed exit values from classic 0/1 to those of `sysexits.h`
* Implemented better random-number generator using POSIX microsecond time
* Changed occurences of `atoi()` to `strtol()`

1.1 (2019/04/01)
----------------

* Added option to enable colour output via ANSI escape codes

1.0 (2019/03/28)
----------------

* Initial release
