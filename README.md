# Bildpunk

A C library for programming vga mode 0x13.

## Etymology

Bildpunk is denglish – it's a mixture of german and english. It is pronounced as "build punk" and means "picture punk".

The name is derived from the german word for "pixel", which is also the swedish word for "pixel", which is _Bildpunkt_. As this library is DOS-first, the name wants to stay inside the 8-character filename limitation of the DOS file system. This way, the _Bildpunk_ was born.

It perfectly describes what Bildpunk is made for: to be creative with pixels.

## Building via linux, targetting MSDOS

`mode256` is built using the OpenWatcom v2 compiler

To build, run:

```sh
# add watcom dos folders to environment
source owsetenv_dos.sh

# use WMAKE to build
wmake -f Makefile.ow2
```

## LICENSE

bildpunk is Public Domain.

The licenses of the dependencies apply (WIP, no dependencies yet)

- lodepng is Copyright (c) 2005-2018 Lode Vandevenne
