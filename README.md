# PICO-PSU
A programmable constant current power supply.

# Description
This hardware/firmware project was born from the need to provide calibration LEDs with a constant current power supply for TESS-W calibration purposes.
However, the constant current source is programmable so that we can test photometers at low and high light levels.

## Hardware

The schematics below shows a PWM signal taken from a [Raspbberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) microcontroller board. This is low-pass filtered by R1 (10Kohms) and C1 (10uF), which produces a DC signal proportional to the ON part of the duty cycle from the minimun voltage (0,2mV) output from the pin  to the max voltage (3.37V). This signal is buffered through a voltage follower (U1) and finally fed to a constant current circuit built around another op-amp (U2) and a typical NPN transistor U3.

![Schematics](doc/img/schematics_pico-psu.png)

***Design note***: *Both U1 and U2 could be merged into a single op-amp.The actual chip provides with 4 op-amps, so there is no practical waste of hardware. For practical reasons, I tested each stage separately, decided not to apply any gain in U1 and introduced U2.*

The PWM square signal output is generated  from the microcontroller using one of its PWM modules with 16-bit resolution and the `TOP` register set to 65534 with no phase correction. The resulting frequency is around 1.907 KHz. This signal is heavily filtered with a first order low pass filter, whose cut-off frequency is $f_c = 1/(2\pi R_1C_1) = 1.59 Hz$:


This filters out the fundamental frequency and harmonics very well showing negligible ripple.

In my low pass filter + voltage follower tests, I found out that U1 introduces a 1.1 mV offset, so when there is no signal, there is a residual voltage fed to the constant current circuit, which translates into a residual current of 1.1 uA across the LED. This has no practical impact. Table 1 shows this effect.

![Table1](doc/img/table.png)

The constant current circuit is based on the principle of op-amp (U2) maitaining a constant voltage across R2 by its inverting input. 
This constant voltage translates into a $I_e$ emitter constant current flowing from the NPN transistor U3, thus forcing a constant current $I_c$ through its collector no matter the load connected to the collector (the LED in this case) as long as the transistor do not enter into saturation.

![Figure 1](doc/img/current_vs_count.png)

Figure 1 shows the experimental measurements. It shows that the current flowing through the LED is proportional to the ON part of the square waveform until it reaches the saturation regime of U3. Table 1 also shows the measured residual current of 1.2 uA at 0% duty cycle.

![Figure 2](doc/img/protoboard_pico-psu.jpg) 
Figure 2 shows the prototyped circuit in a protoboard. All op-amps are from the same LM324N chip, which accepts single supply rail lines. This is very convenient since we are dealing with unipolar signals (no negative voltages).

# Firmware
The firmware was writting using [FreeRTOS](https://www.freertos.org/), as a first contact with this micro-kernel.

Figure 3 below shows the software architecture in terms of FreeRTOS tasks. The FreeRTOS notifications mechanism is used as a quick way to send
commands to tasks. Commands with arguments are packed into 32 bit integers. The `linstep` command actually sends three notifications, as the
parameters do not fit into a single 32 bit word.

![Figure 3](doc/img/architecture.png)

Each task must define a `vXXXTaskSetup()` which actually executes before the FreeRTOS tasking system is started. 
This function typically initializes hardware and software resources *and also registers supported commands* to the console task.

## Console commands

The following commands are supported:
```
psu> help
Available commands (type <command>  [-h|--help] for details):
        led     : Turns on/off blinking of on-board LED.
        volt    : Get/Set a voltage level in arbitrary units.
        linstep : Define a voltage linear stepping.
        next    : Execute next step voltage.
``` 

Figure 4 shows the interactive definition and exectution of `linstep` and `ǹext`commands.

![Figure 4](doc/img/console.png)

## Acknowledgements
Besides [FreeRTOS](https://www.freertos.org/), this firmware has used the following valuable libraries:
* [The C Macro Collections project](https://github.com/LeoVen/C-Macro-Collections). A STL-like library for C developers. Based heavily on macros, almost all documents except one example are all outdated. But still worth it.
* [The linenoise library](https://github.com/antirez/linenoise). A simple, vt100-like library to implement consoles. Still, very heavy for microcontroller development. I have stripped it to a bare minimun: dumb mode only, no history, no editing. I have also modified the sources to use FreeRTOS heap memory management.
* [Argtable 2](https://github.com/jonathanmarvens/argtable2). Argument parsing library to implement commands with options. Slightly modified to use  FreeRTOS heap memory management and `float` command parsing.