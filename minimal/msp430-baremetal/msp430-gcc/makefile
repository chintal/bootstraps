                      
TARGETMCU	= msp430f5529
CC		= msp430-gcc
CXX		= msp430-g++
OBJCOPY		= msp430-objcopy
OBJDUMP		= msp430-objdump
SIZE		= msp430-size
LD		:= $(CC)
MSPDEBUG	= mspdebug

DEBUG		= -g
OPT		= -O0
WARNINGS	= -Wall -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align \
		  -Wsign-compare -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes \
		  -Wmissing-declarations -Wunused

CFLAGS		= -mmcu=$(TARGETMCU) $(OPT) $(DEBUG) -I. -Idrivers/ \
		  -DGCC_MSP430 $(WARNINGS)

LDFLAGS		= -mmcu=$(TARGETMCU)

SRCS 		= main.c \
		  drivers/HAL_PMM.c \
		  drivers/bc_uart.c \
		  drivers/tick_timer.c \
		  drivers/core_init.c

PROG 		= $(firstword $(SRCS:.c=))

OBJS 		= $(SRCS:.c=.o)

all: 		$(PROG).elf $(PROG).lst

$(PROG).elf:	$(OBJS)
	$(LD) $(LDFLAGS) -o $(PROG).elf $(OBJS)

%.o: 		%.c
	$(CC) -c $(CFLAGS) $< -o $@	

%.lst: 		%.elf
	$(OBJDUMP) -DS $< > $@
	$(SIZE) $<
	
install:	$(PROG).elf
	$(MSPDEBUG) -n tilib "prog $(PROG).elf"

clean :
	-rm -f $(PROG).elf $(PROG).lst $(OBJS)







	


