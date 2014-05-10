PRG            = blink
OBJ            = $(PRG).o
MCU_TARGET     = atmega328p
PART_NUMBER    = m328p
OPTIMIZE       = -O2
DEV            = /dev/sensors/ftdi_A5025VXV
PROGRAMMER     = arduino
F_CPU          = 20000000


DEFS           = -DF_CPU=$(F_CPU)
LIBS           =

# You should not have to change anything below here.

CC             = avr-gcc
CXX            = avr-g++
AVRDUDE        = avrdude
OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map


# all: $(PRG).elf lst text eeprom
all: $(PRG).hex

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(PRG).elf *.map *.hex

hex:  $(PRG).hex

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

EXTRA_CLEAN_FILES       = *.hex *.bin *.srec

upload:
	$(AVRDUDE) -p $(PART_NUMBER) -P $(DEV) -c $(PROGRAMMER) -F -u -U flash:w:$(PRG).hex
