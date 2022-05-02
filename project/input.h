#ifndef input_included
#define input_included

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SWITCHES 15

void switch_interrupt_handler(void);
void switch_init(void);
char switch_update_interrupt_sense();

#endif
