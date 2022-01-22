# Noe's build of dwm

My build of dwm is heavily inspired by [Luke Smith's build](https://github.com/LukeSmithxyz/dwm), which I strongly encourage you to check out for more info.

## Patches and features

* [**actualfullscreen-20191112-cb3f58a**](https://dwm.suckless.org/patches/actualfullscreen/dwm-actualfullscreen-20191112-cb3f58a.diff) provides true fullscreen (`super+f`) in dwm.
* [**alpha/fixborders-6.2**](https://dwm.suckless.org/patches/alpha/dwm-fixborders-6.2.diff) keeps opaque borders when using terminal transparency.
* [**deck-6.0**](https://dwm.suckless.org/patches/deck/dwm-deck-6.0.diff) provides the deck layout and is accessible via `super+u`.
* [**focusmonmouse-6.2**](https://dwm.suckless.org/patches/focusmonmouse/dwm-focusmonmouse-6.2.diff) moves the mouse to the selected monitor.
* [**hide_vacant_tags-6.2**](https://dwm.suckless.org/patches/hide_vacant_tags/dwm-hide_vacant_tags-6.2.diff) hides tags which are not in use.
* [**losefullscreen-6.2**](https://github.com/bakkeby/patches/blob/master/dwm/dwm-losefullscreen-6.2.diff) exits fullscreen when switching focus.
* [**scratchpads-20200414-728d397b**](https://dwm.suckless.org/patches/scratchpads/dwm-scratchpads-20200414-728d397b.diff) is self-explanatory.
* [**stacker-6.2**](https://dwm.suckless.org/patches/stacker/dwm-stacker-6.2.diff) can move windows up the stack with `super+K/J`.
* [**swallow-20201211-61bb8b2**](https://dwm.suckless.org/patches/swallow/dwm-swallow-20201211-61bb8b2.diff) allows for programs launched via the terminal to take its place if they would make it inoperable.
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
