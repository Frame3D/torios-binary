# torios-binary
A group of small fltk programs for many uses!

the internal icons are located in the [xpm](https://github.com/Israel-D/torios-binary/blob/master/include/xpm) directory

current Debian/Ubuntu Build-Depends:

```
 debhelper (>= 9.0.0),
 gcc-multilib [amd64],
 g++-multilib [amd64],
 gcc-multilib [amd64],
 g++-multilib [amd64],
 libc6,
 libxcursor-dev,
 libfltk-images1.3,
 libfltk1.3,
 libfltk1.3-dev,
 libfltk1.3-compat-headers,
 libgcc1,
 libstdc++6,
 libx11-dev,
 libxpm-dev,
 libxinerama-dev,
 libxft-dev,
 libcairo2-dev,
 libjpeg-dev,
 libxext-dev,
 libpng-dev,
 libxfixes-dev,
 libapt-pkg-dev,   ## flapt only
 fluid             ## used to generate cxx/h files automatically...
```

## flpad

A text editor with initial syntax highlighting available for c/c++ files.
This was written using the tutorial on the website, with some seriously heavy modification to run ias a modern tabbed text editor.


This also includes a heavily modified [lexertk.hpp](https://github.com/ArashPartow/lexertk) to process the text for syntax highlighting.


It is extremely easy to add new language definitions copy styles.flpad to $XDG_USER_CONFIG/flpad and edit it:

```conf
[c]
ext=cxx,cpp,c
keywords=alignas, alignof, and, and_eq, asm, bitand, bitor, break, case, catch, class, compl, constexpr, continue, default, delete, do, dynamic_cast, else, explicit, export, extern, false, for, friend, goto, if, inline, new, noexcept, not, not_eq, operator, or, or_eq, private, protected, public, register, reinterpret_cast, return, sizeof, struct, switch, template, this, thread_local, throw, true, try, typedef, typeid, typename, union, using, while, xor, xor_eq
types=auto, bool, char, char16_t, char32_t, class, const, const_cast, decltype, double, dynamic_cast, enum, explicit, extern, float, friend, inline, int, long, mutable, namespace, nullptr_t, private, protected, public, register, short, signed, sizeof, static, static_assert, static_cast, string, struct, template, typedef, typename, union, unsigned, virtual, vector, void, volatile, wchar_t
```
This will look at all files with the cxx,cpp,c extentions and use these keywords, and types for syntax highlighting


For shell scripts it will read the shebang line and look for the header, ex
`#!/bin/sh` will look for the [sh] header


You can also turn syntax highlighting on for regular text files to have all quotes highlighted, numbers colored, as well as brackets, etc...


This can make editing plain text more fun :smile:

this is how the README.md files are treated... no keywords, just a simple header

![Alt text](/screenshots/flpad.png?raw=true "flpad")

## flcalc

A re-themed version of the libre software [flcalc](https://sourceforge.net/projects/flcalc/)


![Alt text](/screenshots/flcalc.png?raw=true "Re-Themed flCalc")

## flaskpass

A simple input dialog that prints to stdout the value entered into the password field, suitable for all askpass usages:

```sh
# some sort of profile/init script... like .xinitrc, .bashrc or whatever
SUDO_ASKPASS="/path/to/flaskpass"
export SUDO_ASKPASS
SSH_ASKPASS="/path/to/flaskpass"
export SSH_ASKPASS
```

![Alt text](/screenshots/flaskpass.png?raw=true "flaskpass")

## flabout

A simple dialog that either displays the internal text, or the cli arguments given as the dialog contents

![Alt text](/screenshots/flabout.png?raw=true "flabout")

## flimage

A simple image viewer that allows zooming, and keyboard navigation ( "," backawards "." forwards) of current image directory

![Alt text](/screenshots/flimage.png?raw=true "flimage")

## flrun

a very simple run dialog

![Alt text](/screenshots/flrun.png?raw=true "flrun")

## flscreenie

a fullscreen (ONLY) screenshot tool

![Alt text](/screenshots/flscreenie.png?raw=true "flscreenie")

## flwelcome

This is pretty much only usable (as is) for ToriOS Debian/Ubuntu based distros

![Alt text](/screenshots/flwelcome.png?raw=true "flwelcome")

## flapt

This is unusable still... but can be a visual apt program (eventually)
