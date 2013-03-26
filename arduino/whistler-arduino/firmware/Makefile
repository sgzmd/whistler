# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# This is a prototype Makefile. Modify it according to your needs.
# You should at least check the settings for
# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected. We recommend that you leave it undefined and
#                add settings like this to your ~/.avrduderc file:
#                   default_programmer = "stk500v2"
#                   default_serial = "avrdoper"
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

DEVICE     = atmega2560
CLOCK      = 16000000
PROGRAMMER = -c stk500v2 -P avrdoper
FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m

# Tune the lines below only if you know what you are doing:

ARDUINO=/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino
ACORE=$(ARDUINO)/avr/cores/arduino

CPP=avr-g++
# You can use following line if no avr-g++ is installed
# /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++
CPPFLAGS=-c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections #-MMD

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

# COMPILE = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -IRF24 \
# 	-I$(ARDUINO)/avr/cores/arduino \
# 	-I$(ARDUINO)/avr/variants/mega \
# 	-I$(ARDUINO)/avr/libraries/SPI

SRC=$(wildcard *.c) $(wildcard *.cpp) RF24/RF24.cpp

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) $(CPPFLAGS)  -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@


.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) $(SRC)
