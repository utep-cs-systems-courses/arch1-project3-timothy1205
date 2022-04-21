#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 3) {		
    secCount = 0;
    redrawScreen = 1;
  }
}
  
void update_shape();
void draw_square();

typedef enum enum_SquareState {
  RIGHT, DOWN, LEFT, UP
} SquareState;
#define SQUARE_SIZE 50

void draw_square()
{
  static unsigned char posX = 0, posY = 0;
  static SquareState squareState = RIGHT;

  fillRectangle(posX, posY, SQUARE_SIZE, SQUARE_SIZE, COLOR_PURPLE);

  switch (squareState) {
    case RIGHT:
      if ((++posX) + SQUARE_SIZE >= screenWidth) {
        squareState = DOWN;
        posX = screenWidth - SQUARE_SIZE;
      }
      fillRectangle(posX - 1, posY, 1, SQUARE_SIZE, COLOR_BLUE);
      break;
    case DOWN:
      if ((++posY) + SQUARE_SIZE >= screenHeight) {
        squareState = LEFT;
        posY = screenHeight - SQUARE_SIZE;
      }
      fillRectangle(posX, posY - 1, SQUARE_SIZE, 1, COLOR_BLUE);
      break;
    case LEFT:
      if (--posX <= 0) {
        squareState = UP;
        posX = 0;
      }
      fillRectangle(posX + SQUARE_SIZE, posY, 1, SQUARE_SIZE, COLOR_BLUE);
      break;
    case UP:
      if (--posY <= 0) {
        squareState = RIGHT;
        posY = 0;
      }
      fillRectangle(posX, posY + SQUARE_SIZE, SQUARE_SIZE, 1, COLOR_BLUE);
      break;
  }
}

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      draw_square();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}

/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
