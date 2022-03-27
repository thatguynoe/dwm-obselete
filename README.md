# Noe's build of dwm

My build of dwm is heavily inspired by [Luke Smith's build](https://github.com/LukeSmithxyz/dwm), which I strongly encourage you to check out for more info. Running on commit [`d39e2f3441fe18aba8d1a62c08918a411ec6f237`](https://git.suckless.org/dwm/commit/d39e2f3441fe18aba8d1a62c08918a411ec6f237.html).

## Patches and features

* [**actualfullscreen-20211013-cb3f58a**](https://dwm.suckless.org/patches/actualfullscreen/dwm-actualfullscreen-20211013-cb3f58a.diff) provides true fullscreen (`super+f`) in dwm.
* [**alpha/fixborders-6.2**](https://dwm.suckless.org/patches/alpha/dwm-fixborders-6.2.diff) keeps opaque borders when using terminal transparency.
* [**alwayscenter-20200625-f04cac6**](https://dwm.suckless.org/patches/alwayscenter/dwm-alwayscenter-20200625-f04cac6.diff) makes all floating windows centered.
* [**deck-6.2**](https://dwm.suckless.org/patches/deck/dwm-deck-6.2.diff) provides the deck layout and is accessible via `super+u`.
* [**exitfullscreen-6.3**](https://github.com/LukeSmithxyz/dwm/pull/186/files) exits fullscreen if a new window is spawned.
* [**focusmonmouse-6.2**](https://dwm.suckless.org/patches/focusmonmouse/dwm-focusmonmouse-6.2.diff) moves the mouse to the selected monitor.
* [**hide_vacant_tags-6.2**](https://dwm.suckless.org/patches/hide_vacant_tags/dwm-hide_vacant_tags-6.2.diff) hides tags which are not in use.
* [**scratchpads-20200414-728d397b**](https://dwm.suckless.org/patches/scratchpads/dwm-scratchpads-20200414-728d397b.diff) is self-explanatory.
* [**stacker-6.2**](https://dwm.suckless.org/patches/stacker/dwm-stacker-6.2.diff) can move windows up the stack with `super+K/J`.
* [**sticky-6.1**](https://dwm.suckless.org/patches/sticky/dwm-sticky-6.1.diff) makes windows "sticky" with `super+s`.
    * [**noautofocussticky-6.2**](https://github.com/LukeSmithxyz/dwm/pull/181/files) does not focus sticky windows when switching tags.
    * The `focus(NULL)` code on line 1898 in `dwm.c` switches focus to the visible window upon unstickying a window; no more accidentally killing previously-stickied windows.
* [**swallow-6.2**](https://dwm.suckless.org/patches/swallow/dwm-swallow-6.2.diff) allows for programs launched via the terminal to take its place if they would make it inoperable.
* [**vanitygaps-6.2**](https://dwm.suckless.org/patches/vanitygaps/dwm-vanitygaps-6.2.diff) provides gaps throughout all layouts.
* Autostarts [dwmblocks](http://github.com/thatguynoe/dwmblocks) through the `runAutostart` function in `dwm.c`.

## Installation

```
git clone https://github.com/thatguynoe/dwm
cd dwm
sudo make install
```

## Please install `libxft-bgra`<sup>`aur`</sup>!

In order for dwm to display color emojis, the `libxft-bgra`<sup>`aur`</sup> package must be installed---else, dwm will crash.
