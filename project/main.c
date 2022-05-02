#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "input.h"
#include "output.h"
#include "lcd.h"
#include "ball.h"


void main()
{
  led_init();
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  game_loop();
}


/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */

    balls_handle_interrupt();
  }
}
