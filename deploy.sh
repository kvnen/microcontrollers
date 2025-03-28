#!/bin/bash

avr-gcc -mmcu=atmega328p -O2 main.c -o main.elf
avrdude -c arduino -p m328p -P /dev/ttyACM0 -U flash:w:main.elf
#for multiple file projects do the compile differently! I dunno how tho.
