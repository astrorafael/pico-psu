# ARGTABLE 2
This is a port of Stewart Heitmann's original [`argtable2 v2.13`](https://argtable.sourceforge.net/) library to an embedded environment such as Raspberry Pi Pico. The original `AUTHORS` and `COPYING` files are preserved.

## Changes
* An additional `argtable2_prv.h` file has been added to cope with custom heap management routines (such as in FreeRTOS)
* Directory structure has been rearranged to place `argtable2.h` under `include/argtable2`. The client software includes it as <argtable2/argtable2.h> 
* An additional CMakeLists.txt file has been added to integrate with the CMake build utility.
* This README file has been included
