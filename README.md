# dwm - dynamic window manager

`dwm` is an extremely fast, small, and dynamic window manager for `X`.


## Features & Patches
- [clickable statusbar](https://dwm.suckless.org/patches/statuscmd/): adds the ability to signal a status monitor program such as `dwmblocks`.
- [stacker](https://dwm.suckless.org/patches/stacker/): provides utilities for managing the client stack.
- [swallow](https://dwm.suckless.org/patches/swallow/): if a program run from a terminal, it temporarily takes its place to save space.

## Requirements

In order to build `dwm` you need the `Xlib` header files.


## Installation

Edit `config.mk` to match your local setup (`dwm` is installed into the `/usr/local` namespace by default).

Afterwards enter the following command to build and install `dwm` (if necessary as root):

```bash
make clean install
```

## Running

Add the following line to your `.xinitrc` to start `dwm` using `startx`:

```bash
exec dwm
```

In order to connect `dwm` to a specific display, make sure that the `DISPLAY` environment variable is set correctly, e.g.:

```bash
DISPLAY=foo.bar:1 exec dwm
```

(This will start `dwm` on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your `.xinitrc`:

```bash
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
  sleep 1
done &
exec dwm
```

## Configuration

The configuration of `dwm` is done by creating a custom `config.h` and (re)compiling the source code.
