# Basic Makefile which brings together simple main.c for Arduino,
# an excellent RF24 library for handling nrf24l01+ and some required
# libraries from Arduino distribution.
#
# Assumes OS X environment, but can be easily adapted for Linux.
# Assumes avr-gcc toolchain is installed.
#
# Author: Roman "sgzmd" Kirillov [me@romankirillov.info]

DEVICE     = atmega2560
CLOCK      = 16000000
PROGRAMMER = -c stk500v2 -P avrdoper
FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m

ARDUINO_BASE=/Applications/Arduino.app/Contents/Resources/Java
ARDUINO=$(ARDUINO_BASE)/hardware/arduino
ACORE=$(ARDUINO)/avr/cores/arduino

CPP=avr-g++
CPPFLAGS=-c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections

COMPILE = $(CPP) -mmcu=$(DEVICE) \
	-DF_CPU=$(CLOCK)L -DARDUINO=152 \
	-I/$(ARDUINO)/avr/cores/arduino \
	-I$(ARDUINO)/avr/variants/mega \
	-I$(ARDUINO)/avr/libraries/SPI \
	-IRF24

OBJECTS    = main.o RF24/RF24.o \
	$(ACORE)/wiring_digital.o \
	$(ACORE)/wiring.o \
	$(ARDUINO)/avr/libraries/SPI/SPI.o \


AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) \
	-C/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/etc/avrdude.conf \
	-P/dev/tty.usbmodemfd131 -b115200 -D

SRC=$(wildcard *.c) $(wildcard *.cpp) RF24/RF24.cpp

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) $(CPPFLAGS)  -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

clean:
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size main.elf

cpp:
	$(COMPILE) $(SRC)
