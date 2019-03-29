varlpenis
=========

Generate ASCII-art penis of arbitrary length

Usage
-----

Straight from the program:
```
usage: varlpenis [options]
  options:
    -e num   set length of semen string
    -h       show this message
    -l num   set length of shaft
    -v       show version and copyright info
```

Further documentation can be found on the `varlpenis(6)` man page.

Example
-------

```console
$ ./varlpenis
8==================D~~~
$ ./varlpenis
8=========================D~~
$ ./varlpenis -l 5 -e 8
8=====D~~~~~~~~
```

Installation
------------

```console
$ ./configure
$ make
# make install
```

Should work on UNIX-like systems; untested on Winblows, MS-DOS or anything
else.  Written in ANSI C using only the standard library.

Some notes
----------

This is a pet project I like to tend to when I'm absolutely bored and have
nigh nothing else to do.  That's why, for example, I wrote the configure
script from scratch.  Plus, it teaches me a bit about how it all works.

Contributing
------------

Tabs for indentation, spaces for alignment.  Put brackets on separate lines
for functions and the like; same line for enumerations or `if` clauses.
Just go through the code and copy the style; or,
[send me an e-Mail](ssterling@firemail.cc) if you're really that worried.

Please be descriptive in commits and merge requests; “fixed shit” doesn't
cut it.

Bugs
----

See [BUGS.md](BUGS.md).  Please report any bugs to the
[issue tracker](https://gitlab.com/ssterling/varlpenis/issues).
