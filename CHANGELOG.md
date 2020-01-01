Changelog
=========

2.0.1 (2020/01/01)
------------------

* Change `str_length` in `repeat_string()` to be `strlen(str) + 1`,
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
