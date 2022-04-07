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
  P1DIR |= LED_RED;		/**< Green led on when CPU on */
  P1OUT |= LED_RED;
//led_init();
  configureClocks();
  lcd_init();
  ////buzzer_init();
  //switch_init();

  enableWDTInterrupts();
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  //toy_reset();
  clearScreen(COLOR_PURPLE);
  while (1) {
  lcd_loop();

  P1OUT &= ~LED_RED;
  or_sr(0x10);
  P1OUT |= LED_RED;
}
  
  //or_sr(0x18);  // CPU off, GIE on





  //P1DIR |= LED_GREEN;		/**< Green led on when CPU on */
  //P1OUT |= LED_GREEN;
  //configureClocks();
  //lcd_init();
  //switch_init();
  
  //enableWDTInterrupts();      /**< enable periodic interrupt */
  //or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  //clearScreen(COLOR_BLUE);
 // while (1) {			/* forever */
  //  if (redrawScreen) {
  //    redrawScreen = 0;
  //    update_screen();
  //  }
  //  P1OUT &= ~LED_GREEN;	/* led off */
  //  or_sr(0x10);	/**< CPU OFF */
  //  P1OUT |= LED_GREEN;	/* led on */
//  }
} 

void __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    //switch_interrupt_handler();	/* single handler for all switches */
  }
}

//void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
//{
  //buzzer_timer_interrupt();
  //led_timer_interrupt();
  //wdt_c_handler();
//} 
