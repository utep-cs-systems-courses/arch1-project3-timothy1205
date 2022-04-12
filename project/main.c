#include <msp430.h>
#include "libTimer.h"
#include "input.h"
#include "output.h"
#include "toy.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcd.h"

extern short redrawScreen;
void main(void) 
{  
  led_init();
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();

  enableWDTInterrupts();
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  toy_reset();
  clearScreen(COLOR_PURPLE);
  
  while (1) {
    lcd_loop();

    led_red_off();
    or_sr(0x10);
    led_red_on();
  }
  
or_sr(0x18);  // CPU off, GIE on

} 

void __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
