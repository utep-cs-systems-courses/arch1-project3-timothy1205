# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:project3-c.elf project3-s.elf

COMMON_OBJECTS  = main.o wdt_handler.o lcd.o input.o output.o ball.o utils.o

#additional rules for files
project3-c.elf: ${COMMON_OBJECTS} switch_interrupt_handler-c.o buzzer_timer_interrupt-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

project3-s.elf: ${COMMON_OBJECTS} switch_interrupt_handler-s.o buzzer_timer_interrupt-s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-c: project3-c.elf
	msp430loader.sh $^

load-s: project3-s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
