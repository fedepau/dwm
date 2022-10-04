# CFP's build of dwm

My build of dwm. For documentation, refer to [the original website](https://dwm.suckless.org/).

## Applied patches:
- [accessnthmonitor](https://dwm.suckless.org/patches/accessnthmonitor/)
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [attachdirection](https://dwm.suckless.org/patches/attachdirection/)
- [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/)
- [focusonnetactive](https://dwm.suckless.org/patches/focusonnetactive/)
- [fullscreen](https://dwm.suckless.org/patches/fullscreen/)
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [movestack](https://dwm.suckless.org/patches/movestack/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [preserveonrestart](https://dwm.suckless.org/patches/preserveonrestart/)
- [scratchpad](https://dwm.suckless.org/patches/scratchpad/)
- [status2d](https://dwm.suckless.org/patches/status2d/)
- [status2d-xrdb](https://dwm.suckless.org/patches/status2d/)
- [statusallmons](https://dwm.suckless.org/patches/statusallmons/)
- [statuscmd](https://dwm.suckless.org/patches/statuscmd/)
- [swallow](https://dwm.suckless.org/patches/swallow/)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
- [warp](https://dwm.suckless.org/patches/warp/)
- [xrdb](https://dwm.suckless.org/patches/xrdb/)

## Requirements:
Xlib header files. On Arch-based systems:

```bash
# pacman -S libx11
```

## Installation:
Edit config.mk and config.h and run:

```bash
# make clean install
```
