# dwm - dynamic window manager

`dwm` is an extremely fast, small, and dynamic window manager for `X`.

## Preview

![demo](preview.png)

## Features & Patches

- [clickable statusbar](https://dwm.suckless.org/patches/statuscmd/): Adds the ability to signal a status monitor program such as `dwmblocks`.
- [stacker](https://dwm.suckless.org/patches/stacker/): Provides utilities for managing the client stack.
- [swallow](https://dwm.suckless.org/patches/swallow/): If a program run from a terminal, it temporarily takes its place to save space.
- [xresources](https://dwm.suckless.org/patches/xresources/): Allows to handle settings from `Xresources`.
- [removeborder](https://dwm.suckless.org/patches/removeborder/): Remove the border when there is only one window visible.
- [fullscreen](https://dwm.suckless.org/patches/fullscreen/): Applies the monocle layout with the focused client on top and hides the bar.
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/): Adds (inner) gaps between client windows and (outer) gaps between windows and the screen edge in a flexible manner.
- [notitle](https://dwm.suckless.org/patches/notitle/): Doesn't show the title.
- [shiftview](https://dwm.suckless.org/patches/nextprev/): Increment or decrement the selected tag.
- [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/): Prevents `dwm` from drawing tags with no clients.
- [alpha](https://dwm.suckless.org/patches/alpha/): Allow `dwm` to have translucent bars, while keeping all the text on it opaque.
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/): Actually toggle `fullscreen` for a window, instead of toggling the status bar and the monocle layout.
- [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/): Cycles through all available layouts using `MOD-CTRL-period`.
- [xrdb](https://dwm.suckless.org/patches/xrdb/): Allows dwm to read colors from xrdb (.Xresources) at run time.

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
