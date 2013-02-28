TARG=main
 
CC = avr-gcc
OBJCOPY = avr-objcopy

SRCS= main.c Test.c AT_lib.c uart.c
 
OBJS = $(SRCS:.c=.o)

MCU=atmega8

CFLAGS = -mmcu=$(MCU) -Wall -g3 -Os -Werror -lm  -mcall-prologues -DF_CPU=8000000
LDFLAGS = -mmcu=$(MCU)  -Wall -g3 -Os  -Werror 
 
all: $(TARG)
 
$(TARG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@.elf  $(OBJS) -lm
	$(OBJCOPY) -O binary -R .eeprom -R .nwram  $@.elf $@.bin
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram  $@.elf $@.hex
 
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
 
clean:
	rm -f *.elf *.bin *.hex  $(OBJS) *.map
