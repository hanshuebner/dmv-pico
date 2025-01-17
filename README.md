# dmv-pico - Hooking up a Raspberry Pi Pico 2 to a NCR Decision Mate 5

This repository contains experimental code to simulate a Signetics 2651 UART connected
to the bus of the NCR Decision Mate V.  This UART is also used in NCR's official serial
interface (K212) and thus should be compatible with software adapted to that chip.

The code is a proof of concept as I wanted to try hooking a Pico 2 to a 5V system without
level converters and simulate an UART chip in software.  It is unfinished and meant to
serve as a starting point for something more complete.
