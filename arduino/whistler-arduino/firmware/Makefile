# Basic Makefile which brings together simple main.c for Arduino,
# an excellent RF24 library for handling nrf24l01+ and some required
# libraries from Arduino distribution.
#
# Assumes OS X environment, but can be easily adapted for Linux.
# Assumes avr-gcc toolchain is installed.
#
# Author: Roman "sgzmd" Kirillov [me@romankirillov.info]

DEVICE     = atmega328p
#atmega2560
CLOCK      = 16000000
PROGRAMMER = -c stk500v2 -P avrdoper
FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m

ARDUINO_BASE=/Applications/Arduino.app/Contents/Resources/Java
ARDUINO=$(ARDUINO_BASE)/hardware/arduino
ACORE=$(ARDUINO)/avr/cores/arduino

CPP=/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc
CPPFLAGS=-c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -D__AVR_LIBC_DEPRECATED_ENABLE__ -MMD -fpermissive
AR  = /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar
LINKER=/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc -Os -Wl,--gc-sections -mmcu=$(DEVICE) -lm

COMPILE = $(CPP) -mmcu=$(DEVICE) \
	-DF_CPU=$(CLOCK)L -DARDUINO=152 \
	-I../../../common/arpix \
	-I/$(ARDUINO)/avr/cores/arduino \
	-I$(ARDUINO)/avr/variants/standard \
	-I$(ARDUINO)/avr/libraries/SPI \
	-IRF24

OBJECTS    = \
	main.o \
	RF24/RF24.o \
	$(ACORE)/wiring_digital.o \
	$(ACORE)/wiring.o \
	$(ACORE)/HardwareSerial.o \
	$(ACORE)/Print.o \
	$(ACORE)/WString.o \
	$(ACORE)/new.o \
	$(ACORE)/malloc.o \
	$(ACORE)/WInterrupts.o \
	$(ACORE)/wiring_analog.o \
	$(ACORE)/wiring_pulse.o \
	$(ACORE)/wiring_shift.o \
	$(ACORE)/IPAddress.o \
	$(ACORE)/main.o \
	$(ACORE)/Stream.o \
	$(ACORE)/Tone.o \
	$(ACORE)/hooks.o \
	$(ACORE)/USBCore.o \
	$(ARDUINO)/avr/libraries/SPI/SPI.o \


AVRDUDE = $(ARDUINO_BASE)/hardware/tools/avr/bin/avrdude -p$(DEVICE) \
	-C$(ARDUINO_BASE)/hardware/tools/avr/etc/avrdude.conf \
	-carduino \
	-P/dev/tty.usbmodemfd131 -b115200 -D

SRC=$(wildcard *.cc) $(wildcard *.cpp) RF24/RF24.cpp

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) $(CPPFLAGS)  -c $< -o $@

.cc.o:
	$(COMPILE) $(CPPFLAGS)  -c $< -o $@

.cpp.o:
	$(COMPILE) $(CPPFLAGS) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

core.a: $(OBJECTS)
	@for i in $(OBJECTS); do echo $(AR) rcs core.a $$i; $(AR) rcs core.a $$i; done

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

clean:
	rm -f main.hex main.elf main.eep main.d core.a $(OBJECTS)

main.elf: $(OBJECTS)
	$(LINKER) -o main.elf $(OBJECTS) -lm

main.hex: main.elf
	rm -f main.hex

	avr-objcopy -O ihex -j .eeprom \
		--set-section-flags=.eeprom=alloc,load \
		--no-change-warnings \
		--change-section-lma \
		.eeprom=0 \
		main.elf main.eep

	avr-objcopy -O ihex -R .eeprom  main.elf main.hex
	avr-size main.elf

cpp:
	$(COMPILE) $(SRC)
