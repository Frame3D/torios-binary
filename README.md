# torios-binary
A group of small fltk programs the internal icons are located in the header [include/toolbar_icons.h](https://github.com/Israel-D/torios-binary/blob/master/include/toolbar_icons.h)

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

## flfm

This is basically not usable yet, but is an experimental idea for a lightweight filemanager

## flapt

This is unusable still... but can be a visual apt program (eventually)
